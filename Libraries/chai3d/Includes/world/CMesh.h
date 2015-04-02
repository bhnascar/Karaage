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
    \author    Francois Conti
    \author    Dan Morris
    \author    Chris Sewell
    \version   3.0.0 $Rev: 1304 $
*/
//==============================================================================

//------------------------------------------------------------------------------
#ifdef _MSVC
#pragma warning (disable : 4786)
#endif
//------------------------------------------------------------------------------
#ifndef CMeshH
#define CMeshH
//------------------------------------------------------------------------------
#include "world/CGenericObject.h"
#include "materials/CMaterial.h"
#include "materials/CTexture2d.h"
#include "graphics/CColor.h"
//------------------------------------------------------------------------------
#include <vector>
#include <list>
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
namespace chai3d {
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
class cWorld;
//------------------------------------------------------------------------------

//==============================================================================
/*!
    \file       CMesh.h

    \brief 
    <b> Scenegraph </b> \n 
    Virtual Mesh.
*/
//==============================================================================
//------------------------------------------------------------------------------

//! Array of vertices.
class cVertexArray;
typedef std::shared_ptr<cVertexArray> cVertexArrayPtr;

//! Array of triangles.
class cTriangleArray;
typedef std::shared_ptr<cTriangleArray> cTriangleArrayPtr;
//------------------------------------------------------------------------------

//==============================================================================
/*!    
    \class      cMesh
    \ingroup    scenegraph

    \brief
    3D Mesh object

    \details
    cMesh represents a collection of vertices, triangles, materials,
    and texture properties that can be rendered graphically and haptically.
*/
//==============================================================================
class cMesh : public cGenericObject
{
    //--------------------------------------------------------------------------
    // CONSTRUCTOR & DESTRUCTOR:
    //--------------------------------------------------------------------------
    
public:

    //! Constructor of cMesh.
    cMesh(cMaterialPtr a_material = cMaterialPtr());

    //! Destructor of cMesh.
    virtual ~cMesh();


    //--------------------------------------------------------------------------
    // PUBLIC METHODS - GENERAL
    //--------------------------------------------------------------------------

public:

    //! Create a copy of itself.
    virtual cMesh* copy(const bool a_duplicateMaterialData = false,
                        const bool a_duplicateTextureData = false, 
                        const bool a_duplicateMeshData = false,
                        const bool a_buildCollisionDetector = false);


    //--------------------------------------------------------------------------
    // PUBLIC METHODS - VERTICES
    //--------------------------------------------------------------------------

public:


    //! Create a new vertex and add it to the vertex list.
    unsigned int newVertex(const double a_x = 0.0, 
                           const double a_y = 0.0, 
                           const double a_z = 0.0,
                           const double a_normalX = 1.0, 
                           const double a_normalY = 0.0, 
                           const double a_normalZ = 0.0,
                           const double a_textureCoordX = 0.0,
                           const double a_textureCoordY = 0.0,
                           const double a_textureCoordZ = 0.0);

    //! Create a new vertex and add it to the vertex list.
    unsigned int newVertex(const cVector3d& a_pos, 
                           const cVector3d& a_normal = cVector3d(1,0,0),
                           const cVector3d& a_textureCoord = cVector3d(0,0,0),
                           const cColorf& a_color = cColorf(0,0,0,1));

    //! Read the number of stored vertices.
    inline unsigned int getNumVertices() const { return (unsigned int)(m_vertices->getNumVertices()); }

    
    //--------------------------------------------------------------------------
    // PUBLIC METHODS - TRIANGLES
    //--------------------------------------------------------------------------

public:

    //! Create a new triangle by passing vertex indices.
    unsigned int newTriangle(const unsigned int a_indexVertex0,
                             const unsigned int a_indexVertex1, 
                             const unsigned int a_indexVertex2);

    //! Create a new triangle and three new vertices by passing vertex positions, normals and texture coordinates.
    unsigned int newTriangle(const cVector3d& a_vertex0 = cVector3d(0,0,0), 
                             const cVector3d& a_vertex1 = cVector3d(0,0,0),
                             const cVector3d& a_vertex2 = cVector3d(0,0,0),
                             const cVector3d& a_normal0 = cVector3d(1,0,0), 
                             const cVector3d& a_normal1 = cVector3d(1,0,0),
                             const cVector3d& a_normal2 = cVector3d(1,0,0),
                             const cVector3d& a_textureCoord0 = cVector3d(0,0,0), 
                             const cVector3d& a_textureCoord1 = cVector3d(0,0,0),
                             const cVector3d& a_textureCoord2 = cVector3d(0,0,0),
                             const cColorf& a_colorVertex0 = cColorf(0,0,0,1),
                             const cColorf& a_colorVertex1 = cColorf(0,0,0,1),
                             const cColorf& a_colorVertex2 = cColorf(0,0,0,1));

    //! Remove a triangle from my triangle array.
    bool removeTriangle(const unsigned int a_index);

    //! Read the number of stored triangles.
    unsigned int getNumTriangles();

    //! Clear all triangles and vertices of mesh.
    void clear();


    //--------------------------------------------------------------------------
    // PUBLIC METHODS - GRAPHIC RENDERING
    //--------------------------------------------------------------------------

public:

    //! Invalidate any existing display lists and marks the mesh for update.
    virtual void markForUpdate(const bool a_affectChildren = false);

    //! Set the alpha value at each vertex and in all of my material colors.
    virtual void setTransparencyLevel(const float a_level,
                                      const bool a_applyToTextures = false,
                                      const bool a_affectChildren = false);

    //! Set color of each vertex.
    void setVertexColor(const cColorf& a_color);

    //! Enable or disable the rendering of vertex normals.
    void setShowNormals(const bool a_showNormals) { m_showNormals = a_showNormals; }

    //! Returns whether rendering of normals is enabled.
    bool getShowNormals() const { return (m_showNormals); }

    //! Set graphic properties for normal-rendering.
    void setNormalsProperties(const double a_length, 
                              const cColorf& a_color);


    //--------------------------------------------------------------------------
    // PUBLIC METHODS - COLLISION DETECTION:
    //--------------------------------------------------------------------------

public:

    //! Set up a brute force collision detector for this mesh.
    virtual void createBruteForceCollisionDetector();

    //! Set up an AABB collision detector for this mesh.
    virtual void createAABBCollisionDetector(const double a_radius);

    //! Update the relationship between the tool and the current object.
    void computeLocalInteraction(const cVector3d& a_toolPos,
                                 const cVector3d& a_toolVel,
                                 const unsigned int a_IDN);


    //--------------------------------------------------------------------------
    // PUBLIC METHODS - MESH MANIPULATION:
    //--------------------------------------------------------------------------

public:

    //! Scale this mesh by using different scale factors along X,Y and Z axes.
    void scaleXYZ(const double a_scaleX, const double a_scaleY, const double a_scaleZ);

    //! Compute all triangle normals, optionally propagating the operation to my children.
    void computeAllNormals();

    //! Reverse all normals on this model.
    virtual void reverseAllNormals();

    //! Shifts all vertex positions by the specified amount.
    virtual void offsetVertices(const cVector3d& a_offset, 
                                const bool a_updateCollisionDetector = true);

    //! Compute the center of mass of this mesh, based on vertex positions.
    virtual cVector3d getCenterOfMass();


    //--------------------------------------------------------------------------
    // PROTECTED METHODS - INTERNAL
    //--------------------------------------------------------------------------

protected:

    //! Render object graphically (OpenGL).
    virtual void render(cRenderOptions& a_options);

    //! Draw a small line for each vertex normal.
    virtual void renderNormals(cRenderOptions& a_options);

    //! Render triangles, material and texture properties.
    virtual void renderMesh(cRenderOptions& a_options);

    //! Update the global position of each of my vertices.
    virtual void updateGlobalPositions(const bool a_frameOnly);

    //! Update my boundary box dimensions based on my vertices.
    virtual void updateBoundaryBox();

    //! Copy properties of this object to another.
    void copyMeshProperties(cMesh* a_obj,
        const bool a_duplicateMaterialData,
        const bool a_duplicateTextureData, 
        const bool a_duplicateMeshData,
        const bool a_buildCollisionDetector);

    //! Scale current object with scale factor.
    virtual void scaleObject(const double& a_scaleFactor) {scaleXYZ(a_scaleFactor, a_scaleFactor, a_scaleFactor);}


    //--------------------------------------------------------------------------
    // PROTECTED MEMBERS - DISPLAY PROPERTIES:
    //--------------------------------------------------------------------------

protected:

    //! If __true__, then normals are displayed.
    bool m_showNormals;

    //! Length of each normal (for graphic rendering of normals).
    double m_normalsLength;


    //--------------------------------------------------------------------------
    // PUBLIC MEMBERS - DISPLAY PROPERTIES:
    //--------------------------------------------------------------------------

public:

    //! Color used to render lines representing normals.
    cColorf m_normalsColor;


    //--------------------------------------------------------------------------
    // PUBLIC MEMBERS - TRIANGLE AND VERTEX DATA:
    //--------------------------------------------------------------------------

public:

    //! Array of vertices.
    cVertexArrayPtr m_vertices;

    //! Array of triangles.
    cTriangleArrayPtr m_triangles;


    //--------------------------------------------------------------------------
    // VERTEX AND ELEMENTS ARRAYS: (SHADERS)
    //--------------------------------------------------------------------------

protected:

    GLuint m_VAO;

    GLuint m_positionBuffer;
    GLuint m_normalBuffer;
    GLuint m_textCoordBuffer;

    GLuint m_elementBuffer;
};

//------------------------------------------------------------------------------
} // namespace chai3d
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------

