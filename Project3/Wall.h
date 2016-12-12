#include "OgreMatrix3.h"
#include "OgreVector3.h"

// Forward delcarations of Ogre classes.  Note the Ogre namespace!
namespace Ogre {
    class SceneNode;
    class SceneManager;
	class Entity;
}

// Forward delcarations of our own classes
class World;

class Wall
{
public:
    Wall(Ogre::SceneManager *sceneManager, int doorway, Ogre::Vector3 position, Ogre::Radian angleoffset);


	Ogre::SceneNode *wall[3];

	Ogre::Entity *leftWall;
	Ogre::Entity *rightWall;
	Ogre::Entity *upper;
	Ogre::Entity *doorFill;
	Ogre::Entity *doorWay;

	Ogre::SceneNode *lWall;
	Ogre::SceneNode *rWall;
	Ogre::SceneNode *uWall;
	Ogre::SceneNode *noDoor;
	Ogre::SceneNode *door;

	Ogre::AxisAlignedBox getBox();

public:
	Ogre::SceneManager *mSceneManager;
	World *mWorld;
};