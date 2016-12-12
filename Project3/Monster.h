#ifndef __Monster_h_
#define __Monster_h_


namespace Ogre {
    class SceneNode;
    class SceneManager;
	class Vector3;
	class Quaternion;
	class Entity;
	class TextAreaOverlayElement;
}

class World;
class OBB;
class SoundBank;

class Monster 
{

public:
    // You may want to add parameters to the AI Manager constructor
	Monster(World *world);
	~Monster();

	Ogre::SceneNode *mMonster;
	Ogre::Entity *ent1;
    // Go through all of the AIs, and call think on each one
    void Think(float time, Ogre::Vector3 pos);
	OBB *monsterOBB;

protected:
	World *mWorld;
	
    // Probablay want a list of individual AI classes here ...
private:
	bool targetingPlayer;
	bool reachedTarget;
	bool hitDoor;
	float targetX;
	float targetZ;
	SoundBank *s;
};
#endif