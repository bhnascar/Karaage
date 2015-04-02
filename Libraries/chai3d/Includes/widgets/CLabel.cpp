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
#include "CLabel.h"
using namespace std;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
namespace chai3d {
//------------------------------------------------------------------------------

//==============================================================================
/*!
    Constructor of cLabel.
*/
//==============================================================================
cLabel::cLabel(cFont* a_font)
{
    // set label properties
    m_fontScale = 1.0;
    m_string = "";
    m_font = a_font;
    m_stringPosition.set(0.0, 0.0, 0.1); // the offset of 0.1 places the string in front of the panel.

    // set panel properties
    m_panelColorTopLeft.setGrayLevel(0.40f);
    m_panelColorTopRight.setGrayLevel(0.40f);
    m_panelColorBottomLeft.setGrayLevel(0.40f);
    m_panelColorBottomRight.setGrayLevel(0.40f);
    m_panelRadiusTopLeft =       0.0;
    m_panelRadiusTopRight =      0.0;
    m_panelRadiusBottomLeft =    0.0;
    m_panelRadiusBottomRight =   0.0;
    m_numPanelSegmentsPerCorner = 8;
    m_panelEnabled = false;
}


//==============================================================================
/*!
    Destructor of cLabel.
*/
//==============================================================================
cLabel::~cLabel()
{
}


//==============================================================================
/*!
    Render the label in OpenGL.

    \param  a_options  Rendering options.
*/
//==============================================================================
void cLabel::render(cRenderOptions& a_options)
{
#ifdef C_USE_OPENGL

    // render background panel
    if (m_panelEnabled)
    {
        cMesh::render(a_options);
    }

    /////////////////////////////////////////////////////////////////////////
    // Render parts that are always opaque
    /////////////////////////////////////////////////////////////////////////
    if (SECTION_RENDER_OPAQUE_PARTS_ONLY(a_options))
    {
        // disable lighting  properties
        glDisable(GL_LIGHTING);

        // render font color
        m_fontColor.render();

        // render string at desired location
        glPushMatrix();
        glTranslated(m_stringPosition(0), m_stringPosition(1), 0.0);
        m_font->renderString(m_string, m_fontColor, m_fontScale, a_options);
        glPopMatrix();

        // enable lighting  properties
        glEnable(GL_LIGHTING);
    }

#endif
}


//==============================================================================
/*!
    Set String.

    \param  a_string  Input string.
*/
//==============================================================================
void cLabel::setString(const string a_string)
{
    // copy string
    m_string = a_string;

    // get width and height of string
    double w = getStringWidth();
    double h = getStringHeight();

    // update size of panel if needed
    if (m_panelEnabled)
    {
        // get available width from panel. we remove the radius on each side to make
        // sure that the string fits within the panel.
        double aw = m_width - 
                    cMax(m_panelRadiusTopLeft, m_panelRadiusBottomLeft) - 
                    cMax(m_panelRadiusTopRight, m_panelRadiusBottomRight);

        // if the panel is smaller that the requested dimensions, we resize it.
        if ( (m_height < (1.2 * h)) || 
             (aw < (1.2 * w)) )
        {
            setSize(cMax(m_width, 1.2 * w + cMax(m_panelRadiusTopLeft, m_panelRadiusBottomLeft) + cMax(m_panelRadiusTopRight, m_panelRadiusBottomRight)), 
                         cMax(m_height, 1.2 * h));   
        }

        // set position of string within panel
        m_stringPosition(0) = 0.5 * (m_width - w);
        m_stringPosition(1) = 0.5 * (m_height - h);
    }
    else
    {
        m_width = w;
        m_height = h;
    }

    // adjust size of boundary box
    updateBoundaryBox();
}


//==============================================================================
/*!
    Set the font scale factor.

    \param  a_scale  Scale factor.
*/
//==============================================================================
void cLabel::setFontScale(const double a_scale) 
{ 
    // update scale factor
    m_fontScale = cAbs(a_scale); 

    // adjust size of boundary box
    updateBoundaryBox();
}


//==============================================================================
/*!
    Get width of current string in pixels.

    \return Return length of string in pixels.
*/
//==============================================================================
double cLabel::getStringWidth() const
{
    if (m_font == NULL)
    {
        return (0);
    }
    else
    {
        return (m_fontScale * m_font->getStringWidth(m_string));
    }
}


//==============================================================================
/*!
    Get height of current string in pixels.

    \return Return width of string in pixels.
*/
//==============================================================================
double cLabel::getStringHeight() const
{
    if (m_font == NULL)
    {
        return (0);
    }
    else
    {
        return (m_fontScale * m_font->getPointSize());
    }
}


//==============================================================================
/*!
    Create a copy of itself.

    \param  a_duplicateMaterialData  If __true__, material (if available) is duplicated, otherwise it is shared.
    \param  a_duplicateTextureData  If __true__, texture data (if available) is duplicated, otherwise it is shared.
    \param  a_duplicateMeshData  If __true__, mesh data (if available) is duplicated, otherwise it is shared.
    \param  a_buildCollisionDetector  If __true__, collision detector (if available) is duplicated, otherwise it is shared.

    \return Return new object.
*/
//==============================================================================
cLabel* cLabel::copy(const bool a_duplicateMaterialData,
    const bool a_duplicateTextureData, 
    const bool a_duplicateMeshData,
    const bool a_buildCollisionDetector)
{
    cLabel* obj = new cLabel(m_font);

    // copy cLabel properties
    copyLabelProperties(obj, 
        a_duplicateMaterialData, 
        a_duplicateTextureData,
        a_duplicateMeshData,
        a_buildCollisionDetector);

    // return object
    return (obj);
}


//==============================================================================
/*!
    Copy properties of this object to another.

    \param  a_obj  Destination object where properties are copied to.
    \param  a_duplicateMaterialData  If __true__, material (if available) is duplicated, otherwise it is shared.
    \param  a_duplicateTextureData  If __true__, texture data (if available) is duplicated, otherwise it is shared.
    \param  a_duplicateMeshData  If __true__, mesh data (if available) is duplicated, otherwise it is shared.
    \param  a_buildCollisionDetector  If __true__, collision detector (if available) is duplicated, otherwise it is shared.
*/
//==============================================================================
void cLabel::copyLabelProperties(cLabel* a_obj,
    const bool a_duplicateMaterialData,
    const bool a_duplicateTextureData, 
    const bool a_duplicateMeshData,
    const bool a_buildCollisionDetector)
{
    // copy properties of cPanel
    copyPanelProperties(a_obj, 
        a_duplicateMaterialData, 
        a_duplicateTextureData,
        a_duplicateMeshData,
        a_buildCollisionDetector);

    // copy properties of cLabel
    a_obj->m_fontScale = m_fontScale;
    a_obj->m_fontColor = m_fontColor;

    a_obj->setString(m_string);
}


//------------------------------------------------------------------------------
} // namespace chai3d
//------------------------------------------------------------------------------
