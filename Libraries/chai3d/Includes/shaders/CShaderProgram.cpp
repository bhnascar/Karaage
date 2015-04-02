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
#include "shaders/CShaderProgram.h"
//------------------------------------------------------------------------------
#include "world/CGenericObject.h"
//------------------------------------------------------------------------------
using std::vector;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
namespace chai3d {
//------------------------------------------------------------------------------

//==============================================================================
/*!
    Constructor of cShaderProgram.
*/
//==============================================================================
cShaderProgram::cShaderProgram()
{
    // initialization
    m_id = 0;
    m_enabled = false;
    m_linked = false;
    m_shaders.clear();
    m_shaderCount = 0;
}


//==============================================================================
/*!
    Destructor of cShaderProgram.
*/
//==============================================================================
cShaderProgram::~cShaderProgram()
{
#ifdef C_USE_OPENGL
    if (m_id > 0)
    {
        glDeleteProgram(m_id);
    }
#endif
}


//==============================================================================
/*!
    Attach a shader to the shader program.

    \param  a_shader  Shader object.
*/
//==============================================================================
void cShaderProgram::attachShader(cShaderPtr a_shader)
{
    // add shader to list/
    m_shaders.push_back(a_shader);

    // increment the number of shaders we have associated with the program
    m_shaderCount++;
}


//==============================================================================
/*!
    Link the shader program and return the link status.
*/
//==============================================================================
bool cShaderProgram::linkProgram()
{
#ifdef C_USE_OPENGL
    // check for necessary OpenGL extensions
    if(!(GLEW_ARB_shading_language_100))
    {
        return (C_ERROR);
    }

    // check if program shader has already been linked
    if (m_linked) { return (C_SUCCESS); }

    // Generate a unique Id / handle for the shader program if needed
    if (m_id == 0)
    {
        m_id = glCreateProgram();
    }

    // If we have at least two shaders (like a vertex shader and a fragment shader)...
    if (m_shaderCount > 0)
    {
        // attach all shaders to program shader
        vector<cShaderPtr>::iterator it;
        for (it = m_shaders.begin(); it < m_shaders.end(); it++)
        {
            // make sure shader is compiled
            if ((*it)->isCompiled() == false)
            {
                (*it)->compile();
            }

            // attach shader
            if ((*it)->isCompiled() == true)
            {
                glAttachShader(m_id, (*it)->getId());
            }
        }

        // assign default location

        glBindAttribLocation(m_id, C_VB_POSITION, "aPosition");
        glBindAttribLocation(m_id, C_VB_NORMAL, "aNormal");
        glBindAttribLocation(m_id, C_VB_TEXCOORD, "aTexCoord");
        glBindAttribLocation(m_id, C_VB_COLOR, "aColor");
        glBindAttribLocation(m_id, C_VB_TANGENT, "aTangent");
        glBindAttribLocation(m_id, C_VB_BITANGENT, "aBitangent");

        // perform the linking process
        glLinkProgram(m_id);

        // check the status
        GLint linkStatus;
        glGetProgramiv(m_id, GL_LINK_STATUS, &linkStatus);
        if (linkStatus == GL_FALSE)
        {
            m_linked = false;
            return (C_ERROR);
        }
        else
        {
            m_linked = true;
            return (C_SUCCESS);
        }
    }
    else
    {
        m_linked = false;
        return (C_ERROR);
    }
#else
    return (C_ERROR);
#endif
}


//==============================================================================
/*!
    Enable the shader program.

    \param  a_object  Object on which the program shader will apply
    \param  a_options  Rendering options.
*/
//==============================================================================
void cShaderProgram::use(cGenericObject* a_object, cRenderOptions& a_options)
{
#ifdef C_USE_OPENGL
    // use program
    if (m_linked)
    {
        glUseProgram(m_id);
        m_enabled = true;
    }
#endif
}


//==============================================================================
/*!
    Disable the shader program.
*/
//==============================================================================
void cShaderProgram::disable()
{
#ifdef C_USE_OPENGL
    glUseProgram(0);
    m_enabled = false;
#endif
}


//==============================================================================
/*!
    Bind attribute to name.

    \param  a_index Index of the attribute to be bound
    \param  a__name  Name of the attribute.
*/
//==============================================================================
void cShaderProgram::bindAttributeLocation(const unsigned int a_index, const char *a_name)
{
#ifdef C_USE_OPENGL
    // check program
    if (!m_linked) { return; } 

    // get location
    glUseProgram(m_id);
    glBindAttribLocation(m_id, a_index, a_name);

    // finalize
    if (!m_enabled)
    {
        glUseProgram(0);
    }
#endif
}


//==============================================================================
/*!
    Get location of the specified attribute.

    \param  a_name  Name of the attribute.
    \return  Attribute location.
*/
//==============================================================================
int cShaderProgram::getAttributeLocation(const char *a_name) 
{
#ifdef C_USE_OPENGL
    // check program
    if (!m_linked) { return(C_ERROR); } 

    // get location
    glUseProgram(m_id);
    int attributeLocation = glGetAttribLocation(m_id, a_name);

    // finalize
    if (!m_enabled)
    {
        glUseProgram(0);
    }

    return (attributeLocation);
#else
    return (0);
#endif
}


//==============================================================================
/*!
    Get location of the specified uniform.

    \param  a_name  Name of the uniform.
    \return  Uniform location.
*/
//==============================================================================
int cShaderProgram::getUniformLocation(const char *a_name) 
{
#ifdef C_USE_OPENGL
    // check program
    if (!m_linked) { return(C_ERROR); } 

    // get location
    glUseProgram(m_id);
    int attributeLocation = glGetUniformLocation(m_id, a_name);

    // finalize
    if (!m_enabled)
    {
        glUseProgram(0);
    }

    return (attributeLocation);
#else
    return (0);
#endif
}


//==============================================================================
/*!
    Set __int__ uniform to specified value.

    \param  a_name  Name of the uniform.
    \param  a_value  New value of the uniform.
*/
//==============================================================================
void cShaderProgram::setUniformi(const char* a_name, const GLint a_value)
{
#ifdef C_USE_OPENGL
    // check program
    if (!m_linked) { return; } 

    // check location
    GLint location = glGetUniformLocation(m_id, a_name);
    if (location < 0) { return; }

    // assign value
    glUseProgram(m_id);
    glUniform1i(location, a_value);
    
    // finalize
    if (!m_enabled)
    {
        glUseProgram(0);
    }
#endif
}


//==============================================================================
/*!
    Set __float__ uniform to specified value.

    \param  a_name  Name of the uniform.
    \param  a_value  New value of the uniform.
*/
//==============================================================================
void cShaderProgram::setUniformf(const char* a_name, const GLfloat a_value)
{
#ifdef C_USE_OPENGL
    // check program
    if (!m_linked) { return; } 

    // check location
    GLint location = glGetUniformLocation(m_id, a_name);
    if (location < 0) { return; }

    // assign value
    glUseProgram(m_id);
    glUniform1f(location, a_value);

    // finalize
    if (!m_enabled)
    {
        glUseProgram(0);
    }
#endif
}


//==============================================================================
/*!
    Set __cVector3d__ uniform to specified value.

    \param  a_name  Name of the uniform.
    \param  a_value  New value of the uniform.
*/
//==============================================================================
void cShaderProgram::setUniform(const char* a_name, cVector3d& a_value) 
{
#ifdef C_USE_OPENGL
    // check program
    if (!m_linked) { return; } 

    // check location
    GLint location = glGetUniformLocation(m_id, a_name);
    if (location < 0) { return; }

    // assign value
    glUseProgram(m_id);
    glUniform3dv(location, 1, &a_value(0));

    // finalize
    if (!m_enabled)
    {
        glUseProgram(0);
    }
#endif
}


//==============================================================================
/*!
    Set __cMatrix3d__ uniform to specified value.

    \param  a_name  Name of the uniform.
    \param  a_value  New 3x3 matrix of the uniform.
    \param  a_transposed  Is the matrix transposed?
*/
//==============================================================================
void cShaderProgram::setUniform(const char* a_name, cMatrix3d& a_value, bool a_transposed)
{
#ifdef C_USE_OPENGL
    // check program
    if (!m_linked) { return; } 

    // check location
    GLint location = glGetUniformLocation(m_id, a_name);
    if (location < 0) { return; }

    // assign value
    glUseProgram(m_id);
    glUniformMatrix3dv(location, 1, a_transposed, &a_value(0,0));

    // finalize
    if (!m_enabled)
    {
        glUseProgram(0);
    }
#endif
}


//==============================================================================
/*!
    Set __cTransform__ uniform to specified value.

    \param  a_name  Name of the uniform.
    \param  a_value  New 4x4 matrix of the uniform.
    \param  a_transposed  Is the matrix transposed?
*/
//==============================================================================
void cShaderProgram::setUniform(const char* a_name, cTransform& a_value, bool a_transposed)
{
#ifdef C_USE_OPENGL
    // check program
    if (!m_linked) { return; } 

    // check location
    GLint location = glGetUniformLocation(m_id, a_name);
    if (location < 0) { return; }

    // assign value
    glUseProgram(m_id);
    glUniformMatrix4dv(location, 1, a_transposed, a_value.getData());

    // finalize
    if (!m_enabled)
    {
        glUseProgram(0);
    }
#endif
}


//==============================================================================
/*!
    Set __int array__ uniform to specified values.

    \param  a_name  Name of the uniform.
    \param  a_values  Pointer to an array with the new values.
    \param  a_count Number of values in the given array.
*/
//==============================================================================
void cShaderProgram::setUniformiv(const char *a_name, const GLint *a_values, const int a_count) 
{
#ifdef C_USE_OPENGL
    // check program
    if (!m_linked) { return; } 

    // check location
    GLint location = glGetUniformLocation(m_id, a_name);
    if (location < 0) { return; }

    // assign value
    glUseProgram(m_id);
    glUniform1iv(location, a_count, a_values);

    // finalize
    if (!m_enabled)
    {
        glUseProgram(0);
    }
#endif
}


//==============================================================================
/*!
    Set __float array__ uniform to specified values.

    \param  a_name  Name of the uniform.
    \param  a_values  Pointer to an array with the new values.
    \param  a_count Number of values in the given array.
*/
//==============================================================================
void cShaderProgram::setUniformfv(const char *a_name, const GLfloat *a_values, const int a_count) 
{
#ifdef C_USE_OPENGL
    // check program
    if (!m_linked) { return; } 

    // check location
    GLint location = glGetUniformLocation(m_id, a_name);
    if (location < 0) { return; }

    // assign value
    glUseProgram(m_id);
    glUniform1fv(location, a_count, a_values);

    // finalize
    if (!m_enabled)
    {
        glUseProgram(0);
    }
#endif
}


//==============================================================================
/*!
    Set Type of Geometry.

    \param  a_type  GL_POINTS, GL_LINES, GL_LINES_ADJACENCY_EXT, GL_TRIANGLES, GL_TRIANGLES_ADJACENCY_EXT.
*/
//==============================================================================
void cShaderProgram::setGeometryInputType(GLint a_type) 
{
#ifdef C_USE_OPENGL
    // check program
    if (!m_linked) { return; } 

    // assign value
    glUseProgram(m_id);
    glProgramParameteriEXT(m_id, GL_GEOMETRY_INPUT_TYPE_EXT, a_type);

    // finalize
    if (!m_enabled)
    {
        glUseProgram(0);
    }
#endif
}


//==============================================================================
/*!
    Set output type of geometry.

    \param  a_type  GL_POINTS, GL_LINE_STRIP, GL_TRIANGLE_STRIP.
*/
//==============================================================================
void cShaderProgram::setGeometryOutputType(GLint a_type) 
{
#ifdef C_USE_OPENGL
    // check program
    if (!m_linked) { return; } 

    // assign value
    glUseProgram(m_id);
    glProgramParameteriEXT(m_id, GL_GEOMETRY_OUTPUT_TYPE_EXT, a_type);

    // finalize
    if (!m_enabled)
    {
        glUseProgram(0);
    }
#endif
}


//==============================================================================
/*!
    Sets the maximum vertex output of the geometry shader. \n
    Query GL_MAX_GEOMETRY_OUTPUT_VERTICES_EXT to get the GPU limitation.

    \param  a_numVerticesOut  Maximal number of vertices.
*/
//==============================================================================
void cShaderProgram::setGeometryVertexCount(GLint a_numVerticesOut)
{
#ifdef C_USE_OPENGL
    // check program
    if (!m_linked) { return; } 

    // assign value
    glUseProgram(m_id);
    glProgramParameteriEXT(m_id, GL_GEOMETRY_VERTICES_OUT_EXT, a_numVerticesOut);

    // finalize
    if (!m_enabled)
    {
        glUseProgram(0);
    }
#endif
}


//------------------------------------------------------------------------------
} // namespace chai3d
//------------------------------------------------------------------------------
