#include "Monster.h"

#include <cmath>
#include <stdlib.h>

#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OgreEntity.h"
#include "Ogre.h"

#include "World.h"
#include "LevelGenerator.h"
#include "OBB.h"
#include "Player.h"
#include "Sound.h"

Monster::Monster(World *world) : mWorld(world)
{
	ent1 = world->SceneManager()->createEntity("DrawCall_640.001.mesh");
	mMonster = world->SceneManager()->getRootSceneNode()->createChildSceneNode();
	mMonster->attachObject(ent1);
	mMonster->scale(0.60,0.60,0.60);
	mMonster->rotate(Ogre::Vector3::NEGATIVE_UNIT_Z,Ogre::Degree(180),Ogre::Node::TS_WORLD );

	targetingPlayer = false;
	reachedTarget = false;
	targetX = 0;
	targetZ = 0;

	monsterOBB = new OBB(ent1->getBoundingBox(), mMonster->getPosition(), mMonster->getOrientation());

	s = new SoundBank();
	s->setup();
	s->openFile("Zombie.wav", "zombie1", 0);
	s->openFile("Zombie1.wav", "zombie2", 0);
	s->openFile("Death.wav", "death", 0);
}

Monster::~Monster()
{
    // Clean up after yourself ...
}

void 
	Monster::Think(float time, Ogre::Vector3 pos)
{
	float SPEED = 1.5;

	monsterOBB->setScale(Ogre::Vector3(0.3, 0.3, 0.3));
	monsterOBB->setPosition(mMonster->getPosition());
	monsterOBB->setOrientation(mMonster->getOrientation());
	
	if (mWorld->mLevelGenerator->getRoomNumberX(mMonster->getPosition().x) == mWorld->mLevelGenerator->getRoomNumberX(pos.x) && mWorld->mLevelGenerator->getRoomNumberZ(mMonster->getPosition().z) == mWorld->mLevelGenerator->getRoomNumberZ(pos.z))
	{
		if (!targetingPlayer)
		{
			if (rand() % 100 < 50)
			{
				s->play("zombie1");
			}
			else
			{
				s->play("zombie2");
			}
		}
		targetingPlayer = true;
		SPEED = 3.5;
	}
	else
	{
		if (targetingPlayer)
		{
			int posX = mWorld->mLevelGenerator->getRoomNumberX(pos.x);
			int posZ = mWorld->mLevelGenerator->getRoomNumberZ(pos.z);
			targetX = mWorld->mLevelGenerator->getRoomXco(posX);
			targetZ = mWorld->mLevelGenerator->getRoomZco(posZ);
			hitDoor = false;
		}
		targetingPlayer = false;
	}

	if (targetingPlayer)
	{
		targetX = pos.x;
		targetZ = pos.z;
	}
	else
	{
		if (reachedTarget)
		{
			int posX = mWorld->mLevelGenerator->getRoomNumberX(mMonster->getPosition().x);
			int posZ = mWorld->mLevelGenerator->getRoomNumberX(mMonster->getPosition().z);
			int roomTo = rand() % 100;
			bool hasTarget = false;
			int count = 0;
			while (!hasTarget && count < 20)
			{
				count ++;
				if (roomTo < 25)
				{
					if (mWorld->mLevelGenerator->checkRoomExists(posX + 1, posZ))
					{
						targetX = mWorld->mLevelGenerator->getRoomXco(posX + 1);
						targetZ = mWorld->mLevelGenerator->getRoomZco(posZ);
						hasTarget = true;
						reachedTarget = false;
						hitDoor = false;
					}
				}
				else if (roomTo < 50)
				{
					if (mWorld->mLevelGenerator->checkRoomExists(posX - 1, posZ))
					{
						targetX = mWorld->mLevelGenerator->getRoomXco(posX - 1);
						targetZ = mWorld->mLevelGenerator->getRoomZco(posZ);
						hasTarget = true;
						reachedTarget = false;
						hitDoor = false;
					}
				}
				else if (roomTo < 75)
				{
					if (mWorld->mLevelGenerator->checkRoomExists(posX, posZ + 1))
					{
						targetX = mWorld->mLevelGenerator->getRoomXco(posX);
						targetZ = mWorld->mLevelGenerator->getRoomZco(posZ + 1);
						hasTarget = true;
						reachedTarget = false;
						hitDoor = false;
					}
				}
				else
				{
					if (mWorld->mLevelGenerator->checkRoomExists(posX, posZ - 1))
					{
						targetX = mWorld->mLevelGenerator->getRoomXco(posX);
						targetZ = mWorld->mLevelGenerator->getRoomZco(posZ - 1);
						hasTarget = true;
						reachedTarget = false;
						hitDoor = false;
					}
				}
			}
		}
	}

	Ogre::Vector3 o =  Ogre::Vector3(targetX, 0, targetZ) - mMonster->getPosition();

	if (!targetingPlayer && !hitDoor)
	{
		o =  Ogre::Vector3(mWorld->mLevelGenerator->getDoorCo(targetX, mMonster->getPosition().x), 0, mWorld->mLevelGenerator->getDoorCo(targetZ, mMonster->getPosition().z)) - mMonster->getPosition();
	}
	
	o.y = 0;
	float x = o.x;
	float z = o.z;
	if (std::abs(x) <= SPEED * time && std::abs(z) <= SPEED * time)
	{
		if(!hitDoor)
		{
			hitDoor = true;
		}
		else
		{
			reachedTarget = true;
		}
	}
	else
	{
		o.normalise();

		if (targetingPlayer)
		{
			if (mWorld->mStaticCollisions->begin() != mWorld->mStaticCollisions->end())
			{
				for(std::vector<OBB*>::iterator it = mWorld->mStaticCollisions->begin(); it != mWorld->mStaticCollisions->end(); ++it) 
				{
					Ogre::Vector3 moveVector;

					if ((*it)->collides(monsterOBB, moveVector) == true)
					{
						mMonster->translate(-moveVector);
						x = moveVector.x;
						z = moveVector.z;
						if (std::abs(x) > std::abs(z))
						{
							o.z = 1;
						}
						else
						{
							o.x = 1;
						}
						monsterOBB->setPosition(mMonster->getPosition());
					}
				}
			}
		}
		Ogre::Vector3 moveVector;
		if (monsterOBB->collides(mWorld->obj1, moveVector) == true && mWorld->light == true) {
			mMonster->translate(
			(o.x * -SPEED * time),
			(0),
			(o.z * -SPEED * time),
			Ogre::Node::TS_WORLD);
		} else {
		mMonster->translate(
			(o.x * SPEED * time),
			(0),
			(o.z * SPEED * time),
			Ogre::Node::TS_WORLD);
		}
		mMonster->lookAt(Ogre::Vector3(targetX,mMonster->getPosition().y,targetZ), Ogre::Node::TS_WORLD, Ogre::Vector3::NEGATIVE_UNIT_Z);
		monsterOBB->setPosition(mMonster->getPosition());

		
		if (monsterOBB->collides(mWorld->tank->playerOBB, moveVector) == true)
		{
			s->play("death");
			mWorld->restart = true;
		}
	}
}

