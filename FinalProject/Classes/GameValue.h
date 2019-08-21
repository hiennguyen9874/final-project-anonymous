#pragma once
#include "Config.h"
#include "cocos2d.h"

USING_NS_CC;

class GameValue
{
public:
	GameValue();
	void Reset();
	void getSlingShot(int i);
	void getItems(int i);
	bool checkSlingShots(int i);
	bool checkItems(int i);
	unsigned int getUsedItem();
	void setUsedItem(unsigned int i);
	unsigned int getUsedSlingShot();
	void setUsedSlingShot(unsigned int i);
	void setcornScore(unsigned int i);
	unsigned int getcornScore();
	unsigned int getPrice(int i);
	Sprite* GetTurtorial(int i);
	Sprite* GetPlot1(int i);
	Sprite* GetPlot2(int i);
	Sprite* GetEnd(int i);
	static GameValue* getInstance();

	int GetHighScore() { 
		return this->m_iHighScore; 
	}
	void SetHighScore(int iHighscore) { 
		this->m_iHighScore = iHighscore; 
	}

	Vec2 GetPositionPlayer() { return this->m_PositionPlayer; }
	void SetPositionPlayer(Vec2 position) { this->m_PositionPlayer = position; }

	Vec2 GetCheckPoint() { return this->m_checkPoint; }
	void SetCheckPoint(Vec2 checkPoint) { this->m_checkPoint = checkPoint; }

	void LoadGameValue();
	void LoadHighScore();

	void SaveHighScore();
	void SaveGameValue();

	void SaveIsLoadGame();
	void LoadIsLoadGame();

	bool GetIsLoadGame() {
		return this->m_isLoadGame;
	}
	void SetIsLoadGame(bool isLoadGame) {
		this->m_isLoadGame = isLoadGame;
	}

	void LoadTurtorial();
	void LoadPlot1();
	void LoadPlot2();
	void LoadEnd();

	float m_fTime;
	int m_numDead;
	unsigned int cornScore;
private:
	static GameValue* m_Instance;
private:
	unsigned int usedItem = -1;
	unsigned int usedSlingShot = 0;
	bool yourSlingShot[SlingShots];
	bool yourItems[GameItems];
	unsigned int priceItems[GameItems];
	
	int m_iHighScore = 0;
	Vec2 m_PositionPlayer;
	Vec2 m_checkPoint;

	bool m_isLoadGame;

	Vector<RefPtr<Sprite>> m_turtorial;
	Vector<RefPtr<Sprite>> m_plot1;
	Vector<RefPtr<Sprite>> m_plot2;
	Vector<RefPtr<Sprite>> m_end;
};
