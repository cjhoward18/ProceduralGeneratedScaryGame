#include "OgreCamera.h"
#include "Room.h"
#include "World.h"
#include "Wall.h"
#include "OgreVector3.h"
#include "OBB.h"

#include "Ogre.h"
#include "OgreMath.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OgreOverlayManager.h"
#include "OgreOverlay.h"
#include "OgreFontManager.h"
#include "OgreTextAreaOverlayElement.h"
#include <stdlib.h>
    

Room::Room(World *world, Ogre::SceneManager *sceneManager, Ogre::Vector4 doors, Ogre::Vector3 position, int roomtype)  : mWorld(world), mSceneManager(sceneManager)
{
	nWall = new Wall(mSceneManager, doors.x, position, Ogre::Radian(0));
	eWall = new Wall(mSceneManager, doors.y, position, Ogre::Radian(Ogre::Math::PI/2));
	sWall = new Wall(mSceneManager, doors.z, position, Ogre::Radian(Ogre::Math::PI));
	wWall = new Wall(mSceneManager, doors.w, position, Ogre::Radian(Ogre::Math::PI/-2));

	floorEnt = mSceneManager->createEntity("Floor.mesh");
	floor = mSceneManager->getRootSceneNode()->createChildSceneNode();
	floor->attachObject(floorEnt);
	floor->scale(5,5,5);
	floor->setPosition(position);

	leftWall = mSceneManager->createEntity("LeftWall.mesh");
	lWall = mSceneManager->getRootSceneNode()->createChildSceneNode();
	lWall->setVisible(false);

	obj1 = new OBB(leftWall->getBoundingBox(), nWall->wall[0]->getPosition(),nWall->wall[0]->getOrientation());
	obj2 = new OBB(nWall->rightWall->getBoundingBox(), nWall->wall[1]->getPosition(),nWall->wall[1]->getOrientation());
	obj3 = new OBB(nWall->upper->getBoundingBox(), nWall->wall[2]->getPosition(),nWall->wall[2]->getOrientation());

	if (doors.x) {
		obj4 = new OBB(nWall->doorWay->getBoundingBox(), nWall->wall[3]->getPosition(),nWall->wall[3]->getOrientation());
	} else {
		obj4 = new OBB(nWall->doorFill->getBoundingBox(), nWall->wall[3]->getPosition(),nWall->wall[3]->getOrientation());
		obj4->setScale(Ogre::Vector3(5, 5, 5));
		mWorld->addCollisionObject(obj4);
	}
	
	obj5 = new OBB(leftWall->getBoundingBox() , eWall->wall[0]->getPosition(),eWall->wall[0]->getOrientation());
	obj6 = new OBB(eWall->rightWall->getBoundingBox(), eWall->wall[1]->getPosition(),eWall->wall[1]->getOrientation());
	obj7 = new OBB(eWall->upper->getBoundingBox(), eWall->wall[2]->getPosition(),eWall->wall[2]->getOrientation());

	if (doors.y) {
		obj8 = new OBB(eWall->doorWay->getBoundingBox(), eWall->wall[3]->getPosition(),eWall->wall[3]->getOrientation());
	} else {
		obj8 = new OBB(eWall->doorFill->getBoundingBox(), eWall->wall[3]->getPosition(),eWall->wall[3]->getOrientation());
		obj8->setScale(Ogre::Vector3(5, 5, 5));
		mWorld->addCollisionObject(obj8);
	}

	obj9 = new OBB(leftWall->getBoundingBox(), sWall->wall[0]->getPosition(),sWall->wall[0]->getOrientation());
	obj10 = new OBB(sWall->rightWall->getBoundingBox(),sWall->wall[1]->getPosition(),sWall->wall[1]->getOrientation());
	obj11 = new OBB(sWall->upper->getBoundingBox(), sWall->wall[2]->getPosition(),sWall->wall[2]->getOrientation());

	if (doors.z) {
		obj12 = new OBB(sWall->doorWay->getBoundingBox(), sWall->wall[3]->getPosition(),sWall->wall[3]->getOrientation());
	} else {
		obj12 = new OBB(sWall->doorFill->getBoundingBox(),sWall->wall[3]->getPosition(),sWall->wall[3]->getOrientation());
		obj12->setScale(Ogre::Vector3(5, 5, 5));
		mWorld->addCollisionObject(obj12);
	}

	obj13 = new OBB(leftWall->getBoundingBox(), wWall->wall[0]->getPosition(),wWall->wall[0]->getOrientation());
	obj14 = new OBB(wWall->rightWall->getBoundingBox(), wWall->wall[1]->getPosition(),wWall->wall[1]->getOrientation());
	obj15 = new OBB(wWall->upper->getBoundingBox(), wWall->wall[2]->getPosition(),wWall->wall[2]->getOrientation());

	if (doors.w) {
		obj16 = new OBB(wWall->doorWay->getBoundingBox(), wWall->wall[3]->getPosition(),wWall->wall[3]->getOrientation());
	} else {
		obj16 = new OBB(wWall->doorFill->getBoundingBox(), wWall->wall[3]->getPosition(),wWall->wall[3]->getOrientation());
		obj16->setScale(Ogre::Vector3(5, 5, 5));
		mWorld->addCollisionObject(obj16);
	}

	obj1->setScale(Ogre::Vector3(5, 5, 5));
	obj2->setScale(Ogre::Vector3(5, 5, 5));
	obj3->setScale(Ogre::Vector3(5, 5, 5));

	obj5->setScale(Ogre::Vector3(5, 5, 5));
	obj6->setScale(Ogre::Vector3(5, 5, 5));
	obj7->setScale(Ogre::Vector3(5, 5, 5));

	obj9->setScale(Ogre::Vector3(5, 5, 5));
	obj10->setScale(Ogre::Vector3(5, 5, 5));
	obj11->setScale(Ogre::Vector3(5, 5, 5));

	obj13->setScale(Ogre::Vector3(5, 5, 5));
	obj14->setScale(Ogre::Vector3(5, 5, 5));
	obj15->setScale(Ogre::Vector3(5, 5, 5));

	mWorld->addCollisionObject(obj1);
	mWorld->addCollisionObject(obj2);
	mWorld->addCollisionObject(obj3);
	
	mWorld->addCollisionObject(obj5);
	mWorld->addCollisionObject(obj6);
	mWorld->addCollisionObject(obj7);

	mWorld->addCollisionObject(obj9);
	mWorld->addCollisionObject(obj10);
	mWorld->addCollisionObject(obj11);

	mWorld->addCollisionObject(obj13);
	mWorld->addCollisionObject(obj14);
	mWorld->addCollisionObject(obj15);

	if (roomtype == 0) {

		int i = rand() % 2;
		int j;
		for (j = 0; j <= i; j++) {
			int w = rand() % 5;
			if (w == 0 ) {
				getPiano(sceneManager, Ogre::Vector3(position.x - 4 + (rand() % 8), position.y, position.z - 4 + (rand() % 8)));
			} else if (w ==1) {
				getChest(sceneManager, Ogre::Vector3(position.x - 4 + (rand() % 8), position.y, position.z - 4 + (rand() % 8)));
				}
			else if ( w == 2) {
				getChair(sceneManager, Ogre::Vector3(position.x - 4 + (rand() % 8), position.y, position.z - 4 + (rand() % 8)));
			} else if (w == 3) {
				getBed(sceneManager, Ogre::Vector3(position.x - 4 + (rand() % 8), position.y, position.z - 4 + (rand() % 8)));
				} else if (w == 4) {
					getBench(sceneManager, Ogre::Vector3(position.x - 4 + (rand() % 8), position.y, position.z - 4 + (rand() % 8)));
			}
				else {
				getBarrel(sceneManager, Ogre::Vector3(position.x - 4 + (rand() % 8), position.y, position.z - 4 + (rand() % 8)));
			}
		}
		
		
	} else if (roomtype == 1) {
		getLadder(sceneManager, position);
	} else {
		getLadder2(sceneManager, Ogre::Vector3(position.x, position.y -2, position.z));
	}
	
}
void
	Room::getPiano(Ogre::SceneManager *sceneManager, Ogre::Vector3 position)
{
	furnEnt = mSceneManager->createEntity("1.mesh");
	furn = mSceneManager->getRootSceneNode()->createChildSceneNode();
	furn->attachObject(furnEnt);
	furn->scale(.75, .75, .75);
	furn->rotate(Ogre::Vector3::UNIT_X,Ogre::Degree(90),Ogre::Node::TS_WORLD );
	furn->setPosition(position);
	obj1 = new OBB(furnEnt->getBoundingBox(), furn->getPosition(), furn->getOrientation());
	obj1->setScale(Ogre::Vector3(.75,.75,.75));
	

	if (mWorld->mStaticCollisions->begin() != mWorld->mStaticCollisions->end())
			{
				for(std::vector<OBB*>::iterator it = mWorld->mStaticCollisions->begin(); it != mWorld->mStaticCollisions->end(); ++it) 
				{
					Ogre::Vector3 moveVector;

					if ((*it)->collides(obj1, moveVector) == true)
					{
						furn->translate(-moveVector);
						obj1->setPosition(furn->getPosition());
					}
				}
	}
	mWorld->addCollisionObject(obj1);
}

void
	Room::getLadder(Ogre::SceneManager *sceneManager, Ogre::Vector3 position)
{
	furnEnt = mSceneManager->createEntity("Ladder.mesh");
	furn = mSceneManager->getRootSceneNode()->createChildSceneNode();
	furn->attachObject(furnEnt);
	furn->scale(5, 5, 5);
	furn->setPosition(position);
	obj1 = new OBB(furnEnt->getBoundingBox(), furn->getPosition(), furn->getOrientation());
	obj1->setScale(Ogre::Vector3(5,5,5));
	mWorld->ladderOBB = obj1;            
	mWorld->ladder = furn;
}

void
	Room::getLadder2(Ogre::SceneManager *sceneManager, Ogre::Vector3 position)
{
	furnEnt = mSceneManager->createEntity("Ladder.mesh");
	furn = mSceneManager->getRootSceneNode()->createChildSceneNode();
	furn->attachObject(furnEnt);
	furn->scale(5, 5, 5);
	furn->setPosition(position);
	
}

void
Room::getChest(Ogre::SceneManager *sceneManager, Ogre::Vector3 position)
{
	furnEnt = mSceneManager->createEntity("chest1_Cube.mesh");
	furn = mSceneManager->getRootSceneNode()->createChildSceneNode();
	furn->attachObject(furnEnt);
	furn->scale(.2, .2, .2);
	furn->rotate(Ogre::Vector3::UNIT_X,Ogre::Degree(90),Ogre::Node::TS_WORLD );
	furn->setPosition(position);
	obj1 = new OBB(furnEnt->getBoundingBox(), furn->getPosition(), furn->getOrientation());
	obj1->setScale(Ogre::Vector3(.2,.2,.2));
	

	if (mWorld->mStaticCollisions->begin() != mWorld->mStaticCollisions->end())
			{
				for(std::vector<OBB*>::iterator it = mWorld->mStaticCollisions->begin(); it != mWorld->mStaticCollisions->end(); ++it) 
				{
					Ogre::Vector3 moveVector;

					if ((*it)->collides(obj1, moveVector) == true)
					{
						furn->translate(-moveVector);
						obj1->setPosition(furn->getPosition());
					}
				}
	}
	mWorld->addCollisionObject(obj1);
}

void
Room::getChair(Ogre::SceneManager *sceneManager, Ogre::Vector3 position)
{
	furnEnt = mSceneManager->createEntity("chair_chesterfield.mesh");
	furn = mSceneManager->getRootSceneNode()->createChildSceneNode();
	furn->attachObject(furnEnt);
	furn->scale(.7, .7, .7);
	furn->rotate(Ogre::Vector3::UNIT_X,Ogre::Degree(90),Ogre::Node::TS_WORLD );
	furn->setPosition(position);
	obj1 = new OBB(furnEnt->getBoundingBox(), furn->getPosition(), furn->getOrientation());
	obj1->setScale(Ogre::Vector3(.7,.7,.7));
	

	if (mWorld->mStaticCollisions->begin() != mWorld->mStaticCollisions->end())
			{
				for(std::vector<OBB*>::iterator it = mWorld->mStaticCollisions->begin(); it != mWorld->mStaticCollisions->end(); ++it) 
				{
					Ogre::Vector3 moveVector;

					if ((*it)->collides(obj1, moveVector) == true)
					{
						furn->translate(-moveVector);
						obj1->setPosition(furn->getPosition());
					}
				}
	}
	mWorld->addCollisionObject(obj1);
}

void
Room::getBed(Ogre::SceneManager *sceneManager, Ogre::Vector3 position)
{
	furnEnt = mSceneManager->createEntity("MetalWhite.mesh");
	furn = mSceneManager->getRootSceneNode()->createChildSceneNode();
	furn->attachObject(furnEnt);
	furn->scale(.25, .25, .25);
	furn->rotate(Ogre::Vector3::UNIT_X,Ogre::Degree(90),Ogre::Node::TS_WORLD );
	furn->setPosition(position);
	obj1 = new OBB(furnEnt->getBoundingBox(), furn->getPosition(), furn->getOrientation());
	obj1->setScale(Ogre::Vector3(.25,.25,.25));
	

	if (mWorld->mStaticCollisions->begin() != mWorld->mStaticCollisions->end())
			{
				for(std::vector<OBB*>::iterator it = mWorld->mStaticCollisions->begin(); it != mWorld->mStaticCollisions->end(); ++it) 
				{
					Ogre::Vector3 moveVector;

					if ((*it)->collides(obj1, moveVector) == true)
					{
						furn->translate(-moveVector);
						obj1->setPosition(furn->getPosition());
					}
				}
	}
	mWorld->addCollisionObject(obj1);
}

void
Room::getBarrel(Ogre::SceneManager *sceneManager, Ogre::Vector3 position)
{
	furnEnt = mSceneManager->createEntity("obj0.mesh");
	furn = mSceneManager->getRootSceneNode()->createChildSceneNode();
	furn->attachObject(furnEnt);
	furn->scale(1, 1, 1);
	
	furn->setPosition(position);
	obj1 = new OBB(furnEnt->getBoundingBox(), furn->getPosition(), furn->getOrientation());
	obj1->setScale(Ogre::Vector3(1,1,1));
	

	if (mWorld->mStaticCollisions->begin() != mWorld->mStaticCollisions->end())
			{
				for(std::vector<OBB*>::iterator it = mWorld->mStaticCollisions->begin(); it != mWorld->mStaticCollisions->end(); ++it) 
				{
					Ogre::Vector3 moveVector;

					if ((*it)->collides(obj1, moveVector) == true)
					{
						furn->translate(-moveVector);
						obj1->setPosition(furn->getPosition());
					}
				}
	}
	mWorld->addCollisionObject(obj1);
}


void
Room::getBench(Ogre::SceneManager *sceneManager, Ogre::Vector3 position)
{
	furnEnt = mSceneManager->createEntity("Bench.mesh");
	furn = mSceneManager->getRootSceneNode()->createChildSceneNode();
	furn->attachObject(furnEnt);
	furn->scale(.005, .005, .005);
	furn->rotate(Ogre::Vector3::UNIT_X,Ogre::Degree(90),Ogre::Node::TS_WORLD );
	furn->setPosition(position);
	obj1 = new OBB(furnEnt->getBoundingBox(), furn->getPosition(), furn->getOrientation());
	obj1->setScale(Ogre::Vector3(.005,.005,.005));
	

	if (mWorld->mStaticCollisions->begin() != mWorld->mStaticCollisions->end())
			{
				for(std::vector<OBB*>::iterator it = mWorld->mStaticCollisions->begin(); it != mWorld->mStaticCollisions->end(); ++it) 
				{
					Ogre::Vector3 moveVector;

					if ((*it)->collides(obj1, moveVector) == true)
					{
						furn->translate(-moveVector);
						obj1->setPosition(furn->getPosition());
					}
				}
	}
	mWorld->addCollisionObject(obj1);
}

// get desk , chair, bed etc....

