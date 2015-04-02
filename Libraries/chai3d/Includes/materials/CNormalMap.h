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
    \version   3.0.0 $Rev: 1289 $
*/
//==============================================================================

//------------------------------------------------------------------------------
#ifndef CMormalMapH
#define CMormalMapH
//------------------------------------------------------------------------------
#include "materials/CTexture2d.h"
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
namespace chai3d {
//------------------------------------------------------------------------------

//==============================================================================
/*! 
    \file   CNormalMap.h

    \brief  
    <b> Materials </b> \n 
    Normal Map.
*/
//==============================================================================

//------------------------------------------------------------------------------
class cNormalMap;
typedef std::shared_ptr<cNormalMap> cNormalMapPtr;
//------------------------------------------------------------------------------

//==============================================================================
/*!
    \class      cNormalMap
    \ingroup    materials

    \brief      
    3D Normal Map

    \details      
    cNormalMap implements a normal map which is used for haptic and graphic 
    bump mapping.
*/
//==============================================================================
class cNormalMap : public cTexture2d
{
    //--------------------------------------------------------------------------
    // CONSTRUCTOR & DESTRUCTOR:
    //--------------------------------------------------------------------------

public:

    //! Constructor of cNormalMap.
    cNormalMap();

    //! Destructor of cNormalMap.
    virtual ~cNormalMap();

    //! Shared cTexture1d allocator.
    static cNormalMapPtr create() { return (std::make_shared<cNormalMap>()); }


    //--------------------------------------------------------------------------
    // PUBLIC METHODS:
    //--------------------------------------------------------------------------

public:

    //! Create a copy of current object.
    cNormalMapPtr copy();

    //! Create a normal map from a 2D image texture.
    virtual void createMap(cTexture1dPtr a_texture);

    //! Create a normal map from 2D texture.
    virtual void createMap(cImagePtr a_image);

    //! Flip normals along U and/or V axis.
    void flip(const bool a_flipU, const bool a_flipV);
};

//------------------------------------------------------------------------------
} // namespace chai3d
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------

