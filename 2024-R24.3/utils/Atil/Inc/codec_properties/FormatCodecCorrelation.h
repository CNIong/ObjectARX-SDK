///////////////////////////////////////////////////////////////////////////////
//
// (C) Autodesk, Inc. 2007-2011. All rights reserved.
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
///////////////////////////////////////////////////////////////////////////////


#ifndef ATILDEFS_H
#include "AtilDefs.h"
#endif
#ifndef FORMATCODECPROPERTYINTERFACE_H
#include "FormatCodecPropertyInterface.h"
#endif
#ifndef FORMATCODECINCLUSIVEPROPERTYSETINTERFACE_H
#include "FormatCodecInclusivePropertySetInterface.h"
#endif
#ifndef POINT3D_H
#include "Point3d.h"
#endif
#ifndef VECTOR2D_H
#include "Vector2d.h"
#endif

#ifndef FORMATCODECCORRELATION_H
#define FORMATCODECCORRELATION_H

namespace Atil
{
///<summary> This class is for returning correlation meta-data encoded with the
///image file. It is used by applications to place the image data into a world coordinate
///system. </summary>
class FormatCodecCorrelation : public FormatCodecPropertyInterface
{
public:
    enum Units {
        /// <summary> No units</summary>
        kNone,
        /// <summary> Units are unknown</summary>
        kUnknown,
        /// <summary> Units of measure.</summary>
        kMillimeter,
        /// <summary> Units of measure.</summary>
        kCentimeter,
        /// <summary> Units of measure.</summary>
        kMeter,
        /// <summary> Units of measure.</summary>
        kKilometer,
        /// <summary> Units of measure.</summary>
        kInch,
        /// <summary> Units of measure.</summary>
        kFoot,
        /// <summary> Units of measure.</summary>
        kUSSurveyFoot,
        /// <summary> Units of measure.</summary>
        kYard,
        /// <summary> Units of measure.</summary>
        kMile,
        /// <summary> Units of measure.</summary>
        kMicroinches,
        /// <summary> Units of measure.</summary>
        kMils,
        /// <summary> Units of measure.</summary>
        kAngstroms,
        /// <summary> Units of measure.</summary>
        kNanometers,
        /// <summary> Units of measure.</summary>
        kMicrons,
        /// <summary> Units of measure.</summary>
        kDecimeters,
        /// <summary> Units of measure.</summary>
        kDekameters,
        /// <summary> Units of measure.</summary>
        kHectometers,
        /// <summary> Units of measure.</summary>
        kGigameters,
        /// <summary> Units of measure.</summary>
        kAstronomical,
        /// <summary> Units of measure.</summary>
        kLightYears,
        /// <summary> Units of measure.</summary>
        kParsecs,
        /// <summary> Units of measure.</summary>
        kRadians,
        /// <summary> Units of measure.</summary>
        kArcSeconds,
        /// <summary> Units of measure.</summary>
        kDegrees
    };
    
public:
    /// <summary> The destructor. </summary>
    virtual ~FormatCodecCorrelation ();

    /// <summary> The clone method makes a complete copy of any subclassed object.</summary>
    /// <returns> This returns the cloned <c>FormatCodecCorrelation</c> subclass.</returns>
    virtual FormatCodecPropertyInterface* clone () const;
    
    /// <summary> This gets the current insertion point.</summary>
    /// <param name="ptInsertionPt">A reference to a <c>Point3d</c> to receive the 
    /// insertion point.</param>
    virtual void getInsertionPoint (Point3d& ptInsertionPt) const;

    /// <summary> This sets the current insertion point.</summary>
    /// <param name="ptInsertionPt">A const reference to a <c>Point3d</c>.</param>
    virtual void setInsertionPoint (const Point3d& ptInsertionPt);

    /// <summary> This gets the current scale.</summary>
    /// <param name="vecScale">A reference to a <c>Vector2d</c> which will hold the 
    /// scale in X and in Y.</param>
    virtual void getScale (Vector2d& vecScale) const;

    /// <summary> This sets the scale.</summary>
    /// <param name="vecScale">A const reference to a <c>Vector2d</c> which holds the 
    /// scale in X and in Y.</param>
    virtual void setScale (const Vector2d& vecScale);

    /// <summary> This gets the current rotation in radians.</summary>
    /// <param name="dfRotation">A reference to a <c>double</c> which will hold the 
    /// rotation in radians.</param>
    virtual void getRotation (double& dfRotation) const;

    /// <summary> This sets the current rotation in radians.</summary>
    /// <param name="dfRotation">A const reference to a <c>double</c> which holds 
    /// the rotation in radians.</param>
    virtual void setRotation (const double& dfRotation);

    /// <summary> This gets the current resolution.</summary>
    /// <param name="vecResolution">A reference to a <c>Vector2d</c> which will hold 
    /// the resolution in X and in Y.</param>
    virtual void getResolution (Vector2d& vecResolution) const;

    /// <summary> This sets the current resolution.</summary>
    /// <param name="vecResolution">A const reference to a <c>Vector2d</c> which holds 
    /// the resolution in X and in Y.</param>
    virtual void setResolution (const Vector2d& vecResolution);

    /// <summary> This gets the current resolution units.</summary>
    /// <param name="vecResolution">A reference to an <c>Units</c> which be set to the 
    /// units of the image.</param>
    virtual void getResolutionUnits (Units& resUnits) const;

    /// <summary> This sets the current resolution units.</summary>
    /// <param name="vecResolution">A const reference to an <c>Units</c> which is 
    /// the units of the image.</param>
    virtual void setResolutionUnits (Units resUnits);

    /// <summary> This queries the existance of a textual description of the image 
    /// coordinate system.</summary>
    /// <returns> This will return true if there is a textual description available.</returns>
    virtual bool hasCoordinateSystemDescription() const;

    /// <summary> This gets the  textual description of the image coordinate system.</summary>
    /// <param name="sbDescription">A reference to a <c>StringBuffer</c> which be set 
    /// to the image coordinate system description text.</param>
    /// <returns> This will return true if the referenced <c>StringBuffer</c> was correctly set.</returns>
    virtual void getCoordinateSystemDescription (Atil::StringBuffer& sbDescription) const;

    /// <summary> Queuries if the object is correctly set. </summary>
    /// <returns> This will return true if the object has been correctly set up.</returns>
    virtual bool isValid () const;
        
protected:
    /// <summary>Empty constructor.</summary>
    FormatCodecCorrelation ();
    /// <summary>cloning constructor.</summary>
    /// <param name="from">A const reference to a <c>FormatCodecCorrelation</c>
    /// object to copy.</param>
    FormatCodecCorrelation (const FormatCodecCorrelation& from);
    
protected:
    /// <summary>The point of insertion.</summary>
    Point3d mptInsertionPoint;
    /// <summary>The scale of the image.</summary>
    Vector2d mvecScale;
    /// <summary>The rotation of the image.</summary>
    double mdfRotation;
    /// <summary>The resolution of the image.</summary>
    Vector2d mvecResolution;
    /// <summary>The units of the resolution.</summary>
    Units mResUnits;
    /// <summary>The state of the object.</summary>
    bool mbValid;
};
///<summary> A class to return multiple correlation descriptions and give them a
///relative priority or ranking </summary> 
class FormatCodecCorrelationSet : public FormatCodecInclusivePropertySetInterface
{
public:
    /// <summary>Empty constructor.</summary>
    FormatCodecCorrelationSet ();
    /// <summary>Trivial destructor.</summary>
    virtual ~FormatCodecCorrelationSet ();

    /// <summary> Retrieve the correlation property from the provided index </summary>
    /// <param name="nIndex">The index in the set of properties held.</param>
    /// <returns>This returns a <c>FormatCodecCorrelation</c> object pointer from the set.
    /// This pointer is owned by the set and should not be deleted. </param>
    /// <remarks>This class is intended to provide a ranking system for codecs to express
    /// the relative priority among multiple correlation sets it can return. The 
    /// <c>FormatCodecCorrelation objects may or may not be returned independantly from those
    /// contained in the set. It is suggested that Image file codec implementors return the most 
    /// accurate or preferred set of correlation in an independent <c>FormatCodecCorrelation</c> 
    /// in addition the set of all correlations according to rank. This preserves backward 
    /// compatibility for applications that require correlation and acquire it by keyword. </remarks>
    virtual const FormatCodecCorrelation* getCorrelation (int nIndex) const;
};

} // end of namespace Atil

#endif
