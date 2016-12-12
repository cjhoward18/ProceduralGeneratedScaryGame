#include "OgreMatrix3.h"
#include "OgreVector3.h"
#include "OgreVector4.h"

// Forward delcarations of Ogre classes.  Note the Ogre namespace!
namespace Ogre {
    class SceneNode;
    class SceneManager;
	class Entity;
}

// Forward delcarations of our own classes
class World;
class Wall;
class OBB;

class Room
{
public:
    Room(World *world, Ogre::SceneManager *sceneManager, Ogre::Vector4 doors, Ogre::Vector3 position, int roomtype);

	Ogre::Entity *floorEnt;
	Ogre::SceneNode *floor;
	Wall *nWall;
	Wall *eWall;
	Wall *wWall;
	Wall *sWall;
	OBB  *obj1;
	OBB  *obj2;
	OBB  *obj3;
	OBB  *obj5;
	OBB  *obj6;
	OBB  *obj7;
	OBB  *obj8;
	OBB  *obj9;
	OBB  *obj10;
	OBB  *obj11;
	OBB  *obj12;
	OBB  *obj13;
	OBB  *obj14;
	OBB  *obj15;
	OBB  *obj16;
	OBB  *obj4;


	Ogre::Entity *leftWall;
	Ogre::SceneNode *lWall;


	Ogre::Entity *furnEnt;
	Ogre::SceneNode *furn;
	void getPiano(Ogre::SceneManager *sceneManager, Ogre::Vector3 position);
	void getLadder(Ogre::SceneManager *sceneManager, Ogre::Vector3 position);
	void getLadder2(Ogre::SceneManager *sceneManager, Ogre::Vector3 position);
	void getChest(Ogre::SceneManager *sceneManager, Ogre::Vector3 position);
	void getChair(Ogre::SceneManager *sceneManager, Ogre::Vector3 position);
	void getBed(Ogre::SceneManager *sceneManager, Ogre::Vector3 position);
	void getBarrel(Ogre::SceneManager *sceneManager, Ogre::Vector3 position);
	void getBench(Ogre::SceneManager *sceneManager, Ogre::Vector3 position);


protected:
	Ogre::SceneManager *mSceneManager;
	World *mWorld;
};