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
#ifndef CDialH
#define CDialH
//------------------------------------------------------------------------------
#include "widgets/CGenericWidget.h"
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
namespace chai3d {
//------------------------------------------------------------------------------

//==============================================================================
/*!
    \file       CDial.h

    \brief 
    <b> Widgets </b> \n 
    2D dial.
*/
//==============================================================================

//==============================================================================
/*!
    \class      cDial
    \ingroup    widgets

    \brief
    2D Widget Level.

    \details
    Implementation of a 2D dial.
*/
//==============================================================================
class cDial : public cGenericWidget
{    
    //--------------------------------------------------------------------------
    // CONSTRUCTOR & DESTRUCTOR:
    //--------------------------------------------------------------------------

public:

    //! Constructor of cDial.
    cDial();

    //! Destructor of cDial.
    virtual ~cDial() {};


    //--------------------------------------------------------------------------
    // PUBLIC MEMBERS:
    //--------------------------------------------------------------------------

public:

    //! Color of activated increment lines.
    cColorf m_colorActive;

    //! Color of inactivated increment lines.
    cColorf m_colorInactive;


    //--------------------------------------------------------------------------
    // PUBLIC METHODS:
    //--------------------------------------------------------------------------

public:

    //! Create a copy of itself.
    virtual cDial* copy(const bool a_duplicateMaterialData = false,
        const bool a_duplicateTextureData = false, 
        const bool a_duplicateMeshData = false,
        const bool a_buildCollisionDetector = false);

    //! Set the number of increments. The value can range from 2 to 200.
    void setNumIncrements(const int a_numIncrements);

    //! Get the number of increments.
    inline int getNumIncrements() const { return (m_numIncrements); }

    //! Set the range of input values which command the increment lines.
    void setRange(const double a_minValue, const double a_maxValue); 

    //! Get minimum possible value from range.
    inline double getRangeMin() const { return (m_minValue); }

    //! Get maximum possible from range.
    inline double getRangeMax() const { return (m_maxValue); }

    //! Set the diameter of the cDial object.
    void setSize(const double a_size);

    //! Set value.
    void setValue(const double a_value);

    //! Set first value.
    void setValue0(const double a_value0);

    //! Get first value.
    inline double getValue0() const { return (m_value0); }

    //! Set second value.
    void setValue1(const double a_value1);

    //! Get second value.
    inline double getValue1() const { return (m_value1); }

    //! Set both values.
    virtual void setValues(const double a_value0, 
                           const double a_value1);

    //! Use a single colored line increment to display the value.
    inline void setSingleIncrementDisplay(const bool a_singleIncrementDisplay) { m_flagSingleIncrementDisplay = a_singleIncrementDisplay; }

    //! Get status about display mode.
    inline bool getSingleIncrementDisplay() const { return (m_flagSingleIncrementDisplay); }


    //--------------------------------------------------------------------------
    // PROTECTED MEMBERS:
    //--------------------------------------------------------------------------

protected:

    //! Number of increments.
    int m_numIncrements;

    //! Range - minimum value.
    double m_minValue;

    //! Range - maximum value
    double m_maxValue;

    //! Value 0.
    double m_value0;

    //! Value 1.
    double m_value1;

    //! If __true__, then the single segment display is activated.
    bool m_flagSingleIncrementDisplay;


    //--------------------------------------------------------------------------
    // PROTECTED METHODS:
    //--------------------------------------------------------------------------

protected:

    //! Update model.
    virtual void updateDialMesh();

    //! Update the bounding box of this object.
    virtual void updateBoundaryBox();

    //! Copy properties of this object to another.
    void copyDialProperties(cDial* a_obj,
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
