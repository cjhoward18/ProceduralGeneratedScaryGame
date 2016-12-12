#ifndef __LevelGenerator_h_
#define __LevelGenerator_h_

#include <vector>

namespace Ogre
{
	class SceneManager;
}

class World;
class Monster;

class LevelGenerator
{
public:
	LevelGenerator(World *world, Ogre::SceneManager *sceneManager);
	void generateLevel(int rows, int columns, int roomWidth, int monsters);
	void Think(float time);
	int getRoomNumberX(int xCo);
	int getRoomNumberZ(int zCo);
	bool checkRoomExists(int x, int y);
	float getRoomXco(int x);
	float getRoomZco(int z);
	float getDoorCo(float x1, float x2);

private:
	void generateBranches(int currentRow, int currentColumn);
	void generateRoom(int currentRow, int currentColumn);
	void generateMonsters();
	void generateModels();
	int findArrayPosition(int currentRow, int currentColumn);
	bool getArrayValueAt(bool *arr, int currentRow, int currentColumn);
	void LevelGenerator::setArrayValueAt(bool *arr, bool value, int currentRow, int currentColumn);

	World *mWorld;
	Ogre::SceneManager *mSceneManager;

	// mRows AND mColumns SHOULD BE ODD NUMBER
	int mRows;
	int mColumns;
	int mRoomWidth;
	int mMonsterNumbers;

	bool *mRooms;
	bool *mNodes;
	bool *mMonsters;

	std::vector<Monster*> *mMonsterArray;
};

#endif