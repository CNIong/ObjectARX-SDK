
//////////////////////////////////////////////////////////////////////////////
//
// Copyright © 2007-2009 by Autodesk, Inc. 
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

#pragma once
#pragma pack (push, 8)

// Forward class declarations.
//
class AcImpConstraintGroupNode;
class AcDbImpAssoc2dConstraintGroup;
class AcDbAssoc2dConstraintGroupUtil;

// typedef
//
typedef Adesk::UInt32 AcConstraintGroupNodeId;

/// <summary> <para>
/// This class represents a node owned by AcDbAssoc2dConstraintGroup.
/// Usually a node is connected with multiple other nodes and the connection  
/// between two nodes is not directed. 
/// </para> <para>
/// A AcConstraintGroupNode object should always be created and deleted through
/// higher level APIs and the memory pointed by it is internal held and should 
/// never be released by user directly.
/// </para>
/// </summary>
///
class ACDB_PORT AcConstraintGroupNode : public AcRxObject, 
                                        public AcHeapOperators
{
public:
  ACRX_DECLARE_MEMBERS(AcConstraintGroupNode);

  /// <summary> Default destructor. </summary>
  ///
  virtual ~AcConstraintGroupNode();

  /// <summary> Null node id </summary>
  ///
  enum GroupNodeId
  {
    kNullGroupNodeId = 0
  };

  /// <summary> 
  /// Every AcConstraintGroupNode object in a AcDbAssoc2dConstraintGroup has
  /// a unique node id which may be cached by the client applications. 
  /// </summary>
  /// <returns> AcConstraintGroupNodeId. </returns>
  ///
  AcConstraintGroupNodeId nodeId() const;

  /// <summary> 
  /// This function returns the AcDbObjectId of its owning AcDbAssoc2dConstraintGroup. 
  /// If this node has not been added into a AcDbAssoc2dConstraintGroup, AcDbObjectId::kNull
  /// is returned. 
  /// </summary>
  /// <returns> AcDbObjectId. </returns>
  ///
  AcDbObjectId owningConstraintGroupId()const;

protected:

  /// <summary> Protected default constructor. </summary>
  /// 
  AcConstraintGroupNode();

  AcImpConstraintGroupNode* mpImpGroupNode;
  friend class AcDbImpAssoc2dConstraintGroup;
  friend class AcDbAssoc2dConstraintGroupEvalHelper;
  friend class AcDbAssoc2dConstaintGroupCloningHelper;
};

#pragma pack (pop)
