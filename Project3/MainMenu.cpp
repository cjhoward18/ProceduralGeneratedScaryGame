#include "MainMenu.h"

#include "OgreOverlay.h"
#include "OgreOverlayManager.h"
#include "OgreOverlayContainer.h"
#include "OgreTextAreaOverlayElement.h"

#include "World.h"
#include "InputHandler.h"
#include "Camera.h"
#include "Sound.h"

MainMenu::MainMenu(World *world, InputHandler *input) : mWorld(world), mInputHandler(input)
{
	Ogre::OverlayManager& om = Ogre::OverlayManager::getSingleton();
	mOverlay = om.getByName("GameTitle");
	mPlayButtonOverlay = om.getByName("PlayButton");
	mRestartButtonOverlay = om.getByName("RestartButton");
	mExitButtonOverlay= om.getByName("ExitButton");
	mInstructionsOverlay = om.getByName("Instructions");
	optionSelected = 0;
	released = true;

	Ogre::TextAreaOverlayElement *te = (Ogre::TextAreaOverlayElement *) om.getOverlayElement("PlayButton/Panel/Text1");
	te->setCaption("> PLAY <");

	Ogre::TextAreaOverlayElement *te2 = (Ogre::TextAreaOverlayElement *) om.getOverlayElement("RestartButton/Panel/Text1");
	te2->setCaption("  RESTART  ");

	Ogre::TextAreaOverlayElement *te3 = (Ogre::TextAreaOverlayElement *) om.getOverlayElement("ExitButton/Panel/Text1");
	te3->setCaption("  EXIT  ");

	Ogre::TextAreaOverlayElement *te4 = (Ogre::TextAreaOverlayElement *) om.getOverlayElement("Instructions/Panel/Text1");
	te4->setCaption("FIND THE LADDER TO GET THE NEXT LEVEL \n\n AVOID THE MONSTERS \n\n WASD TO MOVE \n SPACE TO SPRINT \n F TO TOGGLE FLASHLIGHT \n\n");
	
	transitionIn = 0;
	transitionOut = 0;
	cameraY = 0;

	s = new SoundBank();
	s->setup();
	s->openFile("bell.ogg", "b", 0);

}

void MainMenu::Think(float time)
{
	if (inMenu)
	{
		if (transitionIn)
		{
			mWorld->getCamera()->setPosition(Ogre::Vector3(1, cameraY, 1));
			mWorld->getCamera()->lookAt(Ogre::Vector3(0, 0, 0));

			if (cameraY < 1)
			{
				mWorld->getCamera()->setPosition(Ogre::Vector3(0, 1, 0));
				inMenu = false;
				transitionIn = false;
			}
			else
			{
				cameraY -= 150 * time;
			}
		}
		else if (transitionOut)
		{
			mWorld->getCamera()->setPosition(Ogre::Vector3(10, cameraY, 10));
			mWorld->getCamera()->lookAt(Ogre::Vector3(0, 0, 0));

			if (cameraY > 50)
			{
				mWorld->getCamera()->setPosition(Ogre::Vector3(10, 50, 10));
				transitionOut = false;
			}
			else
			{
				cameraY += 250 * time;
			}
		}
		else if (mInputHandler->IsKeyDown(OIS::KC_DOWN) || mInputHandler->IsKeyDown(OIS::KC_UP) || mInputHandler->IsKeyDown(OIS::KC_RETURN))
		{
			if (released)
			{
				released = false;
				if (mInputHandler->IsKeyDown(OIS::KC_DOWN))
				{
					s->play("b");
					changeOption(1);
				}
				else if (mInputHandler->IsKeyDown(OIS::KC_UP))
				{
					s->play("b");
					changeOption(-1);
				}
				else if (mInputHandler->IsKeyDown(OIS::KC_RETURN))
				{
					if (optionSelected == 0)
					{
						hideMenu();
					}
					else if (optionSelected == 1)
					{
						mWorld->restartGame();
						hideMenu();
					}
					else if (optionSelected == 2)
					{
						mWorld->exitGame();
					}
				}
			}
		}
		else
		{
			released = true;
		}
	}
	else
	{
		if (mInputHandler->IsKeyDown(OIS::KC_ESCAPE))
		{
			Ogre::OverlayManager& om = Ogre::OverlayManager::getSingleton();
			Ogre::TextAreaOverlayElement *te4 = (Ogre::TextAreaOverlayElement *) om.getOverlayElement("Instructions/Panel/Text1");
			te4->setCaption("FIND THE LADDER TO GET THE NEXT LEVEL \n\n AVOID THE MONSTERS \n\n WASD TO MOVE \n SPACE TO SPRINT \n F TO TOGGLE FLASHLIGHT \n\n");
			optionSelected = 0;
			changeOption(0);
			displayMenu();
		}
	}
}

void MainMenu::killPlayer()
{
	Ogre::OverlayManager& om = Ogre::OverlayManager::getSingleton();
	Ogre::TextAreaOverlayElement *te4 = (Ogre::TextAreaOverlayElement *) om.getOverlayElement("Instructions/Panel/Text1");
	te4->setCaption("YOU DIED. DON'T DO THAT. \n\n FIND THE LADDER TO GET THE NEXT LEVEL \n\n AVOID THE MONSTERS \n\n WASD TO MOVE \n SPACE TO SPRINT \n F TO TOGGLE FLASHLIGHT \n\n");
}

void MainMenu::displayMenu()
{
	mOverlay->show();
	mPlayButtonOverlay->show();
	mRestartButtonOverlay ->show();
	mExitButtonOverlay->show();
	mInstructionsOverlay->show();
	transitionOut = 1;
	transitionIn = 0;
	inMenu = true;
}

void MainMenu::hideMenu()
{
	mOverlay->hide();
	mPlayButtonOverlay->hide();
	mRestartButtonOverlay->hide();
	mExitButtonOverlay->hide();
	mInstructionsOverlay->hide();
	transitionOut = 0;
	transitionIn = 1;
}

void MainMenu::changeOption(int difference)
{
	if (optionSelected + difference >= 0 && optionSelected + difference <= 2)
	{
		optionSelected += difference;

		Ogre::OverlayManager& om = Ogre::OverlayManager::getSingleton();
		Ogre::TextAreaOverlayElement *te = (Ogre::TextAreaOverlayElement *) om.getOverlayElement("PlayButton/Panel/Text1");
		Ogre::TextAreaOverlayElement *te2 = (Ogre::TextAreaOverlayElement *) om.getOverlayElement("RestartButton/Panel/Text1");
		Ogre::TextAreaOverlayElement *te3 = (Ogre::TextAreaOverlayElement *) om.getOverlayElement("ExitButton/Panel/Text1");
		
		if (optionSelected == 0)
		{
			te->setCaption("> PLAY <");
			te2->setCaption("  RESTART  ");
			te3->setCaption("  EXIT  ");
		}
		else if (optionSelected == 1)
		{
			te->setCaption("  PLAY  ");
			te2->setCaption("> RESTART <");
			te3->setCaption("  EXIT  ");
		}
		else
		{
			te->setCaption("  PLAY  ");
			te2->setCaption("  RESTART  ");
			te3->setCaption("> EXIT <");
		}
	}	
}