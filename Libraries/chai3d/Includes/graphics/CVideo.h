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
    \author    Sebastien Grange
    \version   3.0.0 $Rev: 1303 $
*/
//==============================================================================

//------------------------------------------------------------------------------
#ifndef CVideoH
#define CVideoH
//------------------------------------------------------------------------------
#include "graphics/CImage.h"
#include "timers/CPrecisionClock.h"
//------------------------------------------------------------------------------
#include <memory>
//------------------------------------------------------------------------------
namespace chai3d {
//------------------------------------------------------------------------------

//==============================================================================
/*!
    \file       CVideo.h

    \brief
    <b> Graphics </b> \n 
    2D Video Data Structure.
*/
//==============================================================================

//------------------------------------------------------------------------------
class cVideo;
typedef std::shared_ptr<cVideo> cVideoPtr;
//------------------------------------------------------------------------------

//==============================================================================
/*!
    \class      cVideo
    \ingroup    graphics 

    \brief
    2D Video structure

    \details    
    cVideo provides a class to support video files of the OGG/Vorbis format.
    Audio is also supported.
*/
//==============================================================================
class cVideo
{
    //--------------------------------------------------------------------------
    // CONSTRUCTOR & DESTRUCTOR:
    //--------------------------------------------------------------------------

public:

    //! Default constructor of cVideo.
    cVideo();

    //! Destructor of cVideo.
    virtual ~cVideo();

    //! Shared cVideo allocator.
    static cVideoPtr create() { return (std::make_shared<cVideo>()); }


    //--------------------------------------------------------------------------
    // PUBLIC METHODS - GENERAL COMMANDS:
    //--------------------------------------------------------------------------

public:

    //! Create a copy of current object.
    cVideoPtr copy();

    //! Free video from memory.
    void erase() { cleanup(); }

    //! Returns __true__ if a video file has been loaded in memory, __false__ otherwise.
    inline bool isInitialized() const { return (m_clip != NULL); }

    //! Get width of video image.
    inline unsigned int getWidth() const { return (m_width);  }

    //! Get height of video image.
    inline unsigned int getHeight() const { return (m_height); }

    //! Get number of frames of video stream.
    inline unsigned int getFrameCount() const { return (m_frameCount); }

    //! Get duration of video in seconds.
    inline double getDuration() const { return (m_duration); }

    //! Get rate of video in frames per second.
    inline double getFPS() const { return (m_fps); }


    //-----------------------------------------------------------------------
    // PUBLIC METHODS - MANIPULATING VIDEO:
    //--------------------------------------------------------------------------

public:

    //! Start playing the video.
    void play();

    //! Pause the video.
    void pause();

    //! Stop the video.
    void stop();

    //! Set auto-replay mode.
    void setAutoReplay(bool a_replay = true);

    //! Check the video playing status.
    bool isPaused();

    //! Seek a particular time in the video.
    bool seek(double a_time);

    //! Seek a particular frame in the video.
    bool seekFrame(unsigned int a_index);

    //! Get index of current video frame.
    int getCurrentFrameIndex() { return m_frameIndex; }

    //! Get time position of current video frame.
    double getCurrentTimePosition();

    //! Access the current frame (does not allocate a copy).
    bool getCurrentFramePointer(cImage &a_image);

    //! Get a copy of the current frame.
    bool getCurrentFrame(cImage &a_image);

    //! Access any frame (does not allocate a copy).
    bool getFramePointer(int a_index, cImage &a_image);

    //! Get a copy of any frame.
    bool getFrame(int a_index, cImage &a_image);


    //-----------------------------------------------------------------------
    // PUBLIC METHODS - FILES:
    //--------------------------------------------------------------------------

public:

    //! Load video file by passing image path and name as argument.
    bool loadFromFile(const std::string& a_filename);

    //! Get the filename from which this video was last loaded or saved.
    std::string getFilename() const { return (m_filename); }

    //! Get the video title.
    std::string getName() const { return (m_name); }


    //-----------------------------------------------------------------------
    // PROTECTED  METHODS:
    //--------------------------------------------------------------------------

protected:

    //! Initialize member variables.
    void defaults();

    //! Delete memory and rid ourselves of any video we had previously loaded.
    void cleanup();

    //! Update frame index and pointer to current time.
    bool update();

    //! Reset the video to the first frame and make it ready to play again.
    void reset();

    //! Store a frame locally (and flip horizontally).
    inline void storeFrame(void *frame);


    //-----------------------------------------------------------------------
    // PROTECTED MEMBERS:
    //--------------------------------------------------------------------------

protected:

    //! Video filename.
    std::string m_filename;

    //! Video name.
    std::string m_name;

    //! Width in pixels of the current video.
    unsigned int m_width;

    //! Height in pixels of the current video.
    unsigned int m_height;

    //! Frame count of the current video.
    unsigned int m_frameCount;

    //! Current frame index of the current video.
    unsigned int m_frameIndex;

    //! Duration in seconds of the current video.
    double m_duration;

    //! Last time the frame index was updated.
    double m_lastUpdate;

    //! First frame flag.
    bool m_firstFrame;

    //! Frame per seconds of the current video.
    double m_fps;

    //! Shared video manager.
    static void *m_manager;

    //! Video manager time base.
    cPrecisionClock m_clock;

    //! Video clip object.
    void *m_clip;

    //! Video frame data.
    unsigned char *m_data;

    //! Interface to audio control.
    static void *m_audio;
};

//------------------------------------------------------------------------------
} // namespace chai3d
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------
