#ifndef AD_IDGRAPH_H
#define AD_IDGRAPH_H 1
//
// (C) Copyright 1999 by Autodesk, Inc. 
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
// ========= idgraph.h:  AcDbObjectIdGraph classes ================ 
//
//    This header defines classes:
//
//	AcDbObjectIdGraph - a derived class for representing object references
//	AcDbObjectIdGraphNode - each node represents an object id
//
//

#include "graph.h"
#include "dbidmap.h"

#pragma pack (push, 8)

// =====================================
//      Object Id Graph Classes
// =====================================


class AcDbObjectIdGraphNode : public AcDbGraphNode
{
public:
    AcDbObjectIdGraphNode(const AcDbObjectId id);
    virtual ~AcDbObjectIdGraphNode();

    AcDbObjectId           id           () const;

private:

    AcDbObjectId        mId;
};


class AcDbObjectIdGraph : public AcDbGraph
{
public:
    AcDbObjectIdGraph();
    virtual ~AcDbObjectIdGraph();

    Acad::ErrorStatus       addNode     (AcDbObjectIdGraphNode *);
    Acad::ErrorStatus       delNode     (AcDbObjectIdGraphNode *);
    AcDbObjectIdGraphNode*  findNode    (const AcDbObjectId) const;
    AcDbObjectIdGraphNode*  idNode      (int idx) const;


private:
    AcDbIdMapping       mIdNodeMap;
};
// =====================================
//      Inline methods
// =====================================

// AcDbObjectIdGraphNode inlines

inline AcDbObjectId AcDbObjectIdGraphNode::id() const
    {return mId; }


// AcDbObjectId inlines ...

inline AcDbObjectIdGraphNode* AcDbObjectIdGraph::idNode(int idx) const
    { return (AcDbObjectIdGraphNode*)node(idx); }

#pragma pack (pop)

#endif

