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
#ifndef CGenericWidgetH
#define CGenericWidgetH
//------------------------------------------------------------------------------
#include "world/CMesh.h"
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
namespace chai3d {
//------------------------------------------------------------------------------

//==============================================================================
/*!
    \file       CGenericWidget.h

    \brief 
    <b> Widgets </b> \n 
    A base class for widgets.
*/
//==============================================================================

//==============================================================================
/*!
    \class      cGenericWidget
    \ingroup    widgets

    \brief
    Abstract class for 2D widgets.

    \details
    A base class for widgets. Widgets can be positioned anywhere on the front and
    back layers of the camera. The position is expressed by [x,y] coordinates.
*/
//==============================================================================
class cGenericWidget : public cMesh
{    
    //--------------------------------------------------------------------------
    // CONSTRUCTOR & DESTRUCTOR:
    //--------------------------------------------------------------------------

public:

    //! Constructor of cGenericWidget.
    cGenericWidget();

    //! Destructor of cGenericWidget.
    virtual ~cGenericWidget() {};


    //--------------------------------------------------------------------------
    // VIRTUAL PUBLIC METHODS:
    //--------------------------------------------------------------------------

public:

    //! Create a copy of itself.
    virtual cGenericWidget* copy(const bool a_duplicateMaterialData = false,
        const bool a_duplicateTextureData = false, 
        const bool a_duplicateMeshData = false,
        const bool a_buildCollisionDetector = false);

    //! Get width of widget.
    virtual double getWidth() const { return (m_width); }

    //! Get height of widget.
    virtual double getHeight() const { return (m_height); }

    //! Rotate widget around z-axis with a given angle defined in degrees.
    virtual void rotateWigetDeg(double a_angleDeg) { rotateAboutLocalAxisDeg(cVector3d(0,0,1), a_angleDeg); }

    //! Rotate widget around z-axis with a given angle defined in radians.
    virtual void rotateWigetRad(double a_angleRad) { rotateAboutLocalAxisRad(cVector3d(0,0,1), a_angleRad); }

    //! Update bounding box of widget.
    virtual void updateBoundaryBox()
    {
        m_boundaryBoxMin.set(0.0, 0.0, 0.0);
        m_boundaryBoxMax.set(m_width, m_height, 0.0);
    }


    //--------------------------------------------------------------------------
    // PROTECTED METHODS:
    //--------------------------------------------------------------------------

protected:

    //! Copy properties of this object to another.
    void copyGenericWidgetProperties(cGenericWidget* a_obj,
        const bool a_duplicateMaterialData,
        const bool a_duplicateTextureData, 
        const bool a_duplicateMeshData,
        const bool a_buildCollisionDetector);


    //--------------------------------------------------------------------------
    // PROTECTED MEMBERS:
    //--------------------------------------------------------------------------

protected:

    //! Width of widget.
    double m_width;

    //! Height of widget.
    double m_height;
};

//------------------------------------------------------------------------------
} // namespace chai3d
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------
