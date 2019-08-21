#pragma once

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "GameObject.h"
#include "CheckPoint.h"
#include "Player.h"
#include "Gold.h"
#include "TreasureChest.h"
#include "Enemy.h"
#include "GameValue.h"
#include "MovingPlatform.h"
#include "Boss.h"
#include "Stone.h"
#include "Elevator.h"

USING_NS_CC;
using namespace std;

class ContacListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	int GetNumOfContact();
	Vec2 GetCollisionPoint();
	bool GetOnSpineVariable();
	void SetOnSpineVariable(bool bOnSpineVaiable);
	bool CheckBoucing();
	void ReFalseIsBoucing();
	Gold* GetDiamondContact() { return this->m_diamondContact; }
	TreasureChest* GetTreasureChestContact() { return this->m_treasureChest; }
	CheckPoint* GetCheckPointContact() { return this->m_CheckPoint; }
	bool CanJump();

	// Enemy
	bool GetOnEnemy() {
		return this->m_onEnemy;
	}

	void SetOnEnemy(bool onEnemy) {
		this->m_onEnemy = onEnemy;
	}

	Enemy* GetEnemyPointer() {
		return this->m_Enemy;
	}

	void SetEnemyPointer() {
		this->m_Enemy = nullptr;
	}

	// Van toc cua player truoc khi dap vao tu
	b2Vec2 GetLinearVelocity() {
		return this->m_linearVelocityPlayer;
	}

	Vec2 GetPositionPlatform() {
		if (this->GetOnMovingPlatform())
			return this->m_Movingplatform->getPosition();
		else if (this->GetOnElevator())
			return this->m_ptrElevator->getPosition();
	}

	// MovingPlatform
	bool GetOnMovingPlatform() {
		return this->m_onMovingPlatform;
	}

	void SetOnMovingPlatform(bool bOnMovingPlatform) {
		this->m_onMovingPlatform = bOnMovingPlatform;
	}

	MovingPlatform * GetMovingPlatformPointer() {
		return this->m_Movingplatform;
	}

	void SetMovingPlatformPointer() {
		this->m_Movingplatform = nullptr;
	}

	// Player on Elevator button
	bool GetOnElevatorButton() {
		return this->m_onElevatorButton;
	}

	void SetOnElevatorButton(bool onElevatorButton) {
		this->m_onElevatorButton = onElevatorButton;
	}

	Elevator *GetPtrElevatorButton() {
		return this->m_ptrElevator;
	}

	bool GetOnElevator() {
		return this->m_onElevator;
	}

	void SetOnElevator(bool onElevator) {
		this->m_onElevator = onElevator;
	}

	// Boss 
	bool GetOnBoss() {
		return this->m_onBoss;
	}

	void SetOnBoss(bool onBoss) {
		this->m_onBoss = onBoss;
	}

	Boss *GetBossPointer() {
		return this->m_ptrBoss;
	}

	void SetBossPointer() {
		this->m_ptrBoss = nullptr;
	}

	// Boss va cham voi da
	bool GetOnBossContactWithStone() {
		return this->m_onContactWithStone;
	}

	void SetBossContactWithStone(bool BossOnContactWithStone) {
		this->m_onContactWithStone = false;
	}

	Boss *GetBossOnContactWithStone() {
		return this->m_ptrBossContactWithStone;
	}

	Stone *GetStoneOnContactWithBoss() {
		return this->m_ptrStoneContactWithBoss;
	}

	// Stone va cham voi Player
	bool GetOnPlayerConttactWithStone() {
		return this->m_onPlayerOnContactWithStone;
	}

	void SetOnPlayerContactWithStone(bool PlayerContactWithStone) {
		this->m_onPlayerOnContactWithStone = PlayerContactWithStone;
	}

	Player *GetPlayerOnContactWithStone() {
		return this->m_playerOnContactWithStone;
	}

	Stone *GetStoneOnContactWithPlayer() {
		return this->m_stoneOnContactWithPlayer;
	}

	bool CheckContactWithJail() {
		return this->m_contactWithJail;
	}

	//
	bool GetIsPlayerEffectLand() {
		return this->m_bPlayerEffect;
	}

	void SetIsPlayerEffectLand(bool isPlayerEffectLand);

private:
	bool m_contactWithJail = false;
	int m_numOfContact = 0;
	bool m_onSpine = false;

	Vec2 m_positionCollision = Vec2(0, 0);

	bool m_isBoucing = false;
	Vec2 m_StoneCollision = Vec2::ZERO;

	RefPtr<Stone> m_stone = nullptr;

	Vec2 m_positionColliTreasureChest = Vec2(0, 0);

	// Treasure Chest
	RefPtr<Gold> m_diamondContact = nullptr;
	RefPtr<TreasureChest> m_treasureChest = nullptr;
	RefPtr<CheckPoint> m_CheckPoint = nullptr;

	// Enemy
	bool m_onEnemy = false;
	RefPtr<Enemy> m_Enemy = nullptr;
	b2Vec2 m_linearVelocityPlayer;

	// Moving platform
	bool m_onMovingPlatform = false;
	RefPtr<MovingPlatform> m_Movingplatform = nullptr;

	// Boss
	bool m_onBoss = false;
	RefPtr<Boss> m_ptrBoss = nullptr;

	// Boss contact with stone
	bool m_onContactWithStone = false;
	RefPtr<Boss> m_ptrBossContactWithStone;
	RefPtr<Stone> m_ptrStoneContactWithBoss;

	// Player dung ben tren Thang may
	bool m_onElevatorButton = false;
	bool m_onElevator = false;
	RefPtr<Elevator> m_ptrElevator;

	// Stone va cham voi player
	bool m_onPlayerOnContactWithStone = false;
	RefPtr<Player> m_playerOnContactWithStone;
	RefPtr<Stone> m_stoneOnContactWithPlayer;

	bool m_bPlayerEffect = false;

	float m_fPreTimeEffectLand = -1;
};

