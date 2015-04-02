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
#ifndef CPanelH
#define CPanelH
//------------------------------------------------------------------------------
#include "widgets/CGenericWidget.h"
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
namespace chai3d {
//------------------------------------------------------------------------------

//==============================================================================
/*!
    \file       CPanel.h

    \brief 
    <b> Widgets </b> \n 
    A plain 2D Panel.
*/
//==============================================================================

//==============================================================================
/*!
    \class      cPanel
    \ingroup    widgets

    \brief
    2D Widget Panel.

    \details
    Implementation of a 2D Panel. A panel is defined by a width and a height. 
    Radius values and color properties are defined for each of its four corners.
    A panel is modeled as a mesh. If the panel is disabled, then no mesh is 
    constructed when the internal updatePanel() command is called.
*/
//==============================================================================
class cPanel : public cGenericWidget
{    
    //--------------------------------------------------------------------------
    // CONSTRUCTOR & DESTRUCTOR:
    //--------------------------------------------------------------------------

public:

    //! Constructor of cPanel.
    cPanel();

    //! Destructor of cPanel.
    virtual ~cPanel() {};


    //--------------------------------------------------------------------------
    // PUBLIC METHODS:
    //--------------------------------------------------------------------------

public:

    //! Create a copy of itself.
    virtual cPanel* copy(const bool a_duplicateMaterialData = false,
        const bool a_duplicateTextureData = false, 
        const bool a_duplicateMeshData = false,
        const bool a_buildCollisionDetector = false);

    //! Set the width, height and radius of each corner of Panel.
    virtual void set(const double& a_width, 
        const double& a_height,
        const double& a_radiusTopLeft = 0,
        const double& a_radiusTopRight = 0,
        const double& a_radiusBottomLeft = 0,
        const double& a_radiusBottomRight = 0);

    //! Set the width and height of Panel.
    virtual void setSize(const double& a_width, 
        const double& a_height);

    //! Set the radius for each corner of Panel.
    virtual void setCornerRadius(const double& a_radiusTopLeft = 0,
        const double& a_radiusTopRight = 0,
        const double& a_radiusBottomLeft = 0,
        const double& a_radiusBottomRight = 0);

    //! Set Panel color.
    virtual void setColor(const cColorf& a_panelColor);

    //! Set Panel color components for all four corners.
    virtual void setCornerColors(const cColorf& a_panelColorTopLeft, 
        const cColorf& a_panelColorTopRight, 
        const cColorf& a_panelColorBottomLeft, 
        const cColorf& a_panelColorBottomRight);

    //! Set a vertical gradient color.
    virtual void setPanelColorVerticalGradient(cColorf a_topColor, 
        cColorf a_bottomColor);

    //! Set a horizontal gradient color.
    virtual void setHorizontalLinearGradient(cColorf a_leftColor, 
        cColorf a_rightColor);

    //! Get Panel color at top left corner.
    inline cColorf getColorTopLeft() const { return (m_panelColorTopLeft); }

    //! Get color at top right corner.
    inline cColorf getColorTopRight() const { return (m_panelColorTopRight); }

    //! Get color at to left corner.
    inline cColorf getColorBottomLeft() const { return (m_panelColorBottomLeft); }

    //! Get color at to left corner.
    inline cColorf getColorBottomRight() const { return (m_panelColorBottomRight); }

    //! Enable or Disable modeling of Panel
    void setPanelEnabled(const bool a_enabled) { m_panelEnabled = a_enabled; }

    //! Enable or Disable modeling of Panel
    bool getPanelEnabled() {return (m_panelEnabled); }


    //--------------------------------------------------------------------------
    // VIRTUAL PUBLIC METHODS:
    //--------------------------------------------------------------------------

public:

    //! Assign a transparency level to the panel.
    void setTransparencyLevel(const float a_level, 
        const bool a_applyToTextures = false,
        const bool a_affectChildren = false);


    //--------------------------------------------------------------------------
    // PROTECTED MEMBERS:
    //--------------------------------------------------------------------------

protected:

    //! Radius of top left corner of Panel.
    double m_panelRadiusTopLeft;

    //! Radius of top right corner of Panel.
    double m_panelRadiusTopRight;

    //! Radius of bottom left corner of Panel.
    double m_panelRadiusBottomLeft;

    //! Radius of bottom right corner of Panel.
    double m_panelRadiusBottomRight;

    //! Number of segments used to render each corner of Panel.
    int m_numPanelSegmentsPerCorner;

    //! If __true__, Panel modeling is enabled. 
    bool m_panelEnabled;


    //--------------------------------------------------------------------------
    // PROTECTED METHODS:
    //--------------------------------------------------------------------------

protected:

    //! Update the mesh model of Panel.
    virtual void updatePanelMesh();

    //! Copy properties of this object to another.
    void copyPanelProperties(cPanel* a_obj,
        const bool a_duplicateMaterialData,
        const bool a_duplicateTextureData, 
        const bool a_duplicateMeshData,
        const bool a_buildCollisionDetector);


    //--------------------------------------------------------------------------
    // PROTECTED MEMBERS:
    //--------------------------------------------------------------------------

protected:

    //! Panel color at top left corner.
    cColorf m_panelColorTopLeft;

    //! Panel color at top right corner.
    cColorf m_panelColorTopRight;

    //! Panel color at bottom left corner.
    cColorf m_panelColorBottomLeft;

    //! Panel color at bottom right corner.
    cColorf m_panelColorBottomRight;
};

//------------------------------------------------------------------------------
} // namespace chai3d
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------
