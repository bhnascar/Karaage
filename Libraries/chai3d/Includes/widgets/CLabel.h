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
    \version   3.0.0 $Rev: 1242 $
*/
//==============================================================================

//------------------------------------------------------------------------------
#ifndef CLabelH
#define CLabelH
//------------------------------------------------------------------------------
#include "widgets/CPanel.h"
#include "graphics/CFont.h"
#include "graphics/CColor.h"
#include "system/CString.h"
#include <string>
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
namespace chai3d {
//------------------------------------------------------------------------------

//==============================================================================
/*!
    \file       CLabel.h

    \brief 
    <b> Widgets </b> \n 
    String Label.
*/
//==============================================================================

//==============================================================================
/*!
    \class      cLabel
    \ingroup    widgets  

    \brief
    2D Widget Label.

    \details
    This class provides functionalities to display one line of text.
*/
//==============================================================================
class cLabel : public cPanel
{
    //--------------------------------------------------------------------------
    // CONSTRUCTOR & DESTRUCTOR:
    //--------------------------------------------------------------------------

public:

    //! Constructor of cLabel.
    cLabel(cFont* a_font);

    //! Destructor of cLabel.
    virtual ~cLabel();


    //-----------------------------------------------------------------------
    // PUBLIC MEMBERS:
    //--------------------------------------------------------------------------

public:

    //! Font type.
    cFont* m_font;

    //! Font color.
    cColorf m_fontColor;


    //-----------------------------------------------------------------------
    // PUBLIC MEMBERS:
    //--------------------------------------------------------------------------

public:

    //! Set String.
    void setString(const std::string a_string);

    //! Get string.
    std::string getString() const { return (m_string); }

    //! Set font scale factor.
    void setFontScale(const double a_scale);

    //! Get font scale factor.
    double getFontScale() const { return (m_fontScale); }


    //-----------------------------------------------------------------------
    // PROTECTED MEMBERS:
    //--------------------------------------------------------------------------

protected:

    //! Scale factor of fonts.
    double m_fontScale;

    //! String to be displayed.
    std::string m_string;

    //! Position of string in reference to Panel.
    cVector3d m_stringPosition;


    //--------------------------------------------------------------------------
    // PUBLIC METHODS:
    //--------------------------------------------------------------------------

public:

    //! Create a copy of current object.
    cLabel* copy(const bool a_duplicateMaterialData = false,
                 const bool a_duplicateTextureData = false, 
                 const bool a_duplicateMeshData = false,
                 const bool a_buildCollisionDetector = false);

    //! Get width of string in pixels.
    virtual double getStringWidth() const;

    //! Get height of string in pixels.
    virtual double getStringHeight() const;


    //--------------------------------------------------------------------------
    // PROTECTED METHODS:
    //--------------------------------------------------------------------------

protected:

    //! Render object graphically (OpenGL).
    virtual void render(cRenderOptions& a_options);

    //! Copy properties of this object to another.
    void copyLabelProperties(cLabel* a_obj,
        const bool a_duplicateMaterialData,
        const bool a_duplicateTextureData, 
        const bool a_duplicateMeshData,
        const bool a_buildCollisionDetector);
};

//------------------------------------------------------------------------------
} // namespace chai3d
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------
