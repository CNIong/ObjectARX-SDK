#ifndef AC_BRPROPS_H
#define AC_BRPROPS_H 1
//
//  Copyright 2023 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// The AcBrMassProps struct contains the volume, the mass (equal
// to the volume unless the density is specified as anything other
// than unity), the centroid (centre of gravity), the radii of
// gyration (square root of the moments of inertia divided by
// the rigid body mass), the rigid body moments of inertia (mass
// times the square of the axial radius), the products of inertia
// (mass times the distance from the centroid to the yz plane
// times the distance from the centroid to the xz plane), the
// principal moments at the centroid (derived from the products
// of inertia) and the principal axes at the centroid.


#include "adesk.h"
#include "gepnt3d.h"
#include "gevec3d.h"


struct AcBrMassProps
{
	double			mVolume; // 2nd field in AmiMassProps
	double			mMass; // 1st field in AmiMassProps
	AcGePoint3d		mCentroid; // 5th field in AmiMassProps
	double			mRadiiGyration[3]; // 3rd field in AmiMassProps
	double			mMomInertia[3]; // 7th field in AmiMassProps
	double			mProdInertia[3]; // 8th field in AmiMassProps
	double			mPrinMoments[3]; // 4th field in AmiMassProps
	AcGeVector3d	mPrinAxes[3]; // 6th field in AmiMassProps
};


#endif

