#include "FileUtil.h"
 #include "OgreResourceGroupManager.h"


std::string FileUtil::getFullPath(std::string resourceName)
{
	std::string foundPath = resourceName;
	Ogre::ResourceGroupManager* groupManager = Ogre::ResourceGroupManager::getSingletonPtr() ;
	Ogre::String group = groupManager->findGroupContainingResource(resourceName) ;
	Ogre::FileInfoListPtr fileInfos = groupManager->findResourceFileInfo(group,resourceName);
	Ogre::FileInfoList::iterator it = fileInfos->begin();
	if(it != fileInfos->end())
	{
		foundPath = it->archive->getName() +  resourceName;
	}

	return foundPath;
}