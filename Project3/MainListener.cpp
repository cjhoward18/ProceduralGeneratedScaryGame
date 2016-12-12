#include "MainListener.h"
#include "AIManager.h"
#include "InputHandler.h"
#include "World.h"
#include "Camera.h"
#include <ois.h>


MainListener::MainListener(Ogre::RenderWindow *mainWindow, InputHandler *inputManager, AIManager *aiManager, World *world, GhostCamera *cam) :
mRenderWindow(mainWindow), mInputHandler(inputManager), mAIManager(aiManager), mWorld(world), mGhostCamera(cam)
{
	x = 0;
}


// On every frame, call the appropriate managers
bool 
	MainListener::frameStarted(const Ogre::FrameEvent &evt)
{
	float time = evt.timeSinceLastFrame;
	if (time > 0.5)
	{
		time = 0.5;
	}
	mAIManager->Think(time);
    //  The only reason we have the Think method of the InputHandler return
    //   a value, is for the escape key to cause our application to end.
    //   Feel free to change this to something that makes more sense to you.
	mInputHandler->Think(time);
    mGhostCamera->Think(time);
	mWorld->Think(time);
	// Call think methods on any other managers / etc you want to add

	bool keepGoing = mWorld->getKeepGoing();

	// Ogre will shut down if a listener returns false.  We will shut everything down if
	// either the user presses escape or the main render window is closed.  Feel free to 
	// modify this as you like.
	if (mRenderWindow->isClosed())
	{
		keepGoing = false;
	}

	return keepGoing;
}