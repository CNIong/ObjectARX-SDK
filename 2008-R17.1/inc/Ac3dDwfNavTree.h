//  Copyright 2003-2006 by Autodesk, Inc.
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
/////////////////////////////////////////////////////////////////////////////

/// <summary>
/// This class describes the interface that must be implemented by the 
/// (optional) NavTree Publisher. The NavTree publisher controls what will 
/// appear in the navigation tree in the Viewer.
/// If no NavTree publisher is passed in to the Ac3dDwfPublisher, then it
/// will display a "flat" tree listing all the objects with their class names
/// and handles.
///
/// You must create an object that implements the Ac3dDwfNavTreePublisher interface,
/// i.e. an object that derives from Ac3dDwfNavTreePublisher and implements its functions.
/// You will get called after each entity is done publishing its graphics and properties.
/// Use those calls to build a tree of Ac3dDwfNavTreeNode's, based on the data
/// in the Ac3dDwfEntityHeader. That data includes the "Graphics keys" which are
/// used in the DWF to identify the graphics associated with the entity.
/// When all other publishing is done, the Ac3dDwfPublisher will ask you for that
/// tree by asking for its root node: Ac3dDwfNavTreeNode* root();
///
/// </summary>


#ifndef AC3DDWFNAVTREE_H
#define AC3DDWFNAVTREE_H

class Ac3dDwfNavTreeNode : public AcRxObject
{
public:
    /// <summary>
    /// This method is called to get the display name of the tree node
    /// </summary>
    ///
    /// <returns>
    /// returns the name of the tree node.
    /// </returns>
    virtual const AcString&     displayName() const = 0;

    /// <summary>
    /// This method is called to get the graphic identifiers for this tree 
    /// node
    /// </summary>
    ///
    /// <returns>
    /// returns the graphic identifiers for this tree node
    /// </returns>
    virtual const AcArray<long>& keys() const = 0;

    /// <summary>
    /// This method is called to get the number of descendants for this
    /// tree node. Number of descendants includes children, grandchildren
    /// and so on recursively.
    /// </summary>
    ///
    /// <returns>
    /// returns the number of descendants in the tree node.
    /// </returns>
    virtual       int           nDescendants() const = 0;

    /// <summary>
    /// This method is called to get the flag to see if this node should
    /// be displayed as a group or not. The default implementation appends
    /// the number of descendants to the display name
    /// </summary>
    ///
    /// <returns>
    /// returns true if tree node is a group.
    /// </returns>
    virtual       bool          isGroup() const = 0;

    /// <summary>
    /// This method is called to get an array of all the tree node children
    /// of this tree node.
    /// </summary>
    ///
    /// <returns>
    /// returns a array of all the children of this tree node.
    /// </returns>
    virtual const AcArray<const Ac3dDwfNavTreeNode*>& children() const = 0;

    /// <summary>
    /// This method is called to get the flag to see if node is grouped
    /// by block. If this is true, all the descendants graphics will be grouped
    /// together into this tree node, which will have no descendants.
    /// </summary>
    ///
    /// <returns>
    /// returns true if node is grouped by block.
    /// </returns>
    virtual       bool          isBlock() const = 0;
    /// <summary>
    /// Call this method to add a child to the root node. When trying to
    /// register the Ac3dDwfNavTreeNode root in the AcDMMSheetReactorInfo, only
    /// the first client wins. In order for other clients who are registered 
    /// after the first client, to add or remove children, Clients can choose
    /// to implement addChild and removeChild methods.
    /// </summary>
    ///
    /// <param name="root">
    /// a pointer to an Ac3dDwfNavTreeNode object that the clients wants
    /// to add to the navigation tree.
    /// </param>
    ///
    /// <returns>
    /// returns true if successfully adds the Ac3dDwfNavTreeNode node as child
    /// to the root node
    /// </returns>
    ///
    virtual       bool          addChild(const Ac3dDwfNavTreeNode* node) = 0;
    /// <summary>
    /// Call this method to remoave a child from the root node. When trying to
    /// register the Ac3dDwfNavTreeNode root in the AcDMMSheetReactorInfo, only
    /// the first client wins. In order for other clients who are registered 
    /// after the first client, to add or remove children, Clients can choose
    /// to implement addChild and removeChild methods.
    /// </summary>
    ///
    /// <param name="root">
    /// a pointer to an Ac3dDwfNavTreeNode object that the clients wants
    /// to remove from the navigation tree
    /// </param>
    ///
    /// <returns>
    /// returns true if successfully removes the Ac3dDwfNavTreeNode node from
    /// the navigation tree
    /// </returns>
    ///
    virtual       bool          removeChild(const Ac3dDwfNavTreeNode* node) = 0;
};

#endif //AC3DDWFNAVTREE_H
