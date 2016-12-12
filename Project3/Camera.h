#ifndef __Camera_h_
#define __Camera_h_


namespace Ogre
{
    class Camera;
    class Vector3;
}
class World;


class GhostCamera
{

public:
    GhostCamera(Ogre::Camera *renderCamera, World *world); 

    void Think(float time);
	void setOrientationFromGhostOrientation(Ogre::Quaternion GhostOrientation);
    void setPositionFromGhostPosition(Ogre::Quaternion GhostOrientiation, Ogre::Vector3 GhostPosition);
	void setOrientation(Ogre::Quaternion orientation);
	Ogre::Vector3 getPosition();
	void setPosition(Ogre::Vector3 position);
	void yaw(Ogre::Degree degree);
	void lookAt(Ogre::Vector3 point);

	// If you have a different cameras, you'll want some acessor methods here.
    //  If your camera always stays still, you could remove this class entirely

protected:

    Ogre::Camera *mRenderCamera; 
    World *mWorld;
};

#endif