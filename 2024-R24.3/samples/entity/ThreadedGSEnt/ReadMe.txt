========================================================================
    ThreadedGSEnt.arx sample application

Copyright 2023 Autodesk, Inc.  All rights reserved.

Use of this software is subject to the terms of the Autodesk license 
agreement provided at the time of installation or download, or which 
otherwise accompanies this software in either electronic or hard copy form.   
========================================================================

This sample application demonstrates how a custom ARX entity can make use of a
new feature to perform dynamic re-tessellations on a worker thread, instead of
the main thread. The goal is new feature is to no longer block the main thread
(which usually manifests to the users in a brief lag in cursor movements and
pan/zoom/orbit operations) for re-tessellations.

All entities that query AcGiWorldDraw::deviation() in their worldDraw/viewportDraw
implementation are subject to dynamic re-tessellations. Depending on the AutoCAD
view settings (certain 3D visual styles with certain properties), AutoCAD can
call the entity's worldDraw/viewportDraw methods during pan/zoom/orbit in order
to retrieve a new tessellation from the entity for the new zoom level.

This sample ARX application contains a custom entity, AcDbThreadedGSEntity, which
is implemented in a way that those dynamic re-tessellations are called from a
GS worker thread, instead of the main thread.

It also defines a custom user command, ADDCUSTOMENTITY, to add this custom entity
to the drawing.

The first step for a custom entity to participate in dynamic re-tessellations
at all is to call AcGiWorldDraw::deviation() in their worldDraw implementation:

Adesk::Boolean AcDbThreadedGSEntity::subWorldDraw(AcGiWorldDraw* pWd)
{
    .
    .
    double d = 0.01 / pWd->deviation(kAcGiMaxDevForCircle, mCenter) * mRadius;

This will make this custom entity's worldDraw method to be conditionally called
during zoom operations; for example, in the 3D visual style "Conceptual".
However, the default behavior is to call the entity's worldDraw method from the
AutoCAD main thread (which may be noticeable to the users in form of a brief lag
during dynamic zoom).

A custom entity, like ThreadedGSEnt, can now tell the graphic system to have its
worldDraw/viewportDraw methods called for the purpose of re-tessellations on a
3DGS worker thread instead. This is done by implementing an override for
subSetAttributes(), and setting the AcGiDrawable::kThreadedWorldDrawViewportDraw
flag in its implementation:

Adesk::UInt32 AcDbThreadedGSEntity::subSetAttributes(AcGiDrawableTraits* pTraits)
{
    return __super::subSetAttributes(pTraits) | AcGiDrawable::kThreadedWorldDrawViewportDraw;
}

However, AcDb itself is not thread-safe. This means that it is important to not
call any AcDb functions or methods during the threaded worldDraw/viewportDraw
callouts. If a custom entity needs some information/data from AcDb for its
worldDraw implementation, we have created an ARX protocol extension mechanism
that allows the custom entity to query (and store) that information on the main
thread, right before we call the threaded worldDraw method. In the worldDraw
implementation, it is now possible (again, using an ARX protocol extension) to
retrieve that previously gathered and stored data in a thread-safe way.

The name of the ARX protocol extension that such a custom entity needs to support
is AcDbEntityParallelDrawPE. It implements a method prepareForParallelDraw().
In that method, it is safe to call any AcDb methods and functions (as this method
will be called on the main thread, right before the threaded GS worldDraw call),
and the AcDbDwgFiler* passed into this method can be used to store any gathered
information:

class AcDbEntityParallelDrawPE_AcDbThreadedGSEntity : public AcDbEntityParallelDrawPE
{
public:
    Adesk::Boolean prepareForParallelDraw(AcDbEntity* pEnt, AcDbDwgFiler* pFiler) const override
    {
        pFiler->writeHardPointerId((AcDbHardPointerId)((AcDbThreadedGSEntity*)pEnt)->getOrCreateLayerIdByName(L"CUSTOMENTITYLAYER"));
        return Adesk::kTrue;
    }

};

.
.

AcDbThreadedGSEntity::desc()->addX(AcDbEntityParallelDrawPE::desc(), new AcDbEntityParallelDrawPE_AcDbThreadedGSEntity());


Then, later, in the threaded worldDraw callout, another new protocol extension,
AcGiContextParallelDrawPE, can be used to get hold of that AcDbDwgFiler*, in order
to retrieve the previously stored data:

Adesk::Boolean AcDbThreadedGSEntity::subWorldDraw(AcGiWorldDraw* pWd)
{
    .
    .
    AcDbDwgFiler *pEntityData = nullptr;
    AcGiContextParallelDrawPE* pe = AcGiContextParallelDrawPE::cast(pWd->context()->isA()->queryX(AcGiContextParallelDrawPE::desc()));
    if (nullptr != pe)
        pEntityData = pe->entityDataFiler(pWd->context());

    if (nullptr != pEntityData) {
        pEntityData->readHardPointerId((AcDbHardPointerId*)&layerId);
    }

There is also one new global helper API function, bool acdbIsGsWorkerThread(),
which can be called during the worldDraw/viewportDraw implementation. This
function will return 'true' when worldDraw is currently called from the GS
worker thread, and 'false' otherwise (when called on the AutoCAD main thread).
