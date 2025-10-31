       ObjectARX Developer's Guide Sample Code Table of Contents
 (C) Copyright 1998 by Autodesk, Inc.

This directory (and some of the samples in the "samples" directory)
contains code to build ObjectARX applications that use the sample code from the 
ObjectARX Developer's Guide.  Users can run these ObjectARX applications to 
verify the behavior of sample code found in the Developer's Guide.
This file provides a quick correlation between the pieces of sample code
shown in the ObjectARX Developer's Guide and the actual source files they come
from.  Each sample in the manual has a source file that is part of a
sample program that can be built and run.

In the listing below,  the samples are listed in the order they are found
in the Developer's Guide.  All paths listed below are relative to the ObjectARX
installation directory.


description                                       file name
-------------------------------------------------------------\
ch. 0
No code samples in this chapter

ch. 1
No code samples in this chapter
                        
ch. 2
createLine()                                      docsamps\ents\ents.cpp
createCircle()                                    docsamps\ents\ents.cpp
createNewLayer()                                  docsamps\ents\ents.cpp
changeColor()                                     docsamps\ents\ents.cpp
createGroup()                                     docsamps\ents\ents.cpp

ch. 3
initApp()/unloadApp()                             docsamps\custobj\custobj.cpp
createCircle() with error checking                docsamps\entswerr\entswerr.cpp
createNewLayer() with error checking              docsamps\entswerr\entswerr.cpp

ch. 4
createDwg() & readDwg()                           docsamps\testdb\testdb.cpp
Long Transaction sample                           docsamps\longtrans\AsdkLongTransSample.cpp

ch. 5
selectEntity()                                    docsamps\specials\getobjid.cpp
printXdata()/addXdata()                           docsamps\xdata\xdata.cpp
createXrecord()/listXrecord()                     docsamps\xtsndict\arx\xtsndict.cpp
createXrecord()/listXrecord()                     docsamps\xtsndict\ads\xtsndict.c

ch. 6
subentity highlighting sample program             docsamps\hilight\hilight.cpp
createInsert()/hilitInsert()                      sample\polysamp\hilit.cpp
createLine()                                      docsamps\ents\ents.cpp
makeABlock()                                      docsamps\complex\complex.cpp
defineBlockWithAttributes()                       docsamps\complex\complex.cpp
addBlockWithAtributes()                           docsamps\complex\complex.cpp
printAll()                                        docsamps\complex\complex.cpp
createPolyline()                                  docsamps\complex\complex.cpp
iterate()                                         docsamps\pliniter\pliniter.cpp
projectEllipse()/offsetEllipse()                  docsamps\curve\curve.cpp

ch. 7
addLayer()                                        docsamps\tablerec\tablerec.cpp
iterateLinetypes()                                docsamps\tbliter\tbliter.cpp
groups()/makegroup()/removeAllButLines()          docsamps\groups\groups.cpp
createDictionary()                                docsamps\custobj\custobj.cpp
iterateDictionary()                               docsamps\custobj\custobj.cpp
createXrecord()/listXrecord()                     docsamps\xrecord\arx\xrecord.cpp
refEditApiExample()

ch. 8
AcUi and AdUi MFC Extensions sample               docsamps\mfcsamps\acuisample\AsdkAcUiDialogSample.cpp
                                                  docsamps\mfcsamps\acuisample\AsdkAcUiSample.cpp
                                                  docsamps\mfcsamps\acuisample\StdAfx.cpp

Dynamic library MFC with ARX sample               docsamps\mfcsamps\dynamic\arxmfctmpl.cpp
                                                  docsamps\mfcsamps\dynamic\modal.cpp
                                                  docsamps\mfcsamps\dynamic\stdafx.cpp

ch. 9
No code samples in this chapter

ch. 10
No code samples in this chapter

ch. 11
ACRX macro expanded                               docsamps\specials\acrxmac.txt

ch. 12
dwgOutFields()                                    sample\polysamp\poly.cpp
dwgInFields()                                     sample\polysamp\poly.cpp
dxfOutFields()                                    sample\polysamp\poly.cpp
dxfInFields() order independent                   sample\polysamp\poly.cpp
dxfInFields() order dependent                     sample\polysamp\poly.cpp
  (the order dependent version of dxfInFields() is
  #ifdef'd on ORDER_DEPENDENT)
makeOwner()                                       docsamps\specials\makeownr.cpp
custom ownership hierarchy sample program         docsamps\ownrshp\arx\ownrshp.cpp
AsdkPoly::setNumSides()                           docsamps\sample\polysamp\poly.cpp
AsdkPoly::applyPartialUndo()                      docsamps\sample\polysamp\poly.cpp
interobject references sample program             docsamps\referenc\referenc.cpp
custom database object sample program             docsamps\custobj\custobj.cpp

ch. 13
getOsnapPoints()                                  sample\polysamp\poly.cpp
getGripPoints()                                   sample\polysamp\poly.cpp
moveGripPointsAt()                                sample\polysamp\poly.cpp
getStretchPoints()                                sample\polysamp\poly.cpp
moveStretchPointsAt()                             sample\polysamp\poly.cpp
transformBy()                                     sample\polysamp\poly.cpp
getTransformedCopy()                              sample\polysamp\poly.cpp
intersectWith() (both versions)                   sample\polysamp\poly.cpp
AcEdJig sample program                            docsamps\elipsjig\elipsjig.cpp

ch. 14
No code samples in this chapter

ch. 15
database reactor sample program                   docsamps\dbreact\dbreact.cpp
getting/using reactor objectId                    sample\notfsamp\notfsamp.cpp
persistent reactor sample program                 docsamps\persreac\persreac.cpp

ch. 16
An MDI-Aware example                              docsamps\dbreact\dbreactmdi.cpp

ch. 17
transactCommand() and other functions             sample\polysamp\transact.cpp

ch. 18
cloneSameOwnerObjects()                           docsamps\deepclon\deepclon.cpp
cloneDiffOwnerObjects()                           docsamps\deepclon\deepclon.cpp
cloning objects in NOD                            docsamps\clonenod\clonenod.cpp
standard deepclone() implementation               sample\polysamp\poly.cpp
standard wblockclone() implementation             sample\polysamp\poly.cpp
otherWblock() reactor notification                docsamps\othrwblk\othrwblk.cpp
beginDeepCloneXlation() notification              docsamps\clonreac\clonereac.cpp

ch. 19
initialization and addX calls                     docsamps\tempapp\tempapp.cpp
calling protocol extension functions              docsamps\specials\xcall.cpp
ACRX_X_CALL useage                                docsamps\tempapp\tempapp.cpp
protocol extension sample program                 docsamps\tempapp\tempapp.cpp

ch. 20
No code samples in this chapter

ch. 21
custom object snap modes
input context events                              sample\inputpoint\Reactor.cpp (slightly different form than in Developer's Guide)
input point filter and monitor                    sample\inputpoint\Filter.cpp (slightly different form than in Developer's Guide)
                                                  sample\inputpoint\Monitor.cpp (slightly different form than in Developer's Guide)

ch. 22
Profile Manager sample                            docsamps\profilesamp\AsdkProfileSample.cpp

ch. 23
Accessing COM/ActiveX Automation from MFC in ARX  docsamps\comsamps\AsdkMfcComSamp\acad1.cpp
                                                  docsamps\comsamps\AsdkMfcComSamp\AsdkMfcComSamp.cpp
                                                  docsamps\comsamps\AsdkMfcComSamp\StdAfx.cpp
                                                  
Accessing COM/ActiveX Automation in ARX           docsamps\comsamps\AsdkPlainComSamp\AsdkPlainComDocSamp.cpp
                                                  
Making an COM Wrapper for an AcDbObject           docsamps\comsamps\AsdkSquareWrapper\AsdkSquareWrap\AsdkSquareLib.cpp
                                                  docsamps\comsamps\AsdkSquareWrapper\AsdkSquareWrap\AsdkSquareWrapper.cpp
                                                  docsamps\comsamps\AsdkSquareWrapper\AsdkSquareWrap\StdAfx.cpp
                                                  docsamps\comsamps\AsdkSquareWrapper\Square\squarent.cpp
                                                  docsamps\comsamps\AsdkSquareWrapper\Square\squareui.cpp

ch. 24
AutoCAD DesignCenter Sample                       docsamps\designcenter\AsdkDcContent.cpp
                                                  docsamps\designcenter\AsdkDesignCenterSamp.cpp
                                                  docsamps\designcenter\StdAfx.cpp

ch. 25
No code samples in this chapter

ch. 26
worldDraw() (subentity traits)                    docsamps\acgismps\traits\traits.cpp
worldDraw() (mesh generation)                     docsamps\acgismps\mesh\mesh.cpp
worldDraw() (shell generation)                    docsamps\acgismps\shell\shell.cpp
worldDraw() (textstyle use)                       docsamps\acgismps\textstyl\textstyl.cpp
getTextStyle() (AcDb->AcGi style)                 docsamps\acgismps\stylcvrt\stylcvrt.cpp
viewportDraw() (transforms)                       docsamps\acgismps\coordsys\coordsys.cpp
worldDraw/viewportDraw() (showing use of                        
  getNumPixelsInUnitSquare)                       docsamps\acgismps\viewgeom\viewgeom.cpp
viewportDraw() (window coords)                    docsamps\acgismps\icon\icon.cpp
worlDraw()/viewportDraw() (arc tesselation)       docsamps\acgismps\teselate\teselate.cpp

ch. 27
No code samples in this chapter

ch. 28
No code samples in this chapter

Appendix A
ADS to ADS-Rx sample program                      docsamps\fact\fact.cpp

Appendix B
No code samples in this chapter