CLONEMSG sample Readme.txt

 (C) Copyright 2001 by Autodesk, Inc.

This example shows how to build the relationship between a custom
entity in model space and a custom AcDbObject stored somewhere else
in the drawing database (either NOD or EXD or just by using
AcDbDatabase::addAcDbObject). It also shows and how to maintain
this relationship during save, open, wblock, insert, copy, block
and explode operations.

CLONEMSG creates a custom entity and a custom object. The entity
stores as a member variable the Object Id to the custom object.
The custom entity itself is stored in model space.

The kind of object-id relationship betweeen entity and object can
be defined by the preprocessor-definition HARDPOINTER. If defined, the
entity keeps an AcDbHardPointerId to the object; otherwise, it keeps
an AcDbSoftPointerId.

The way the object itself is stored can be influenced by the
preprocessor-definition NOD. If defined, the object is stored
in a private dictionary in the Named Objects Dictionary (NOD).

namedobjects
 |
  -> mydict
      |
       -> myentry

If there is more than one object, the namekey of the first entry is
"MYENTRY". All further entries get an anonymous namekey in the
"MYDICT" dictionary.

If NOD is not defined, the object is stored in a private
dictionary in the Extension Dictionary of the custom entity:

custom entity
 |
  -> extension dictionary
     |
      -> mydict
          |
           -> myentry

Since there is never more than one entry in the dictionary attached
to each individual custom entity, we don't have to deal with
multiple anonymous entries here.

If you want to have these relationships maintained during
wblock, insert, explode or copy operations you have to install a
beginDeepCloneXlation callback. In the attached example, this can be
done by defining the macro XLATE.

In addition, this example shows a third way of storing an associated 
object in the drawing database. You can get this if you define the
macro DIRECT. In that case, we just call

acdbHostApplicationServices()->workingDatabase()->addAcDbObject(myObj)

to add the object directly to the database (as opposed to adding it to
a container). As a result of addAcDbObject, the object belongs to
the database. It has a unique object id and a unique handle. The
difference is that this object is not owned by someone. That's why 
- in that case - the custom entity stores a AcDbHardOwnershipId to
the object. The object is therefore owned by the custom entity. This 
has the advantage that filing operations such as save, open,wblock,
insert, explode and copy works automatically; the custom object is
always copied with the entity. So you don't need to define XLATE in
the case of DIRECT, and in fact XLATE is ignored if DIRECT is defined.


A custom entity plus its object can be added to the drawing with the
command ADDOBJECTS.

Here are some example of DEFINEs:
-dXLATE;NOD              SoftPointer ID to object in NOD
-dXLATE                  SoftPointer ID to object in EXD
-dXLATE;HARDPOINTER      HardPointer ID to object in EXD
-dXLATE;HARDPOINTER;NOD  HardPointer ID to object in NOD
-dDIRECT                 HardOwnership ID to object (no container)

