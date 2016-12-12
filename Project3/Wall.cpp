#include "OgreCamera.h"
#include "Wall.h"
#include "World.h"
#include "OgreVector3.h"

#include "Ogre.h"
#include "OgreMath.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OgreOverlayManager.h"
#include "OgreOverlay.h"
#include "OgreFontManager.h"
#include "OgreTextAreaOverlayElement.h"
    

Wall::Wall(Ogre::SceneManager *sceneManager, int doorway, Ogre::Vector3 position, Ogre::Radian angleoffset)  : mSceneManager(sceneManager)
{

	leftWall = mSceneManager->createEntity("LeftWall.mesh");
	wall[0] = mSceneManager->getRootSceneNode()->createChildSceneNode();
	wall[0]->attachObject(leftWall);


	rightWall = mSceneManager->createEntity("RightWall.mesh");
	wall[1] = mSceneManager->getRootSceneNode()->createChildSceneNode();
	wall[1]->attachObject(rightWall);

	upper = mSceneManager->createEntity("Upper.mesh");
	wall[2] = mSceneManager->getRootSceneNode()->createChildSceneNode();
	wall[2]->attachObject(upper);

	if (doorway) {
		doorWay = mSceneManager->createEntity("Doorway.mesh");
		wall[3] = mSceneManager->getRootSceneNode()->createChildSceneNode();
		wall[3]->attachObject(doorWay);
	} else {
		doorFill = mSceneManager->createEntity("DoorFill.mesh");
		wall[3] = mSceneManager->getRootSceneNode()->createChildSceneNode();
		wall[3]->attachObject(doorFill);
	}

	for(int i = 0; i < 4; i++) {
		wall[i]->setScale(5,5,5);
		wall[i]->setPosition(position);
		wall[i]->yaw(angleoffset);
	}
}
	Ogre::AxisAlignedBox Wall::getBox() {
		return leftWall->getBoundingBox();
	}



