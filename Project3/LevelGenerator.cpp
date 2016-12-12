#include "LevelGenerator.h"

#include <stdlib.h>
#include <time.h>
#include <vector>

#include "OgreSceneManager.h"
#include "OgreMeshManager.h"
#include "OgrePlane.h"
#include "OgreEntity.h"
#include "OgreSceneNode.h"

#include "World.h"
#include "Room.h"
#include "Monster.h"
#include "Camera.h"

LevelGenerator::LevelGenerator(World *world, Ogre::SceneManager *sceneManager) : mWorld(world), mSceneManager(sceneManager)
{
	srand((unsigned)time(0));

	mMonsterArray = new std::vector<Monster*>;
}

void LevelGenerator::Think(float time)
{
	if (mMonsterArray->begin() != mMonsterArray->end())
	{
		for(std::vector<Monster*>::iterator it = mMonsterArray->begin(); it != mMonsterArray->end(); ++it) 
		{
			(*it)->Think(time, mWorld->mCamera->getPosition());
		}
	}
}

int LevelGenerator::getRoomNumberX(int xCo)
{
	float result = xCo / (mRoomWidth + 0.0);
	if (result > 0)
	{
		result += 0.5;
	}
	else
	{
		result -= 0.5;
	}
	int returning = (int) result;
	return returning;
}

int LevelGenerator::getRoomNumberZ(int zCo)
{
	float result = zCo / (mRoomWidth + 0.0);
	if (result > 0)
	{
		result += 0.5;
	}
	else
	{
		result -= 0.5;
	}
	int returning = (int) result;
	return returning;
}

float LevelGenerator::getRoomXco(int x)
{
	return (x * mRoomWidth);
}

float LevelGenerator::getRoomZco(int z)
{
	return (z * mRoomWidth);
}

float LevelGenerator::getDoorCo(float x1, float x2)
{
	float returning = 0;
	x1 = getRoomNumberX(x1);
	x2 = getRoomNumberX(x2);
	if (x1 - x2 > 0)
	{
		returning = x1 * mRoomWidth - 0.5 * mRoomWidth;
	}
	else if (x1 - x2 < 0)
	{
		returning = x1 * mRoomWidth + 0.5 * mRoomWidth;
	}
	else
	{
		returning = x1 * mRoomWidth;
	}
	return returning;
}

bool LevelGenerator::checkRoomExists(int x, int z)
{
	return (getArrayValueAt(mRooms, x + mRows / 2, z + mColumns / 2));
}

void LevelGenerator::generateLevel(int rows, int columns, int roomWidth, int monsters)
{
	mRows = rows;
	mColumns = columns;
	mRoomWidth = roomWidth;
	mMonsterNumbers = monsters;

	mRooms = new bool[mRows * mColumns];
	for (int x = 0; x < mRows; x++)
	{
		for (int z = 0; z < mColumns; z++)
		{
			setArrayValueAt(mRooms, 0, x, z);
		}
	}

	mMonsters = new bool[mRows * mColumns];
	for (int x = 0; x < mRows; x++)
	{
		for (int z = 0; z < mColumns; z++)
		{
			setArrayValueAt(mMonsters, 0, x, z);
		}
	}

	mMonsterArray->clear();

	int midRow = (mRows - 1) / 2;
	int midColumn = (mColumns - 1) / 2;

	setArrayValueAt(mRooms, 1, midRow, midColumn);
	setArrayValueAt(mRooms, 1, midRow - 1, midColumn);
	setArrayValueAt(mRooms, 1, midRow + 1, midColumn);
	setArrayValueAt(mRooms, 1, midRow, midColumn - 1);
	setArrayValueAt(mRooms, 1, midRow, midColumn + 1);

	generateBranches(midRow - 1, midColumn);
	generateBranches(midRow + 1, midColumn);
	generateBranches(midRow, midColumn - 1);
	generateBranches(midRow, midColumn + 1);

	generateMonsters();

	generateModels();
}

void LevelGenerator::generateBranches(int currentRow, int currentColumn)
{
	generateRoom(currentRow + 1, currentColumn);
	generateRoom(currentRow - 1, currentColumn);
	generateRoom(currentRow, currentColumn + 1);
	generateRoom(currentRow, currentColumn - 1);
}

void LevelGenerator::generateRoom(int currentRow, int currentColumn)
{
	if (!getArrayValueAt(mRooms, currentRow, currentColumn))
	{
		if (rand() % 100 < 30)
		{
			setArrayValueAt(mRooms, 1, currentRow, currentColumn);
			generateBranches(currentRow, currentColumn);
		}
	}
}

void LevelGenerator::generateMonsters()
{
	for (int x = 0; x < mMonsterNumbers; x++)
	{
		int roomX = (int)(mRows / 2);
		int roomY = (int)(mColumns / 2);
		while (roomX == (int)(mRows / 2) && roomY == (int)(mColumns / 2))
		{
			roomX = rand() % (mRows - 1);
			roomY = rand() % (mColumns - 1);
			if (!getArrayValueAt(mRooms, roomX, roomY))
			{
				roomX = (int)(mRows / 2);
				roomY = (int)(mColumns / 2);
			}
		}
		setArrayValueAt(mMonsters, 1, roomX, roomY);
	}
}

void LevelGenerator::generateModels()
{


	Ogre::Plane plane2(Ogre::Vector3::NEGATIVE_UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane(
 "roof",
  Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
  plane2, 
  1500, 1500, 20, 20, 
  true, 
  1, 5, 5, 
  Ogre::Vector3::UNIT_Z);
	Ogre::Entity* roofEntity = mSceneManager->createEntity("roof");
	Ogre::SceneNode* roofNode = mSceneManager->getRootSceneNode()->createChildSceneNode();
	roofNode->attachObject(roofEntity);
	roofNode->setPosition(0, 2.5, 0);
	roofEntity->setMaterialName("SouthWall");

	int roomX = (int)(mRows / 2);
	int roomY = (int)(mColumns / 2);
	while (roomX == (int)(mRows / 2) && roomY == (int)(mColumns / 2))
	{
		roomX = rand() % (mRows - 1);
		roomY = rand() % (mColumns - 1);
		if (!getArrayValueAt(mRooms, roomX, roomY))
		{
			roomX = (int)(mRows / 2);
			roomY = (int)(mColumns / 2);
		}
	}
		
	for (int x = 0; x < mRows; x++)
	{
		for (int z = 0; z < mColumns; z++)
		{
			if (getArrayValueAt(mRooms, x, z))
			{
				bool left, right, up, down;
				left = right = up = down = 0;

				if (x - 1 >= 0 & x - 1 < mRows)
				{
					left = getArrayValueAt(mRooms, x - 1, z);
				}
				if (x + 1 >= 0 & x + 1 < mRows)
				{
					right = getArrayValueAt(mRooms, x + 1, z);
				}
				if (z - 1 >= 0 & z - 1 < mColumns)
				{
					up = getArrayValueAt(mRooms, x, z - 1);
				}
				if (z + 1 >= 0 & z + 1 < mColumns)
				{
					down = getArrayValueAt(mRooms, x, z + 1);
				}
				if (x == mRows / 2 && z == mColumns / 2)
				{
					new Room(mWorld, mSceneManager, Ogre::Vector4(up, left, down, right), Ogre::Vector3(x * mRoomWidth - ((mRows - 1) / 2 * mRoomWidth), 0, z * mRoomWidth - ((mColumns - 1) / 2 * mRoomWidth)), 2);
				}
				else if (x == roomX && z == roomY)
				{
					new Room(mWorld, mSceneManager, Ogre::Vector4(up, left, down, right), Ogre::Vector3(x * mRoomWidth - ((mRows - 1) / 2 * mRoomWidth), 0, z * mRoomWidth - ((mColumns - 1) / 2 * mRoomWidth)), 1);
				}
				else
				{
					new Room(mWorld, mSceneManager, Ogre::Vector4(up, left, down, right), Ogre::Vector3(x * mRoomWidth - ((mRows - 1) / 2 * mRoomWidth), 0, z * mRoomWidth - ((mColumns - 1) / 2 * mRoomWidth)), 0);
				}
			}

			if (getArrayValueAt(mMonsters, x, z))
			{
				Monster *monster = new Monster(mWorld);
				monster->mMonster->setPosition(x * mRoomWidth - ((mRows - 1) / 2 * mRoomWidth), 0.8, z * mRoomWidth - ((mColumns - 1) / 2 * mRoomWidth));
				mMonsterArray->push_back(monster);
			}
		}
	}
	

		
}

int LevelGenerator::findArrayPosition(int currentRow, int currentColumn)
{
	return currentRow * mColumns + currentColumn;
}

bool LevelGenerator::getArrayValueAt(bool *arr, int currentRow, int currentColumn)
{
	return arr[findArrayPosition(currentRow, currentColumn)];
}

void LevelGenerator::setArrayValueAt(bool *arr, bool value, int currentRow, int currentColumn)
{
	arr[findArrayPosition(currentRow, currentColumn)] = value;
}
