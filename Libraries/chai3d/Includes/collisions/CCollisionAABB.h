//==============================================================================
/*
    Software License Agreement (BSD License)
    Copyright (c) 2003-2014, CHAI3D.
    (www.chai3d.org)

    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:

    * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above
    copyright notice, this list of conditions and the following
    disclaimer in the documentation and/or other materials provided
    with the distribution.

    * Neither the name of CHAI3D nor the names of its contributors may
    be used to endorse or promote products derived from this software
    without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
    FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
    COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
    BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
    LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
    ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE. 

    \author    <http://www.chai3d.org>
    \author    Chris Sewell
    \author    Francois Conti
    \version   3.0.0 $Rev: 1282 $
*/
//==============================================================================

//------------------------------------------------------------------------------
#ifndef CCollisionAABBH
#define CCollisionAABBH
//------------------------------------------------------------------------------
#include "math/CMaths.h"
#include "collisions/CGenericCollision.h"
#include "collisions/CCollisionAABBTree.h"
//------------------------------------------------------------------------------
#include <vector>
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
namespace chai3d {
//------------------------------------------------------------------------------

//==============================================================================
/*!
    \file       CCollisionAABB.h

    \brief    
    <b> Collision Detection </b> \n 
    Axis-Aligned Bounding Box Tree (AABB) - Main Interface.
*/
//==============================================================================

//==============================================================================
/*!
    \class      cCollisionAABB
    \ingroup    collisions

    \brief
    Collision detector - Axis aligned bounding box

    \details
    cCollisionAABB provides methods to create an axis-aligned bounding box 
    collision detection tree, and efficiently detect for any collision between a
    a line segment a the triangles bounded by the tree.
*/
//==============================================================================
class cCollisionAABB : public cGenericCollision
{
    enum cCollisionAABBState
    {
        C_AABB_STATE_TEST_CURRENT_NODE,
        C_AABB_STATE_TEST_LEFT_NODE,
        C_AABB_STATE_TEST_RIGHT_NODE,
        C_AABB_STATE_POP_STACK
    };

    struct cCollisionAABBStack
    {
        int m_index;
        cCollisionAABBState m_state;
    };

    //--------------------------------------------------------------------------
    // CONSTRUCTOR & DESTRUCTOR:
    //--------------------------------------------------------------------------

public:

    //! Constructor of cCollisionAABB.
    cCollisionAABB();

    //! Destructor of cCollisionAABB.
    virtual ~cCollisionAABB();


    //--------------------------------------------------------------------------
    // PUBLIC METHODS:
    //--------------------------------------------------------------------------

public:

    //! Initialize and build the AABB collision tree.
    void initialize(const cTriangleArrayPtr a_triangles, 
                    const double a_radius = 0.0);

    //! Draw the bounding boxes in OpenGL.
    void render(cRenderOptions& a_options);

    //! Return the nearest triangle intersected by the given segment, if any.
    bool computeCollision(cGenericObject* a_object,
                          cVector3d& a_segmentPointA, 
                          cVector3d& a_segmentPointB,
                          cCollisionRecorder& a_recorder, 
                          cCollisionSettings& a_settings);


    //--------------------------------------------------------------------------
    // PROTECTED METHODS:
    //--------------------------------------------------------------------------

protected:

    // Internal recursive method used for building the collision tree.
    int buildTree(const int a_indexFirstNode, const int a_indexLastNode, const int a_depth);


    //--------------------------------------------------------------------------
    // PROTECTED MEMBERS:
    //--------------------------------------------------------------------------

protected:

    //! Radius around triangles.
    double m_radius;

    //! Number of triangles.
    int m_numTriangles;

    //! Pointer to the list of triangles in the mesh.
    cTriangleArrayPtr m_triangles;

    //! List of node.
    std::vector<cCollisionAABBNode> m_nodes;

    //! Index of root node.
    int m_rootIndex;

    //! Maximum depth of tree
    int m_maxDepth;

    //! Stack used during collision detection search.
    std::vector<cCollisionAABBStack> m_stack;
};

//------------------------------------------------------------------------------
} // namespace chai3d
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------
