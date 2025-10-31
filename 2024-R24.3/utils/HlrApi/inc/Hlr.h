//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//
//-----------------------------------------------------------------------------
//----- Hidden Line Removal API
//----- by Cyrille Fauvel & Phil Holcombe
//----- Autodesk Developer Consulting Group
//----- June 10th, 1999
//-----------------------------------------------------------------------------
#pragma once

#include <geintarr.h>
#include <dbmain.h>

//-----------------------------------------------------------------------------
#ifdef _HLR_EXPORT_
#define EXP_IMP __declspec(dllexport)
#else
#define EXP_IMP
#endif

#pragma warning (disable: 4251)

#define AsdkHlrApiServiceName _T(/*NOXLATE*/"ASDK_HLR_API_SERVICES")

//-----------------------------------------------------------------------------
enum AsdkHlrControl {
	kProject			=0x0001, //----- Should the curves be projected to a plane?
	kShowAll			=0x0002, //----- Should all curves be returned, or just visible ones?
	kEntity				=0x0004, //----- Is it required to return the entity which caused
								 //----- a particular curve to be created?
	kBlock				=0x0008, //----- Are the objectIds for the generating entities
								 //----- required, including those of the nested blocks?
	kSubentity			=0x0010, //----- Should the subenty information be returned for solids or graphic
								 //----- primitives?
	kHideTangents		=0x0020, //----- Should tangent edges be suppressed?
	kCleanup			=0x0040, //----- Should stored data be cleaned after use?
	kIsolines			=0x0080, //----- Should isolines be shown (same as would be seen in AutoCAD)?
	kUnite				=0x0100, //----- Should the entities be united before hidden lines?
								 //----- Will be much slower, but more accurate for intersecting entities.
	kReuse				=0x0200, //----- Should the algorithm use the data which were created previously?
	kProgress			=0x0400, //----- Should the progress & abort callbacks be called?
	kHandlePoints		=0x0800, //----- Should we show single points (requires bit more processing)?
	kProcessAll			=0x1000, //----- Process all entities without looking at their layer state
								 //----- on which they lie on.
	kHonorInternals		=0x2000, //----- Should we process internal edges' visibility (i.e. AcDbPolyFaceMesh /
								 //----- ACIS internal common edge / custom entity mesh/shell promitives)
								 //----- Will be much slower, but more accurate for internal edges' visibility
								 //----- processing.
	kMeshSilhouettes	=0x4000, //----- Should we generate silhouettes for AcDbPolyFaceMesh
	kSingleCacheVp		=0x8000, //----- The HLR object cache is uniq for all viewports
	kNoScale	       =0x10000  //----- Don't scale geometry before calling hide()
} ;

//-----------------------------------------------------------------------------
class EXP_IMP AsdkHlrData {

public:
	enum Visibility {
		kVisible,			//----- Not hidden by anything
		kHidden,			//----- Hidden by a face
		kOccluded,			//----- Hidden by another edge
		kInternallyHidden,	//----- Hidden because of entity internal visibility of a edge
							//----- (i.e. AcDbPolyFaceMesh / ACIS internal common edge)
		kUndefined			//----- Visibility not yet defined
	} ;

protected:
	AcDbEntity *m_pEntity ;			//----- Entity which generated the curve

	AcDbObjectIdArray m_objectIds ;	//----- Chain of ObjectIds which generated the curve
	AcDbSubentId m_subentId ;		//----- Which edge or face created this curve

	Visibility m_visibility ;		//----- Is the curve visible? etc.
	Visibility m_hlrVisibility ;	//----- In case m_visibility == kInternallyHidden,
									//----- this one tells the HLR visibility output in case it was not hidden internally
	AcDbEntity *m_pResultEntity ;	//----- Resulting entity (usually a curve)

public:
	AsdkHlrData () : m_pEntity (NULL), m_visibility(kUndefined), m_hlrVisibility(kUndefined), m_pResultEntity(NULL) {}
	virtual ~AsdkHlrData () {
		if ( m_pResultEntity && m_pResultEntity->objectId () == AcDbObjectId::kNull )
			delete m_pResultEntity ;
	}

	//----- Corresponding setting functions not anticipated for use by applications
	void setEntity (AcDbEntity *pEnt)
		{ if ( pEnt != NULL ) m_pEntity =pEnt ;	}
	void setObjectIds (AcDbObjectIdArray id)
		{ m_objectIds =id ; }
	void setResultEntity (AcDbEntity *pResultEnt)
		{ m_pResultEntity =pResultEnt ; }
	void setVisibility (Visibility visibility)
		{ m_visibility =visibility ; }
	void setHlrVisibility (Visibility visibility)
		{ m_hlrVisibility =visibility ; }
	void setSubentId (AcDbSubentId subentId)
		{ m_subentId =subentId ; }

	//----- Gets entity causing this curve
	AcDbEntity *getEntity ()
		{ return (m_pEntity) ; }
	//----- Gets ObjectIds causing this curve
	AcDbObjectIdArray &getObjectIds ()
		{ return (m_objectIds) ; }
	//----- Curve itself. This is the actual curve stored by the class.
	//----- !In case of point, the resulting entity would be a point and not a curve!
	AcDbEntity *getResultEntity ()
		{ return (m_pResultEntity) ; }
	//----- Obtains visiblity of this curve
	Visibility getVisibility ()
		{ return (m_visibility) ; }
	Visibility getHlrVisibility ()
		{ return (m_hlrVisibility) ; }
	//----- Obtains the subentities of the curve
	AcDbSubentId getSubentId ()
		{ return (m_subentId) ; }
} ;

//-----------------------------------------------------------------------------
class AsdkHlrEngine ;

class EXP_IMP AsdkHlrCollector {

protected:
	AcArray<AcDbEntity *> mEntities ;	//----- Memory input entity
	bool mbDeleteInDestructor ;			//----- Indicates if the collector object is responsible to destroy
										//----- all memory objects
	AcDbObjectIdArray mEntityIds ;		//----- Database Resident input entity

public:
	AcArray<AsdkHlrData *> mOutputData ;//----- AsdkHlrData output array (contains the curves and data)

public:
	AsdkHlrCollector () : mbDeleteInDestructor(false) {}
	AsdkHlrCollector (AcDbObjectIdArray &ids) ;
	AsdkHlrCollector (AcArray<AcDbEntity *> &entities, bool deleteInDestructor =false) ;
	AsdkHlrCollector (AsdkHlrCollector &collector) ;

	virtual ~AsdkHlrCollector () ;

	bool getDeleteState ()
		{ return (mbDeleteInDestructor) ; }
	void setDeleteState (bool bFlag)
		{ mbDeleteInDestructor =bFlag ; }

	AcArray<AcDbEntity *> &getInputEntities ()
		{ return (mEntities) ; }
	AcDbObjectIdArray &getInputEntityIds ()
		{ return (mEntityIds) ; }

	void addEntity (AcDbEntity *pEnt) ;
	void addEntities (AcArray<AcDbEntity *> &pEnts) ;
	void addEntity (AcDbObjectId id) ;
	void addEntities (AcDbObjectIdArray &ids) ;
	
	void removeEntity (AcDbEntity *pEnt) ;
	void removeEntities (AcArray<AcDbEntity *> &pEnts) ;
	void removeEntity (AcDbObjectId id) ;
	void removeEntities (AcDbObjectIdArray &ids) ;

	void clear () ;

protected:
	//----- Do not call those two methods in your program
	//----- They are called by the 'AsdkHlrEngine' to open/close DBR entities
	virtual int initialize (AcArray<AcDbEntity *> &collection) ;
	virtual void close (AcArray<AcDbEntity *> &collection) ;

	friend class AsdkHlrEngine ;
} ;

//-----------------------------------------------------------------------------
typedef void (*_AbortCallbackFct) (bool *abort) ;
typedef void (*_ProgressCallbackFct) (int percent_completed) ;

class EXP_IMP AsdkHlrEngine {

protected:
	AcDbViewport *mpViewport ;
	int mnControl ;
	_AbortCallbackFct mpAbortCallbackFct ;
	_ProgressCallbackFct mpAcisConvertionProgressCallbackFct ;
	_ProgressCallbackFct mpAhlProgressCallbackFct ;
	_ProgressCallbackFct mpAcadConvertionProgressCallbackFct ;
	
public:
	AsdkHlrEngine (int ctrl =kShowAll | kEntity | kBlock | kSubentity | kReuse) ;
	AsdkHlrEngine (AcDbObjectId id, int ctrl =kShowAll | kEntity | kBlock | kSubentity | kReuse) ;
	AsdkHlrEngine (AcDbViewport *pViewport, int ctrl =kShowAll | kEntity | kBlock | kSubentity | kReuse) ;
	AsdkHlrEngine (AcGePoint3d &viewTarget, AcGeVector3d &viewDirection, int ctrl =kShowAll | kEntity | kBlock | kSubentity | kReuse) ;

	virtual ~AsdkHlrEngine () ;

	Acad::ErrorStatus run (AsdkHlrCollector &collector) ;

	void setAbortCallback (_AbortCallbackFct fct) ;
	
	void setAcisConversionProgressCallBack (_ProgressCallbackFct fct) ;
	void setAhlProgressCallBack (_ProgressCallbackFct fct) ;
	void setAcadConversionProgressCallBack (_ProgressCallbackFct fct) ;
	
	static void cleanHlrCache () ;
	static void cleanHlrCache (AcDbEntity *pEnt, AcDbViewport *pVp =NULL) ;
	static void cleanHlrCache (AcDbEntity *pEnt, AcGePoint3d viewTarget, AcGeVector3d viewDir) ;
} ;

//-----------------------------------------------------------------------------
extern "C" void *createBodyFromTriangles (AcGePoint3dArray &pts, AcGeIntArray &indices) ;
