#ifndef __World_h_
#define __World_h_

#include <vector>
// Forward delcarations of Ogre classes.  Note the Ogre namespace!
namespace Ogre {
    class SceneNode;
    class SceneManager;
	class Entity;
	class Light;
	class Overlay;
	class TextAreaOverlayElement;
}

// Forward delcarations of our own classes
class GhostCamera;
class InputHandler;
class MainMenu;
class Wall;
class Room;
class LevelGenerator;
class Player;
class OBB;
class Sound;
class SoundChunk;
class SoundBank;

class World
{
public:
	
    World(Ogre::SceneManager *sceneManager, InputHandler *input);

    // You'll want various methods to access & change your world here
    void Think(float time);
	void addCamera(GhostCamera *c) { mCamera = c; }
	bool getKeepGoing() { return keepGoing; }
	void restartGame();
	void exitGame(){ keepGoing = false; }
	GhostCamera* getCamera() { return mCamera; }
	void addCollisionObject(OBB *newObject);

	Ogre::SceneManager *SceneManager() { return mSceneManager; }
	Ogre::SceneNode *flashLight;
	Player *tank;

	Ogre::SceneManager *mSceneManager;

	InputHandler *mInputHandler;
	GhostCamera *mCamera;
	MainMenu *mMainMenu;
	LevelGenerator *mLevelGenerator;



	std::vector<OBB*> *mStaticCollisions;
	
	bool restart; 
	bool nextLevel;
	OBB  *obj1;
	bool light;
	Ogre::SceneNode* ladder;
	OBB  *ladderOBB;
	int level;
private:
	
	bool keepGoing;
	
	bool released;
	int k;
	int i;
	float life;
	Ogre::Overlay *mOverlay;
	Ogre::Overlay *mOverlay2;
	Ogre::TextAreaOverlayElement *text;
	Ogre::TextAreaOverlayElement *text2;
	Ogre::Light *spot;

	Ogre::SceneNode* mBeam;
	Ogre::SceneNode* mFlashlight;
	
	Ogre::Entity *beamEntity;
	Ogre::Entity *flashEntity;
	
	OBB  *obj2;

};

#endif