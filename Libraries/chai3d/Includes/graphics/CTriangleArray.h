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
    \version   3.0.0 $Rev: 1305 $
*/
//==============================================================================

//------------------------------------------------------------------------------
#ifndef CTriangleArrayH
#define CTriangleArrayH
//------------------------------------------------------------------------------
#include "math/CMaths.h"
#include "graphics/CVertexArray.h"
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
namespace chai3d {
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
class cGenericObject;
class cCollisionRecorder;
struct cCollisionSettings;
//------------------------------------------------------------------------------

//==============================================================================
/*!
    \file   CTriangleArray.h
    
    \brief  
    <b> Graphics </b> \n 
    Array of 3D triangles.
*/
//==============================================================================

//------------------------------------------------------------------------------
class cTriangleArray;
typedef std::shared_ptr<cTriangleArray> cTriangleArrayPtr;
//------------------------------------------------------------------------------

//==============================================================================
/*!
    \struct     cTriangleArray
    \ingroup    graphics

    \brief
    Array of 3D triangles.

    \details    
    cTriangleArray defines an array of triangles, typically bound to a mesh for 
    describing its geometry.\n

    A triangle array is created by first passing a reference to an array of vertices 
    (\ref cVertexArray) from which the triangles are composed. \n

    Every triangle is described by a set of three vertex indices. The indices point 
    to the vertices, or points, that describe the shape of the triangle. \n
    
    For graphic rendering purposes and memory efficiency, triangles are stored 
    in large arrays. The number of allocated triangles in an array can be
    retrieved by call \ref getNumTriangles().\n
    
    New triangles can be added or removed by calling \ref newTriangle() and 
    \ref removeTriangle(). respectively.\n
    
    When a triangle is removed from the array, the vertex indices are set to zero 
    and the triangle index number is added to a list of free triangles for future 
    allocation. Triangles are therefore never removed from memory, but become a 
    point until they are converted to an active triangle again.\n

    To avoid accumulating large numbers of free triangles, it is possible to 
    compress the array by calling \ref compress(). This method removes all
    non allocated triangles from memory.\n
*/
//==============================================================================
class cTriangleArray
{
    //--------------------------------------------------------------------------
    // CONSTRUCTOR & DESTRUCTOR:
    //--------------------------------------------------------------------------

public:

    //--------------------------------------------------------------------------
    /*!
        Constructor of cTriangleArray.

        \param  a_vertexArray  Array of vertices used to describe these triangles.
    */
    //--------------------------------------------------------------------------
    cTriangleArray(cVertexArrayPtr a_vertexArray)
    {
        // clear all triangles
        clear();

        // store pointer to vertex array
        m_vertices = a_vertexArray;
        m_flagMarkForUpdate     = true;
        m_VAO                   = 0;
        m_elementBuffer         = 0;
    }


    //--------------------------------------------------------------------------
    /*!
        Destructor of cTriangleArray.
    */
    //--------------------------------------------------------------------------
    ~cTriangleArray(){}


    //! Clear all triangles from array.
    void clear()
    {
        m_allocated.clear();
        m_indices.clear();
        m_freeTriangles.clear();
        m_flagMarkForUpdate = true;
    }


    //! Shared cTriangleArray allocator.
    static cTriangleArrayPtr create(cVertexArrayPtr a_vertexArray) { return (std::make_shared<cTriangleArray>(a_vertexArray)); }


    //--------------------------------------------------------------------------
    // PUBLIC METHODS:
    //--------------------------------------------------------------------------

public:

    //! Copy triangle data and return new triangle array.
    cTriangleArrayPtr copy();

    //! Return the number of allocated triangles.
    unsigned int getNumTriangles() { return (unsigned int)(m_allocated.size()); }

    //! Remove all non allocated triangles.
    void compress();


    //--------------------------------------------------------------------------
    /*!
        Create a new triangle.

        \param  a_vertexIndex0  index of vertex 0.
        \param  a_vertexIndex1  index of vertex 1.
        \param  a_vertexIndex2  index of vertex 2.

        \return Return index number of new triangle.
    */
    //--------------------------------------------------------------------------
    int newTriangle(const unsigned int a_vertexIndex0,
                    const unsigned int a_vertexIndex1, 
                    const unsigned int a_vertexIndex2)
    {
        int index;

        // check if there is an available slot on the free triangle list
        if (m_freeTriangles.size() > 0)
        {
            index = m_freeTriangles.front();
            m_allocated[index] = true;
            m_freeTriangles.pop_front();
            setVertices(index, a_vertexIndex0, a_vertexIndex1, a_vertexIndex2);
        }
        else
        {
            // store new indices
            m_indices.push_back(a_vertexIndex0);
            m_indices.push_back(a_vertexIndex1);
            m_indices.push_back(a_vertexIndex2);
            m_allocated.push_back(true);

            // store index of new triangle
            index = (int)(m_allocated.size())-1;
        }

        // return index to new triangle
        return (index);
    }


    //--------------------------------------------------------------------------
    /*!
        Is the triangle currently allocated.

        \return     Return __true__ if triangle is allocated, otherwise 
                    return __false__.
    */
    //--------------------------------------------------------------------------
    inline bool getAllocated(const unsigned int a_triangleIndex) const
    {
        return (m_allocated[a_triangleIndex]);
    };


    //--------------------------------------------------------------------------
    /*!
        Deallocate a selected triangle from the array. The three vertices of the 
        triangle are set to zero, and the triangle is added to the free list
        for future allocation.\n

        If needed, the triangle can be removed from memory by calling 
        \ref compress(). This call is computationally expensive, and 
        therefore should be avoided.

        \param  a_triangleIndex  Index of selected triangle.
    */
    //--------------------------------------------------------------------------
    void removeTriangle(const unsigned int a_triangleIndex)
    {
        // sanity check
        if (m_allocated[a_triangleIndex])
        {
            // disable triangle
            m_allocated[a_triangleIndex] = false;

            // reset indices to vertices
            setVertices(a_triangleIndex, 0, 0, 0);

            // add triangle to free list
            m_freeTriangles.push_back(a_triangleIndex);
        }
    }


    //--------------------------------------------------------------------------
    /*!
        Set the vertices of a selected triangle by passing their index numbers.

        \param  a_triangleIndex  Index of selected triangle.
        \param  a_vertexIndex0  Index of vertex 0.
        \param  a_vertexIndex1  Index of vertex 1.
        \param  a_vertexIndex2  Index of vertex 2.
    */
    //--------------------------------------------------------------------------
    inline void setVertices(const unsigned int a_triangleIndex,
                            const unsigned int a_vertexIndex0,
                            const unsigned int a_vertexIndex1, 
                            const unsigned int a_vertexIndex2)
    {
        m_indices[3*a_triangleIndex+0] = a_vertexIndex0;
        m_indices[3*a_triangleIndex+1] = a_vertexIndex1;
        m_indices[3*a_triangleIndex+2] = a_vertexIndex2;
    }


    //--------------------------------------------------------------------------
    /*!
        Read index of vertex 0 of a selected triangle.

        \param  a_triangleIndex  Index of triangle.

        \return Return pointer to vertex 0.
    */
    //--------------------------------------------------------------------------
    inline unsigned int getVertexIndex0(const unsigned int a_triangleIndex) const
    {
        return (m_indices[3*a_triangleIndex+0]);
    };


    //--------------------------------------------------------------------------
    /*!
        Read index of vertex 1 of a selected triangle.

        \param  a_triangleIndex  Index of selected triangle.

        \return Return pointer to vertex 1.
    */
    //--------------------------------------------------------------------------
    inline unsigned int getVertexIndex1(const unsigned int a_triangleIndex) const
    {
        return (m_indices[3*a_triangleIndex+1]);
    };


    //--------------------------------------------------------------------------
    /*!
        Read index of vertex 2 of a selected triangle.

        \param  a_triangleIndex  Index of triangle.

        \return Return pointer to vertex 2.
    */
    //--------------------------------------------------------------------------
    inline unsigned int getVertexIndex2(const unsigned int a_triangleIndex) const
    {
        return (m_indices[3*a_triangleIndex+2]);
    };


    //--------------------------------------------------------------------------
    /*!
         Read the index of a selected vertex (0,1, or 2) of a selected triangle.

        \param  a_triangleIndex  Index number of selected triangle.
        \param  a_index  The triangle vertex (0, 1, or 2) to access.

        \return Returns the index to the requested vertex.
    */
    //--------------------------------------------------------------------------
    inline unsigned int getVertexIndex(const unsigned int a_triangleIndex,
                                       const unsigned int a_index) const
    {
        switch (a_index)
        {
            default:
            case 0 : return (m_indices[3*a_triangleIndex+0]);
            case 1 : return (m_indices[3*a_triangleIndex+1]);
            case 2 : return (m_indices[3*a_triangleIndex+2]);
        }
    }


    //--------------------------------------------------------------------------
    /*!
        Returns the texture coordinates at the nearest point on the triangle
        from an input location.

        \param  a_triangleIndex  Index number of selected triangle.
        \param  a_localPos  Local point.

        \return Returns interpolated texture coordinate at desired location.
    */
    //--------------------------------------------------------------------------
    cVector3d getTexCoordAtPosition(const unsigned int a_triangleIndex, 
                                    const cVector3d& a_localPos)
    {
        // get vertices of contact triangles
        cVector3d vertex0 = m_vertices->getLocalPos(getVertexIndex0(a_triangleIndex));
        cVector3d vertex1 = m_vertices->getLocalPos(getVertexIndex1(a_triangleIndex));
        cVector3d vertex2 = m_vertices->getLocalPos(getVertexIndex2(a_triangleIndex));

        // project desired point on triangle
        double a0 = 0; 
        double a1 = 0;
        cProjectPointOnPlane(a_localPos, vertex0, vertex1, vertex2, a0, a1);
        cVector3d vertex = cAdd(vertex0, cMul(a0, cSub(vertex1, vertex0)), cMul(a1, cSub(vertex2, vertex0)));

        // compute area of triangle
        double area  = cTriangleArea(vertex0, vertex1, vertex2);

        // compute areas of three sub-triangles formed by the three vertices of the triangle and the contact point.
        double area0 = cTriangleArea(vertex, vertex1, vertex2);
        double area1 = cTriangleArea(vertex, vertex0, vertex2);
        double area2 = cTriangleArea(vertex, vertex0, vertex1);

        // compute weights based on position of contact point
        double c0, c1, c2;
        if (area > 0.0)
        {
            c0 = area0/area;
            c1 = area1/area;
            c2 = area2/area;
        }
        else
        {
            c0 = c1 = c2 = (1.0/3.0);
        }

        cVector3d texCoord;

        if (m_vertices->getUseTexCoordData())
        {
            // retrieve the texture coordinate for each triangle vertex
            cVector3d texCoord0 = m_vertices->getTexCoord(getVertexIndex0(a_triangleIndex));
            cVector3d texCoord1 = m_vertices->getTexCoord(getVertexIndex1(a_triangleIndex));
            cVector3d texCoord2 = m_vertices->getTexCoord(getVertexIndex2(a_triangleIndex));

            // compute the exact texture coordinate at the contact point
            texCoord = cAdd( cMul(c0, texCoord0), cMul(c1, texCoord1), cMul(c2, texCoord2));
        }
        else
        {
            texCoord.set(0.0, 0.0, 0.0);
        }

        // return result
        return (texCoord);
    }


    //--------------------------------------------------------------------------
    /*!
         Compute the normal matrix vectors for all triangles. 
    */
    //--------------------------------------------------------------------------
    inline void computeBTN()
    {
        unsigned int numTriangles = getNumTriangles();
        for (unsigned i=0; i<numTriangles; i++)
        {
            cVector3d T,B,N;

            unsigned int index0 = getVertexIndex0(i);
            unsigned int index1 = getVertexIndex1(i);
            unsigned int index2 = getVertexIndex2(i);

            // Calculate the vectors from the current vertex to the two other vertices in the triangle
            cVector3d v1v0 = m_vertices->getLocalPos(index1) - m_vertices->getLocalPos(index0);
            cVector3d v2v0 = m_vertices->getLocalPos(index2) - m_vertices->getLocalPos(index0);

            cVector3d tex0 = m_vertices->getTexCoord(index0);
            cVector3d tex1 = m_vertices->getTexCoord(index1);
            cVector3d tex2 = m_vertices->getTexCoord(index2);

            // Calculate c1c0_T and c1c0_B
            double c1c0_T = tex1.x() - tex0.x();
            double c1c0_B = tex1.y() - tex0.y();

            // Calculate c2c0_T and c2c0_B
            double c2c0_T = tex2.x() - tex0.x();
            double c2c0_B = tex2.y() - tex0.y();

            double fDenominator = c1c0_T * c2c0_B - c2c0_T * c1c0_B;
            if (cAbs(fDenominator) < C_TINY)
            {
                // We won't risk a divide by zero, so set the tangent matrix to the identity matrix
                T = cVector3d(1.0, 0.0, 0.0);
                B = cVector3d(0.0, 1.0, 0.0);
            }
            else
            {
                // Calculate the reciprocal value once and for all (to achieve speed)
                double fScale1 = 1.0f / fDenominator;

                // T and B are calculated just as the equation in the article states
                T = cVector3d((c2c0_B * v1v0.x() - c1c0_B * v2v0.x()) * fScale1,
                              (c2c0_B * v1v0.y() - c1c0_B * v2v0.y()) * fScale1,
                              (c2c0_B * v1v0.z() - c1c0_B * v2v0.z()) * fScale1);

                B = cVector3d((-c2c0_T * v1v0.x() + c1c0_T * v2v0.x()) * fScale1,
                              (-c2c0_T * v1v0.y() + c1c0_T * v2v0.y()) * fScale1,
                              (-c2c0_T * v1v0.z() + c1c0_T * v2v0.z()) * fScale1);

                // Calculate the reciprocal value once and for all (to achieve speed)
                /*
                double fScale2 = 1.0f / ((T.x() * B.y() * N.z() - T.z() * B.y() * N.x()) + 
                                         (B.x() * N.y() * T.z() - B.z() * N.y() * T.x()) + 
                                         (N.x() * T.y() * B.z() - N.z() * T.y() * B.x()));
                */

                // flipped variables (to be checked!)
                m_vertices->m_tangent[i] = cNormalize(B);
                m_vertices->m_bitangent[i] = cNormalize(T);
            }
        }
    }


    //--------------------------------------------------------------------------
    /*!
        Render OpenGL vertex buffer object
    */
    //--------------------------------------------------------------------------
    inline void render()
    { 
#ifdef C_USE_OPENGL
        unsigned int numtriangles = getNumTriangles();

        // allocate object and buffers if needed
        if (m_VAO == 0)
        {
            // allocate vertex array object
            glGenVertexArrays(1, &m_VAO);
            glBindVertexArray(m_VAO);

            // create buffers that include the properties of all vertices
            m_vertices->render();

            // index buffer
            if (m_elementBuffer == 0)
            {
                glGenBuffers(1, &m_elementBuffer);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * numtriangles * sizeof(unsigned int), &(m_indices[0]), GL_STATIC_DRAW);
            }

            // finalize
            glBindVertexArray(0);
        }

        // update data if needed
        if (m_flagMarkForUpdate)
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, 3 * numtriangles * sizeof(unsigned int), &(m_indices[0]));

            m_flagMarkForUpdate = false;
        }

        // render object
        glBindVertexArray(m_VAO);
        glDrawElements(GL_TRIANGLES, 3 * numtriangles, GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
#endif
    }

    //!  Check if the given line segment intersects a selected triangle from this array.
    bool computeCollision(const unsigned int a_triangleIndex,
                          cGenericObject* a_object,
                          cVector3d& a_segmentPointA,
                          cVector3d& a_segmentPointB,
                          cCollisionRecorder& a_recorder,
                          cCollisionSettings& a_settings) const;


    //--------------------------------------------------------------------------
    /*!
        Compute and return the area for a selected  triangle.

        \return     Returns the area for selected triangle.
    */
    //--------------------------------------------------------------------------
    inline double computeArea(const unsigned int a_triangleIndex)
    {
        // A = 0.5 * | u x v |
        cVector3d u = m_vertices->getLocalPos(getVertexIndex1(a_triangleIndex)) - m_vertices->getLocalPos(getVertexIndex0(a_triangleIndex));
        cVector3d v = m_vertices->getLocalPos(getVertexIndex2(a_triangleIndex)) - m_vertices->getLocalPos(getVertexIndex0(a_triangleIndex));

        return (0.5 * (cCross(u,v).length()));
    }


    //--------------------------------------------------------------------------
    /*!
        Computes the triangle surface normal and if requested, updates the normal
        of each of the three vertices.

        \param  a_triangleIndex  Index number of selected triangle.
        \param  a_applyNormalToVertices  If true, then update normal of each vertex.

        \return Returns the computed triangle surface normal for selected triangle.
    */
    //--------------------------------------------------------------------------
    cVector3d computeNormal(const unsigned int a_triangleIndex,
                            const bool a_applyNormalToVertices)
    {
        // get pointer to vertices
        int vertex0 = getVertexIndex0(a_triangleIndex);
        int vertex1 = getVertexIndex1(a_triangleIndex);
        int vertex2 = getVertexIndex2(a_triangleIndex);

        // retrieve vertex positions
        cVector3d pos0 = m_vertices->getLocalPos(vertex0);
        cVector3d pos1 = m_vertices->getLocalPos(vertex1);
        cVector3d pos2 = m_vertices->getLocalPos(vertex2);

        // compute normal vector
        cVector3d normal, v01, v02;
        pos1.subr(pos0, v01);
        pos2.subr(pos0, v02);
        v01.crossr(v02, normal);
        double length = normal.length();
        if (length > 0.0)
        {
            normal.div(length);
            if (a_applyNormalToVertices)
            {
                m_vertices->setNormal(vertex0, normal);
                m_vertices->setNormal(vertex1, normal);
                m_vertices->setNormal(vertex2, normal);
            }
            return (normal);
        }

        normal.zero();
        return (normal);
    }


    //--------------------------------------------------------------------------
    // PUBLIC MEMBERS:
    //--------------------------------------------------------------------------

public:

    //! Vertex array that contains all vertices used to describe the triangles of this array.
    cVertexArrayPtr m_vertices;

    //! Indices to vertices. For each triangle, there are three indices.
    std::vector<unsigned int> m_indices;

    //! Triangle allocation flags.
    std::vector<bool> m_allocated;

    //! If __true__ then triangle data has been modified.
    bool m_flagMarkForUpdate;


    //--------------------------------------------------------------------------
    // PUBLIC MEMBERS: (OPENGL)
    //--------------------------------------------------------------------------

public:

    //! OpenGL vertex array object.
    GLuint m_VAO;

    //! OpenGL Buffer for storing triangle indices.
    GLuint m_elementBuffer;


    //--------------------------------------------------------------------------
    // PROTECTED MEMBERS:
    //--------------------------------------------------------------------------

public:

    //! List of free slots in the triangle array.
    std::list<unsigned int> m_freeTriangles;
};

//------------------------------------------------------------------------------
} // namespace chai3d
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------


