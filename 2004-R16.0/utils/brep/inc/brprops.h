#ifndef AC_BRPROPS_H
#define AC_BRPROPS_H 1
// (C) Copyright 1998-1999 by Autodesk, Inc.
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

