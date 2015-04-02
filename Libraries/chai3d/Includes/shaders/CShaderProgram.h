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
    \version   3.0.0 $Rev: 1300 $
*/
//==============================================================================

//------------------------------------------------------------------------------
#ifndef CShaderProgramH
#define CShaderProgramH
//------------------------------------------------------------------------------
#include "shaders/CShader.h"
#include "world/CGenericObject.h"
//------------------------------------------------------------------------------
#include <iostream>
#include <map>
#include <vector>
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
namespace chai3d {
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
class cShaderProgram;
typedef std::shared_ptr<cShaderProgram> cShaderProgramPtr;
//------------------------------------------------------------------------------

class cShaderProgram
{
    //--------------------------------------------------------------------------
    // CONSTRUCTOR & DESTRUCTOR:
    //--------------------------------------------------------------------------

public:

    //! Constructor of cShaderProgram.
    cShaderProgram();

    //! Destructor of cShaderProgram.
    virtual ~cShaderProgram();

    //! Shared cShaderProgram allocator.
    static cShaderProgramPtr create() { return (std::make_shared<cShaderProgram>()); }


    //--------------------------------------------------------------------------
    // PUBLIC METHODS:
    //--------------------------------------------------------------------------

public:

    //! Attach a shader to the shader program.
    void attachShader(cShaderPtr a_shader);

    //! Link the shader program and return the link status.
    bool linkProgram();

    //! Enable the shader program.
    void use(cGenericObject* a_object, cRenderOptions& a_options);

    //! Disable the shader program.
    void disable();

    //! Return __true__ if shader is currently in use. __false__ otherwise.
    bool isUsed() { return (m_enabled); }

    //! Bind attribute to name
    void bindAttributeLocation(const unsigned int a_index, const char *a_name);

    //! Get location of the specified attribute.
    int getAttributeLocation(const char *a_name);

    //! Get location of the specified uniform.
    int getUniformLocation(const char *a_name);

    //! Get program ID.
    GLint getID() { return (m_id); }


    //--------------------------------------------------------------------------
    // PUBLIC METHODS: (UNIFORMS)
    //--------------------------------------------------------------------------

public:

    //! Set __int__ uniform to specified value.
    void setUniformi(const char* a_name, const GLint a_value);

    //! Set __float__ uniform to specified value.
    void setUniformf(const char* a_name, const GLfloat a_value);

    //! Set __cVector3d__ uniform to specified value.
    void setUniform(const char* a_name, cVector3d& a_value);

    //! Set __cMatrix3d__ uniform to specified value.
    void  setUniform(const char* a_name, cMatrix3d& a_value, bool a_transposed);

    //! Set __cTransform__ uniform to specified value.
    void setUniform(const char* a_name, cTransform& a_value, bool a_transposed);

    //! Set __int array__ uniform to specified values.
    void setUniformiv(const char* a_name, const GLint *a_values, const int a_count);

    //! Set __float array__ uniform to specified values.
    void setUniformfv(const char* a_name, const GLfloat *a_values, const int a_count);


    //--------------------------------------------------------------------------
    // PUBLIC METHODS: (GEOMETRY)
    //--------------------------------------------------------------------------

public:

    //! Set Type of Geometry.
    void setGeometryInputType(GLint a_type);

    //! Set output type of geometry.
    void setGeometryOutputType(GLint a_type);

    //! Sets the maximum vertex output of the geometry shader.
    void setGeometryVertexCount(GLint a_numVerticesOut);


    //--------------------------------------------------------------------------
    // PROTECTED MEMBERS:
    //--------------------------------------------------------------------------

protected:

    //! Handle ID for the shader program.
    GLuint m_id; 

    //! If __true__ then shader program was compiled linked, __false__ otherwise.
    bool m_linked;

    //! If __true__ then program shader is currently enabled.
    bool m_enabled;

    //! Number of shaders that are attached to the shader program.
    GLuint m_shaderCount;

    //! Map of attributes and their binding locations.
    std::map<std::string, int> m_attributeLocList;

    //! Map of uniforms and their binding locations.
    std::map<std::string, int> m_uniformLocList;

    //! List of attached shaders.
    std::vector<cShaderPtr> m_shaders;
};

//------------------------------------------------------------------------------
} // namespace chai3d
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------
