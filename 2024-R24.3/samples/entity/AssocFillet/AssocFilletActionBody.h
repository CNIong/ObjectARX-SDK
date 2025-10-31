//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// This is the main header file to look at. It contains declaration of 
// the AssocFilletActionBody class.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcDbGeomRef.h"
#include "acdbassocactionbody.h"
#include "AssocFilletconfig.h"
#pragma pack (push, 8)


// The associative fillet action maintains an AcDbArc entity to be a fillet between
// two input edge subentities of two entities (or whole entities like AcDbLine,
// AcDbCircle, if the entity is just a single curve).
//
// The edge subentities may also be optionally trimmed to the fillet arc. The 
// fillet radius as well as whether to trim the input edge subentities may be 
// controlled by expressions that may reference parameters (AcDbAssocVariables). If 
// the fillet radius is 0.0, no AcDbArc is created (or the existing one is erased).
//
// When an input edge changes, or when the fillet radius expression changes, the 
// associative fillet action automatically re-evaluates the AcDbArc and re-trims 
// the input edges. When the input edges produce multiple intersections, it tries 
// to place the re-evaluated fillet arc at the same intersection as before.
//
// When the two entities that contain the input edges are copied, the associative
// fillet action and the fillet arc entity are also copied. When any of the 
// geometries are erased, the fillet action, as well as the AcDbArc, are erased
//
class AssocFilletActionBody : public AcDbAssocActionBody
{
public:
    ACRX_DECLARE_MEMBERS(AssocFilletActionBody);

    AssocFilletActionBody() {}
    virtual ~AssocFilletActionBody() {}

    //////////////////////////////////////////////////////////////////////////
    //               Associative-fillet-specific protocol 
    //////////////////////////////////////////////////////////////////////////

    // Gets/sets the input edge. The edge may be the whole entity like a 
    // line/arc/circle/ellipse/spline, or an edge subentity of an entity, 
    // such as a segment of a polyline.
    //
    // Index 0 is for the first input edge, index 1 is for the second edge
    //
    AcDbEdgeRef       getInputEdge(int index) const; // Returns an empty AcDbEdgeRef if no input edge
    Acad::ErrorStatus setInputEdge(int index, const AcDbEdgeRef&);

    // Returns geometry of the input edge. The returned curve becomes owned by the
    // caller and the caller is responsible for deleting it when no more needed. 
    // May return nullptr if the curve cannot be obtained
    //
    AcGeCurve3d*      getInputCurve(int index) const; 

    // Gets/sets whether the input edge should be trimmed to the fillet arc.
    // An expression can be used to specify the value. If the expression evaluates
    // to 0, it means false, if it evaluates to non-0, it means 0 
    //
    bool              isTrimInputEdge (int index, AcString& expressionOut = AcString()) const;
    Acad::ErrorStatus setTrimInputEdge(int index, bool yesNo, const AcString& expression = L"");

    // The radius mabe optionally be defined by an expression
    //
    double            getRadius(AcString& expressionOut = AcString()) const;
    Acad::ErrorStatus setRadius(double rad, const AcString& expression = AcString());

    // Access to the fillet AcDbArc entity controlled by the associative fillet action
    //
    AcDbObjectId      getFilletArcId() const;
    AcGeCircArc3d     getFilletArcGeom() const;

    // Creates a new AcDbArc in the BTR of the first input edge, 
    // and makes the action reference it.
    //
    Acad::ErrorStatus createFilletArcEntity();
    Acad::ErrorStatus eraseFilletArcEntity();

    // Utility predicate to check whether the entity is an AcDbArc and is controlled 
    // by an associative fillet action. If yes returns true and the AcDbObjectId of
    // the fillet action
    //
    static bool isFilletArc(const AcDbObjectId& filletArcId, AcDbObjectId& filletActionIdOut);

    // Computes and returns the new geometry of the input edges and of the fillet arc, 
    // based on the geometry and values the action currently depends on. If updateConfig 
    // is true, updates mFilletConfig, otherwise it is a read-only operation.
    // The two returned pInputCurveOut become owned by the caller and the caller 
    // is responsible for deleting them when no more needed
    //
    Acad::ErrorStatus computeNewGeometry(bool updateConfigState, AcGeCurve3d* pInputCurveOut[2], AcGeCircArc3d& filletArcOut);

    // Checks whether the action matches the current geometry, i.e. if evaluating 
    // the action would produce the same geometry as is currently referenced
    //
    bool doesActionMatchCurrentGeometry() const;

    // Pseudo-constructor:
    // - Creates AcDbAssocAction, AssocFilletActionBody, and AcDbArc fillet entity 
    // - Adds them to the database of the first input edge
    // - Adds the AcDbArc to the BTR of the first input edge
    // - Adds the action to the AcDbAssocNetwork at the BTR of the first input edge
    // - Sets up the action and the action body
    //
    static Acad::ErrorStatus createAndPostToDatabase(const AcDbEdgeRef  inputEdge[2],
                                                     const bool         trimInputEdge[2],
                                                     const AcString     trimInputEdgeExpression[2], // May be empty strings
                                                     const AcGePoint3d  pickPoint[2],
                                                     double             radius,
                                                     const AcString&    radiusExpression, // May be an empty string
                                                     AcDbObjectId&      createdActionId);

    //////////////////////////////////////////////////////////////////////////
    //                     AcDbAssocActionBody protocol
    //////////////////////////////////////////////////////////////////////////

    // The main method that must always be overridden. It implements code to
    // update the associative fillet AcDbArc entity from the current input 
    // curves, current radius, and current trim-input-geometry flags.
    //
    // If any of the referenced entities are inaccessible (erased), it erases 
    // the action and the fillet arc. However, if the entites are accessible 
    // but the input entity does not provide the requested edge subentity, or 
    // the fillet cannot be calculated, the action evaluation fails, an error 
    // is reported, but the action is not erased
    //
    virtual void evaluateOverride() override;

    // If both input edges have been selected to be cloned, also clone 
    // the fillet action and the fillet arc entity
    //
    virtual Acad::ErrorStatus addMoreObjectsToDeepCloneOverride(AcDbIdMapping&, 
                                                                AcDbObjectIdArray& additionalObjectsToClone) const override;
    virtual Acad::ErrorStatus postProcessAfterDeepCloneOverride(AcDbIdMapping&) override;

    virtual Acad::ErrorStatus transformActionByOverride(const AcGeMatrix3d&) override;

    //////////////////////////////////////////////////////////////////////////
    //                         AcDbObject protocol
    //////////////////////////////////////////////////////////////////////////

    // If hasAnyErasedOrBrokenDependencies() returns true, erases the action,
    // but leaves the fillet arc around
    //
    virtual Acad::ErrorStatus audit(AcDbAuditInfo*) override;

    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler*) const override;     
    virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler*) override;      
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler*) const override;     
    virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler*) override;

private:
    // Configuration of the intersection point, used for determining 
    // at which intersection among possible multiple intersections to 
    // place the fillet arc, and in which of the four quadrants around
    // the intersection to place it
    //
    AssocFilletConfig mFilletConfig;

    // We use an AcDbAssocDependency to reference the fillet AcDbArc entity
    //
    AcDbObjectId mFilletArcDepId; 
};

#pragma pack (pop)
