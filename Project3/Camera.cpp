#include "OgreCamera.h"
#include "Camera.h"
#include "World.h"
#include "OgreVector3.h"

GhostCamera::GhostCamera(Ogre::Camera *renderCamera, World *world) : mRenderCamera(renderCamera), mWorld(world)
{
	mRenderCamera->setNearClipDistance(0.1);
}

void
GhostCamera::Think(float time)
{
	mRenderCamera->getPosition();

	// Any code needed here to move the camera about per frame
	//  (use mRenderCamera to get the actual render camera, of course!)
}

void
GhostCamera::setOrientationFromGhostOrientation(Ogre::Quaternion GhostOrientation)
{

	mRenderCamera->setOrientation(GhostOrientation);
	/*mRenderCamera->setOrientation(GhostOrientation * Ogre::Matrix3(
		1,0,0,
		0,Ogre::Math::Cos(Ogre::Degree(0)),Ogre::Math::Sin(Ogre::Degree(0) * -1),
		0,Ogre::Math::Sin(Ogre::Degree(0)),Ogre::Math::Cos(Ogre::Degree(0)))); */
	// -15 degrees recommended
}

void 
GhostCamera::setPositionFromGhostPosition(Ogre::Quaternion GhostOrientation, Ogre::Vector3 GhostPosition)
{
	mRenderCamera->setPosition(GhostOrientation * Ogre::Vector3(0, 0, 0) + GhostPosition);
	// 0 15 35 is key
	
}

void
GhostCamera::setPosition(Ogre::Vector3 position)
{
	mRenderCamera->setPosition(position);
}

void
GhostCamera::yaw(Ogre::Degree degree)
{
	mRenderCamera->yaw(degree);
}

void
GhostCamera::setOrientation(Ogre::Quaternion orientation)
{
	mRenderCamera->setOrientation(orientation);
}

void
GhostCamera::lookAt(Ogre::Vector3 point) 
{
	mRenderCamera->lookAt(point);
}

Ogre::Vector3
GhostCamera::getPosition()
{
	return mRenderCamera->getPosition();
}
