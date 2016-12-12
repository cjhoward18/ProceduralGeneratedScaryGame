#ifndef __MainListener_h_
#define __MainListener_h_

#include "Ogre.h"
#include "OgreFrameListener.h"


// Forward declaration of classes
namespace Ogre
{
	class RenderWindow;
}

class InputHandler;
class AIManager;
class World;
class GhostCamera;

class MainListener : public Ogre::FrameListener
{
public:
	MainListener(Ogre::RenderWindow *mainWindow, InputHandler *inputHandler, AIManager *aiManager, World *world, GhostCamera *cam);

	bool frameStarted(const Ogre::FrameEvent &evt);


protected:
	InputHandler *mInputHandler;
	AIManager *mAIManager;
	World *mWorld;
    GhostCamera *mGhostCamera;
	Ogre::RenderWindow *mRenderWindow;
	int x;
};

#endif