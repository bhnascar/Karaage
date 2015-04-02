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
    \version   3.0.0 $Rev: 1303 $
*/
//==============================================================================

//------------------------------------------------------------------------------
#ifndef CShaderH
#define CShaderH
//------------------------------------------------------------------------------
#include "system/CGlobals.h"
#include "system/CString.h"
#include "math/CConstants.h"
//------------------------------------------------------------------------------
#ifdef C_USE_OPENGL
#include "GL/glew.h"
#endif
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
namespace chai3d {
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#define C_VB_INDEX_BUFFER 0
#define C_VB_POSITION 1
#define C_VB_NORMAL 2
#define C_VB_TEXCOORD 3
#define C_VB_COLOR 4
#define C_VB_TANGENT 5
#define C_VB_BITANGENT 6
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
enum cShaderType
{
    C_VERTEX_SHADER          = 0x0001,
    C_FRAGMENT_SHADER        = 0x0002,
    C_GEOMETRY_SHADER        = 0x0004
};
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
class cShader;
typedef std::shared_ptr<cShader> cShaderPtr;
//------------------------------------------------------------------------------

class cShader
{
    //--------------------------------------------------------------------------
    // CONSTRUCTOR & DESTRUCTOR:
    //--------------------------------------------------------------------------

public:

    //! Constructor of cShader.
    cShader(cShaderType a_type);

    //! Destructor of cShader.
    virtual ~cShader(){};

    //! Shared cTexture1d allocator.
    static cShaderPtr create(cShaderType a_type) { return (std::make_shared<cShader>(a_type)); }


    //--------------------------------------------------------------------------
    // PUBLIC METHODS:
    //--------------------------------------------------------------------------

public:

    //! Load the shader contents from a char array.
    bool loadSourceCode(const char *a_source);

    //! Load the shader contents from a string.
    bool loadSourceCode(const std::string& a_source);

    //! Load the shader contents from a file.
    bool loadSourceFile(const std::string& a_fileName);

    //! Compile a shader and display any problems if compilation fails
    bool compile(); 

    //! Returns __true__ if shader has been compiled successfully, __false__ otherwise.
    bool isCompiled() const { return (m_compiled); }
    
    //! Get log file.
    std::string getLog() const { return (m_log); }

    //! Get shader ID.
    GLuint getId() const { return (m_id); }

    //! Get source code of shader.
    std::string getSource() { return (m_source); }


    //--------------------------------------------------------------------------
    // STATIC METHODS:
    //--------------------------------------------------------------------------

public:

    static bool hasOpenGLShaders(cShaderType a_type);


    //--------------------------------------------------------------------------
    // PROTECTED MEMBERS:
    //--------------------------------------------------------------------------

protected:

    //! Shader type.
    cShaderType m_type;

    //! Handle ID for the shader.
    GLuint m_id;

    //! The shader source code (i.e. the GLSL code itself).
    std::string m_source; 

    //! Log message following compilation.
    std::string m_log;

    //! If __true__ then shader was compiled successfully, __false__ otherwise.
    bool m_compiled;
};

//------------------------------------------------------------------------------
} // namespace chai3d
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------
