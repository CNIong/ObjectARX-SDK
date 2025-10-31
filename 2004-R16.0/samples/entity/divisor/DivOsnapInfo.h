//
//
// (C) Copyright 1998-2002 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//
// Note: All template class functions have been inlined in the .h, due to the bug
// described in the MS Knowledge Base Article Q128789:
// BUG: LNK2001 on Member Function When Use Nested Class Template
 
template <int i> class AsdkDivOsnapInfo : public AcDbCustomOsnapInfo
{
public:
    ACRX_DECLARE_MEMBERS(AsdkDivOsnapInfo<i>);

    virtual Acad::ErrorStatus   getOsnapInfo(
                 AcDbEntity*           pickedObject,
				 int                   gsSelectionMark,
				 const AcGePoint3d&    pickPoint,
				 const AcGePoint3d&    lastPoint,
				 const AcGeMatrix3d&   viewXform,
				 AcArray<AcGePoint3d>& snapPoints,
				 AcArray<int>&         geomIdsForPts,
				 AcArray<AcGeCurve3d*>& snapCurves,
				 AcArray<int>&         geomIdsForLines) = 0;
};

template <int i> class AsdkDivOsnapEntityInfo : public AsdkDivOsnapInfo<i>
{ 
public:
    virtual Acad::ErrorStatus   getOsnapInfo(
                 AcDbEntity*           pickedObject,
				 int                   gsSelectionMark,
				 const AcGePoint3d&    pickPoint,
				 const AcGePoint3d&    lastPoint,
				 const AcGeMatrix3d&   viewXform,
				 AcArray<AcGePoint3d>& snapPoints,
				 AcArray<int>&         geomIdsForPts,
				 AcArray<AcGeCurve3d*>& snapCurves,
				 AcArray<int>&         geomIdsForLines){
    // Base definition with no functionality
                    return Acad::eOk;}

};

template <int i> class AsdkDivOsnapCurveInfo : public AsdkDivOsnapInfo< i >
{ 
public:
    virtual Acad::ErrorStatus   getOsnapInfo(
                 AcDbEntity*           pickedObject,
				 int                   gsSelectionMark,
				 const AcGePoint3d&    pickPoint,
				 const AcGePoint3d&    lastPoint,
				 const AcGeMatrix3d&   viewXform,
				 AcArray<AcGePoint3d>& snapPoints,
				 AcArray<int>&         geomIdsForPts,
				 AcArray<AcGeCurve3d*>& snapCurves,
				 AcArray<int>&         geomIdsForLines);
};

template <int i> class AsdkDivOsnapPolylineInfo : public AsdkDivOsnapInfo< i >
{
public:
    virtual Acad::ErrorStatus   getOsnapInfo(
                 AcDbEntity*           pickedObject,
				 int                   gsSelectionMark,
				 const AcGePoint3d&    pickPoint,
				 const AcGePoint3d&    lastPoint,
				 const AcGeMatrix3d&   viewXform,
				 AcArray<AcGePoint3d>& snapPoints,
				 AcArray<int>&         geomIdsForPts,
				 AcArray<AcGeCurve3d*>& snapCurves,
				 AcArray<int>&         geomIdsForLines);

    virtual bool getSnapToSegments(){ return m_bSnapToSegments; }
    virtual void setSnapToSegments( bool bSnapToSegments ){ m_bSnapToSegments = bSnapToSegments; }

private:
    bool m_bSnapToSegments;
};

template <int i>
inline Acad::ErrorStatus
AsdkDivOsnapCurveInfo< i >::getOsnapInfo(
    AcDbEntity*           pickedObject,
    int                   gsSelectionMark,
    const AcGePoint3d&    pickPoint,
    const AcGePoint3d&    lastPoint,
    const AcGeMatrix3d&   viewXform,
    AcArray<AcGePoint3d>& snapPoints,
    AcArray<int>&         geomIdsForPts,
	AcArray<AcGeCurve3d*>& snapCurves,
    AcArray<int>&         geomIdsForLines)
{
    // Generic curve function for all AcDbCurves (except AcDbPolylines)
    AcDbCurve *pCurve;
    if ( NULL != ( pCurve = AcDbCurve::cast( pickedObject )))
    {
        double startParam, endParam;
        AcGePoint3d pt;

        assert( Acad::eOk == pCurve->getStartParam( startParam ));
        assert( Acad::eOk == pCurve->getEndParam( endParam ));
        for ( int j = 1; j < i; j++ )
        {
            assert( Acad::eOk == pCurve->getPointAtParam( startParam + ((endParam - startParam) * j / i ), pt ));
            snapPoints.append( pt );
        }
        if ( pCurve->isClosed() )
        {
            assert( Acad::eOk == pCurve->getStartPoint( pt ));
            snapPoints.append( pt );
        }
    }
    return Acad::eOk;
}

template <int i>
inline Acad::ErrorStatus
AsdkDivOsnapPolylineInfo< i >::getOsnapInfo(
    AcDbEntity*           pickedObject,
    int                   gsSelectionMark,
    const AcGePoint3d&    pickPoint,
    const AcGePoint3d&    lastPoint,
    const AcGeMatrix3d&   viewXform,
    AcArray<AcGePoint3d>& snapPoints,
    AcArray<int>&         geomIdsForPts,
	AcArray<AcGeCurve3d*>& snapCurves,
    AcArray<int>&         geomIdsForLines)
{
    //  Specialised implementation for AcDbPolylines:
    //  Parametrisation of AcDbPolylines is different: each whole numbered parameter appears
    //  at a vertex, so we cannot simply divide by three to get the correct parameter.
    int j;

    AcDbPolyline *pPline;
    if ( NULL != ( pPline = AcDbPolyline::cast( pickedObject )))
    {
        if ( m_bSnapToSegments )
        {
            // Snap to a fraction of each of the segments
            unsigned int numSegs = pPline->numVerts() - 1;
            AcGeLineSeg3d segLn;
            AcGeCircArc3d segArc;
            double startParam, endParam, newParam, dist;
            AcGePoint3d pt;

            for ( unsigned int idx = 0; idx < numSegs; idx++ )
            {
                switch( pPline->segType( idx ))
                {
                case AcDbPolyline::kLine:
                    assert( Acad::eOk == pPline->getLineSegAt( idx, segLn ));
                    startParam = segLn.paramOf( segLn.startPoint() );
                    endParam = segLn.paramOf( segLn.endPoint() );
                    for ( j = 1; j < i; j++ )
                    {
                        snapPoints.append( segLn.evalPoint( startParam + ((endParam - startParam) * j / i )));
                    }
                    break;
                case AcDbPolyline::kArc:
                    assert( Acad::eOk == pPline->getArcSegAt( idx, segArc ));
                    startParam = segArc.paramOf( segArc.startPoint() );
                    endParam = segArc.paramOf( segArc.endPoint() );
                    dist = segArc.length( startParam, endParam );
                    for ( j = 1; j < i; j++ )
                    {
                        newParam = segArc.paramAtLength( startParam, dist * j / i );
                        snapPoints.append( segArc.evalPoint( newParam ));
                    }
                    break;
                default:
                    break;
                }
            }
        }
        else {
            double endParam;
            AcGePoint3d pt;
            double dist;

            assert( Acad::eOk == pPline->getEndParam( endParam ));
            assert( Acad::eOk == pPline->getDistAtParam( endParam, dist ));
            for ( j = 1; j < i; j++ )
            {
                assert( Acad::eOk == pPline->getPointAtDist( dist * j / i, pt ));
                snapPoints.append( pt );
            }
            if ( pPline->isClosed() )
            {
                assert( Acad::eOk == pPline->getStartPoint( pt ));
                snapPoints.append( pt );
            }
        }
    }
    return Acad::eOk;
}
