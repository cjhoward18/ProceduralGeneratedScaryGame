#include "OBB.h"

bool RaySlabIntersect(float start, float dir, float min, float max, float& tfirst, float& tlast)
{
	if (fabs(dir) < 1.0E-8)
	{
		return (start < max && start > min);
	}

	float tmin = (min - start) / dir;
	float tmax = (max - start) / dir;
	if (tmin > tmax)
	{
		float tmp = tmin;
		tmin = tmax;
		tmax = tmp;
	}

	if (tmax < tfirst || tmin > tlast)
		return false;

	if (tmin > tfirst) tfirst = tmin;
	if (tmax < tlast)  tlast  = tmax;
	return true;
}



OBB::OBB(Ogre::AxisAlignedBox b) : mNormals(3), mPointsGlobal(8), mPointsLocal(8)
{
	mScale = Ogre::Vector3::UNIT_SCALE;
    mOrientation = Ogre::Quaternion::IDENTITY;
    mPosition = Ogre::Vector3::ZERO;
	mGlobalPointsDirty = true;
    setPoints(b);
}
OBB::OBB(Ogre::AxisAlignedBox b, Ogre::Vector3 position, Ogre::Quaternion orientation) : mNormals(3), mPointsGlobal(8), mPointsLocal(8)
{
    mPosition = position;
    mOrientation = orientation;
	mGlobalPointsDirty = true;
    setPoints(b);
}


 OBB::~OBB(void)
 {

	mGlobalPointsDirty = true;

 }


void
OBB::setPoints(Ogre::AxisAlignedBox b) 
{
    for (int i = 0; i < 8; i++)
    {
        mPointsLocal[i] = b.getCorner((Ogre::AxisAlignedBox::CornerEnum) i);
    }
    resetAABBandPoints();
    setNormals();
}

void
OBB::setScale(Ogre::Vector3 scale)
{
    mScale = scale;
	mGlobalPointsDirty = true;
}


void
OBB::setNormals() 
{
    mNormals[0] = mOrientation * Ogre::Vector3::UNIT_X;
    mNormals[1] = mOrientation * Ogre::Vector3::UNIT_Y;
    mNormals[2] = mOrientation * Ogre::Vector3::UNIT_Z;
}


void 
OBB::setPosition(Ogre::Vector3 newPosition)
{
    Ogre::Vector3 delta = newPosition - mPosition;
    translate(delta);
}
void OBB::translate(Ogre::Vector3 deltaPosition)
{
    mPosition += deltaPosition;
    mAABB.setExtents( mAABB.getMinimum() + deltaPosition, mAABB.getMaximum() + deltaPosition );
    for (int i = 0; i < 8; i++)
    {
        mPointsGlobal[i] += deltaPosition;
    }
}

void OBB::setOrientation(Ogre::Quaternion orentation)
{
    mOrientation = orentation;
	mGlobalPointsDirty = true;

}


double getOverlap(double min1, double max1, double min2, double max2)
{

    if (min1 >= min2 && min1 <= max2)
    {
        return max2 - min1;
    }
    else if (min2 >= min1 && min2 <= max1)
    {
        return -(max1 - min2);
    }
    else 
    {
        return 0;
    }
}


bool testIntersect(Ogre::Vector3 normal, const std::vector<Ogre::Vector3> &points1, const std::vector<Ogre::Vector3> &points2, Ogre::Vector3 &MTD, double &minOverlap)
{
        double minAlong1 = HUGE;
        double maxAlong1 = -HUGE;
        double minAlong2 = HUGE;
        double maxAlong2 = -HUGE;

        for (unsigned int i = 0; i <points1.size(); i++)
        {
            double dotProd =  normal.dotProduct(points1[i]);
            minAlong1 = std::min(minAlong1, dotProd);
            maxAlong1 = std::max(maxAlong1, dotProd);
        }
        for (unsigned int i = 0; i < points2.size(); i++)
        {
            double dotProd =  normal.dotProduct(points2[i]);
            minAlong2 = std::min(minAlong2, dotProd);
            maxAlong2 = std::max(maxAlong2, dotProd);
        }

        double  overlap = getOverlap(minAlong1, maxAlong1, minAlong2, maxAlong2);
        if (overlap == 0)
        {
            return false;
        }
        else if (std::abs(overlap) < std::abs(minOverlap))
        {
            minOverlap = overlap;
            MTD = normal * ((float) minOverlap);
        }
        return true;
}


bool  OBB::collides(Ogre::Vector3 rayStarting, Ogre::Vector3 rayDirection,float &collisionAlongRay)
{
	if (mGlobalPointsDirty)
	{
		setNormals();
		resetAABBandPoints();
		mGlobalPointsDirty = false;
	}


	Ogre::Quaternion inverseRot = mOrientation.Inverse();
	rayStarting = inverseRot * (rayStarting - mPosition); 
	rayDirection = inverseRot * rayDirection;

	float tfirst = 0.0f, tlast =collisionAlongRay;

   if (!RaySlabIntersect(rayStarting.x, rayDirection.x, (mPointsLocal[0].x)*mScale.x , mPointsLocal[Ogre::AxisAlignedBox::NEAR_RIGHT_TOP].x*mScale.x, tfirst, tlast)) return false;
   if (!RaySlabIntersect(rayStarting.y, rayDirection.y, (mPointsLocal[0].y)*mScale.y , mPointsLocal[Ogre::AxisAlignedBox::NEAR_RIGHT_TOP].y* mScale.y, tfirst, tlast)) return false;
   if (!RaySlabIntersect(rayStarting.z, rayDirection.z, (mPointsLocal[0].z)*mScale.z , mPointsLocal[Ogre::AxisAlignedBox::NEAR_RIGHT_TOP].z *mScale.z, tfirst, tlast)) return false;

    collisionAlongRay = tfirst;
    return true;



}


bool OBB::collides(OBB *other, Ogre::Vector3 &MTD) 
{
	if (mGlobalPointsDirty)
	{
		setNormals();
		resetAABBandPoints();
		mGlobalPointsDirty = false;
	}
	if (other->mGlobalPointsDirty)
	{
		other->setNormals();
		other->resetAABBandPoints();
		other->mGlobalPointsDirty = false;
	}
    return collides(*other, MTD);
}



bool OBB::collides(OBB &other, Ogre::Vector3 &MTD) 
{
	if (mGlobalPointsDirty)
	{
		setNormals();
		resetAABBandPoints();
		mGlobalPointsDirty = false;
	}
	if (other.mGlobalPointsDirty)
	{
		other.setNormals();
		other.resetAABBandPoints();
		other.mGlobalPointsDirty = false;
	}
    if (!mAABB.intersects(other.mAABB))
    {
        return false;
    }
    
    double minOverlap = HUGE;
    for (unsigned int i = 0; i < mNormals.size(); i++)
    {
        Ogre::Vector3 normal = -mNormals[i];
        if (!testIntersect(normal, mPointsGlobal, other.mPointsGlobal, MTD, minOverlap))
        {
            return false;
        }
    }
    for (unsigned int i = 0; i < other.mNormals.size(); i++)
    {
        Ogre::Vector3 normal = other.mNormals[i];
        if (!testIntersect(normal, mPointsGlobal, other.mPointsGlobal, MTD, minOverlap))
        {
            return false;
        }
    }

	// TODO:  Check MTV sign for normal cross products
    for (unsigned int i = 0; i < mNormals.size(); i++)
    {
        for (unsigned int j = 0; j < other.mNormals.size(); j++)
        {
            Ogre::Vector3 normal = mNormals[i].crossProduct(other.mNormals[j]);
			if (normal.squaredLength() > 0)
			{
				normal.normalise();
				if (!testIntersect(normal, mPointsGlobal, other.mPointsGlobal, MTD, minOverlap))
				{
					return false;
				}
			}

        }
    }
    return true;  
}

void OBB::resetAABBandPoints()
{
    mAABB = Ogre::AxisAlignedBox::BOX_NULL;

   for (int i = 0; i < 8; i++)
   {
       mPointsGlobal[i] = mOrientation * (mPointsLocal[i] * mScale) + mPosition;
       mAABB.merge(mPointsGlobal[i]);
   }
   mGlobalPointsDirty = false;
}

