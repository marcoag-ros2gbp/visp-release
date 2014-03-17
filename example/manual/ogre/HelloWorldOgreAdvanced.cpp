/****************************************************************************
 *
 * $Id: HelloWorldOgreAdvanced.cpp 4574 2014-01-09 08:48:51Z fspindle $
 *
 * This file is part of the ViSP software.
 * Copyright (C) 2005 - 2014 by INRIA. All rights reserved.
 * 
 * This software is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * ("GPL") version 2 as published by the Free Software Foundation.
 * See the file LICENSE.txt at the root directory of this source
 * distribution for additional information about the GNU GPL.
 *
 * For using ViSP with software that can not be combined with the GNU
 * GPL, please contact INRIA about acquiring a ViSP Professional 
 * Edition License.
 *
 * See http://www.irisa.fr/lagadic/visp/visp.html for more information.
 * 
 * This software was developed at:
 * INRIA Rennes - Bretagne Atlantique
 * Campus Universitaire de Beaulieu
 * 35042 Rennes Cedex
 * France
 * http://www.irisa.fr/lagadic
 *
 * If you have questions regarding the use of this file, please contact
 * INRIA at visp@inria.fr
 * 
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Description:
 * Ogre example.
 *
 * Authors:
 * Bertrand Delabarre
 *
 *****************************************************************************/
/*!
  \example HelloWorldOgreAdvanced.cpp

  \brief Example that shows how to exploit the vpAROgre class.

*/

#include <iostream>

#include <visp/vpOpenCVGrabber.h>
#include <visp/vpV4l2Grabber.h>
#include <visp/vp1394TwoGrabber.h>
#include <visp/vpDirectShowGrabber.h>
#include <visp/vpHomogeneousMatrix.h>
#include <visp/vpImage.h>
#include <visp/vpCameraParameters.h>
#include <visp/vpAROgre.h>

#if defined(VISP_HAVE_OGRE)

#ifndef DOXYGEN_SHOULD_SKIP_THIS

class vpAROgreAdvanced : public vpAROgre
{
private:
  // Animation attribute
  Ogre::AnimationState * mAnimationState;

public:
  vpAROgreAdvanced(const vpCameraParameters &cam = vpCameraParameters(), 
                   unsigned int width = 640, unsigned int height = 480)
		: vpAROgre(cam, width, height)
  {
    mAnimationState = NULL;
  }

protected:
  void createScene()
  {
    // Create the Entity
    Ogre::Entity* robot = mSceneMgr->createEntity("Robot", "robot.mesh");
    // Attach robot to scene graph
    Ogre::SceneNode* RobotNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("Robot");
    RobotNode->setPosition((Ogre::Real)-0.3, (Ogre::Real)0.2, (Ogre::Real)0);
    RobotNode->attachObject(robot);
    RobotNode->scale((Ogre::Real)0.001,(Ogre::Real)0.001,(Ogre::Real)0.001);
    RobotNode->pitch(Ogre::Degree(180));
    RobotNode->yaw(Ogre::Degree(-90));

    // The animation
    // Set the good animation
    mAnimationState = robot->getAnimationState( "Idle" );
    // Start over when finished
    mAnimationState->setLoop( true );
    // Animation enabled
    mAnimationState->setEnabled( true );
  }

  bool customframeEnded( const Ogre::FrameEvent& evt)
  {
    // Update animation
    // To move, we add it the time since last frame
    mAnimationState->addTime( evt.timeSinceLastFrame );
    return true;
  }
};// End of vpAROgreAdvanced class definition
#endif

#endif

int main()
{
  try {
#if defined(VISP_HAVE_OGRE) 
#if defined(VISP_HAVE_V4L2) || defined(VISP_HAVE_DC1394_2) || defined(VISP_HAVE_DIRECTSHOW) || defined(VISP_HAVE_OPENCV)

    // Now we try to find an available framegrabber
#if defined(VISP_HAVE_V4L2)
    // Video for linux 2 grabber
    vpV4l2Grabber grabber;
#elif defined(VISP_HAVE_DC1394_2)
    // libdc1394-2
    vp1394TwoGrabber grabber;
#elif defined(VISP_HAVE_DIRECTSHOW)
    // OpenCV to gather images
    vpOpenCVGrabber grabber;
#elif defined(VISP_HAVE_OPENCV)
    // OpenCV to gather images
    vpOpenCVGrabber grabber;
#endif

    // Image to store gathered data
    // Here we acquire a grey level image. The consequence will be that
    // the background texture used in Ogre renderer will be also in grey
    // level.
    vpImage<unsigned char> I;
    // Open frame grabber
    // Here we acquire an image from an available framegrabber to update
    // the image size
    grabber.open(I);
    grabber.acquire(I);
    // Parameters of our camera
    double px = 565;
    double py = 565;
    double u0 = grabber.getWidth() / 2;
    double v0 = grabber.getHeight() / 2;
    vpCameraParameters cam(px,py,u0,v0);
    // The matrix with our pose
    vpHomogeneousMatrix cMo;
    cMo[2][3] = 1.; // Z = 1 meter

    // Our object
    vpAROgreAdvanced ogre(cam, (unsigned int)grabber.getWidth(), (unsigned int)grabber.getHeight());
    // Initialisation
    ogre.init(I);

    // Rendering loop
    while(ogre.continueRendering()){
      // Image Acquisition
      grabber.acquire(I);
      // Pose computation
      // ...
      // cMo updated
      // Display with vpAROgre
      ogre.display(I, cMo);
    }
    // Release video device
    grabber.close();
#else
    std::cout << "You need an available framegrabber to run this example" << std::endl;
#endif
#else
    std::cout << "You need Ogre3D to run this example" << std::endl;
#endif
    return 0;
  }
  catch(vpException e) {
    std::cout << "Catch an exception: " << e << std::endl;
    return 1;
  }
  catch(...) {
    std::cout << "Catch an exception " << std::endl;
    return 1;
  }
}