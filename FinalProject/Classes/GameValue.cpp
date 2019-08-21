#include "GameValue.h"


void GameValue::getSlingShot(int i)
{
	this->yourSlingShot[i] = true;
}

void GameValue::getItems(int i)
{
	this->yourItems[i] = true;
}

bool GameValue::checkSlingShots(int i)
{
	return this->yourSlingShot[i];
}

bool GameValue::checkItems(int i)
{
	return this->yourItems[i];
}

unsigned int GameValue::getUsedItem()
{
	return this->usedItem;
}

void GameValue::setUsedItem(unsigned int i)
{
	this->usedItem = i;
}

unsigned int GameValue::getUsedSlingShot()
{
	return this->usedSlingShot;
}

void GameValue::setUsedSlingShot(unsigned int i)
{
	this->usedSlingShot = i;
}

void GameValue::setcornScore(unsigned int i)
{
	this->cornScore = i;
}

unsigned int GameValue::getcornScore()
{
	return this->cornScore;
}

unsigned int GameValue::getPrice(int i)
{
	return this->priceItems[i];
}

Sprite * GameValue::GetTurtorial(int i)
{
	return this->m_turtorial.at(i);
}

Sprite * GameValue::GetPlot1(int i)
{
	return this->m_plot1.at(i);
}

Sprite * GameValue::GetPlot2(int i)
{
	return this->m_plot2.at(i);
}

Sprite * GameValue::GetEnd(int i)
{
	return this->m_end.at(i);
}

GameValue::GameValue()
{
	this->Reset();
}

void GameValue::Reset()
{
	this->yourSlingShot[0] = true;
	for (int i = 1; i < SlingShots; i++)
	{
		this->yourSlingShot[i] = false;
	}
	for (int i = 0; i < GameItems; i++)
	{
		this->yourItems[i] = false;
		this->priceItems[i] = 0;
	}
	this->cornScore = 0;
	usedItem = -1;
	usedSlingShot = 0;
	m_fTime = 0;
	m_numDead = 0;
}

GameValue* GameValue::m_Instance = nullptr;
GameValue* GameValue::getInstance()
{
	if (!m_Instance)
		m_Instance = new GameValue();
	return m_Instance;
}

void GameValue::SaveGameValue()
{
	UserDefault::getInstance()->setIntegerForKey(USED_ITEM, this->usedItem);
	UserDefault::getInstance()->setIntegerForKey(USED_SLING_SHOT, this->usedSlingShot);
	UserDefault::getInstance()->setBoolForKey(YOUR_SLING_SHOT_1, this->yourSlingShot[0]);
	UserDefault::getInstance()->setBoolForKey(YOUR_SLING_SHOT_2, this->yourSlingShot[1]);
	UserDefault::getInstance()->setBoolForKey(YOUR_SLING_SHOT_3, this->yourSlingShot[2]);
	UserDefault::getInstance()->setBoolForKey(YOUR_SLING_SHOT_4, this->yourSlingShot[3]);
	UserDefault::getInstance()->setBoolForKey(YOUR_ITEMS_1, this->yourItems[0]);
	UserDefault::getInstance()->setBoolForKey(YOUR_ITEMS_2, this->yourItems[1]);
	UserDefault::getInstance()->setBoolForKey(YOUR_ITEMS_3, this->yourItems[2]);
	UserDefault::getInstance()->setBoolForKey(YOUR_ITEMS_4, this->yourItems[3]);
	
	UserDefault::getInstance()->setIntegerForKey(CORN_SCORE, this->cornScore);
	UserDefault::getInstance()->setFloatForKey(TIME, this->m_fTime);
	UserDefault::getInstance()->setIntegerForKey(NUM_DEAD, this->m_numDead);
	
	UserDefault::getInstance()->setFloatForKey(CHECK_POINT_X, this->m_checkPoint.x);
	UserDefault::getInstance()->setFloatForKey(CHECK_POINT_Y, this->m_checkPoint.y);
	UserDefault::getInstance()->setFloatForKey(POSITION_PLAYER_X, this->m_PositionPlayer.x);
	UserDefault::getInstance()->setFloatForKey(POSITION_PLAYER_Y, this->m_PositionPlayer.y);
	UserDefault::getInstance()->flush();
}

void GameValue::SaveIsLoadGame()
{
	UserDefault::getInstance()->setBoolForKey(IS_LOAD_GAME, m_isLoadGame);
	UserDefault::getInstance()->flush();
}

void GameValue::LoadIsLoadGame()
{
	this->m_isLoadGame = UserDefault::getInstance()->getBoolForKey(IS_LOAD_GAME);
}

void GameValue::LoadTurtorial()
{
	for (int i = 0; i < TurtorialNum; i++)
	{
		Sprite* temp = Sprite::create("Images/Turtorial_" + std::to_string(i + 1) + ".png");
		this->m_turtorial.pushBack(temp);
	}
}

void GameValue::LoadPlot1()
{
	for (int i = 0; i < Plot1; i++)
	{
		Sprite* temp = Sprite::create("Images/P" + std::to_string(i + 1) + ".png");
		this->m_plot1.pushBack(temp);
	}
}

void GameValue::LoadPlot2()
{
	for (int i = 0; i < Plot2; i++)
	{
		Sprite* temp = Sprite::create("Images/C" + std::to_string(i + 1) + ".png");
		this->m_plot2.pushBack(temp);
	}
}
void GameValue::LoadEnd()
{
	for (int i = 0; i < EndLayerImages; i++)
	{
		Sprite* temp = Sprite::create("Images/E" + std::to_string(i + 1) + ".png");
		this->m_end.pushBack(temp);
	}
}
void GameValue::LoadGameValue()
{
	this->usedItem = UserDefault::getInstance()->getIntegerForKey(USED_ITEM);
	this->usedSlingShot = UserDefault::getInstance()->getIntegerForKey(USED_SLING_SHOT);
	this->yourSlingShot[0] = UserDefault::getInstance()->getBoolForKey(YOUR_SLING_SHOT_1);
	this->yourSlingShot[1] = UserDefault::getInstance()->getBoolForKey(YOUR_SLING_SHOT_2);
	this->yourSlingShot[2] = UserDefault::getInstance()->getBoolForKey(YOUR_SLING_SHOT_3);
	this->yourSlingShot[3] = UserDefault::getInstance()->getBoolForKey(YOUR_SLING_SHOT_4);
	this->yourItems[0] = UserDefault::getInstance()->getBoolForKey(YOUR_ITEMS_1);
	this->yourItems[1] = UserDefault::getInstance()->getBoolForKey(YOUR_ITEMS_2);
	this->yourItems[2] = UserDefault::getInstance()->getBoolForKey(YOUR_ITEMS_3);
	this->yourItems[3] = UserDefault::getInstance()->getBoolForKey(YOUR_ITEMS_4);
	
	this->cornScore = UserDefault::getInstance()->getIntegerForKey(CORN_SCORE);
	this->m_fTime = UserDefault::getInstance()->getFloatForKey(TIME);
	this->m_numDead = UserDefault::getInstance()->getIntegerForKey(NUM_DEAD);

	this->m_checkPoint = Vec2(UserDefault::getInstance()->getFloatForKey(CHECK_POINT_X),
		UserDefault::getInstance()->getFloatForKey(CHECK_POINT_Y));
	this->m_PositionPlayer = Vec2(UserDefault::getInstance()->getFloatForKey(POSITION_PLAYER_X),
		UserDefault::getInstance()->getFloatForKey(POSITION_PLAYER_Y));
}

void GameValue::SaveHighScore()
{
	UserDefault::getInstance()->setIntegerForKey(HIGH_SCORE, this->m_iHighScore);
	UserDefault::getInstance()->flush();
}

void GameValue::LoadHighScore()
{
	this->m_iHighScore = UserDefault::getInstance()->getIntegerForKey(HIGH_SCORE);
}

