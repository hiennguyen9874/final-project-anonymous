#include "ContacListener.h"
#include "AudioEngine.h"
#include "SoundMgr.h"

using namespace experimental;

void ContacListener::BeginContact(b2Contact* contact)
{
	this->m_onSpine = false;

	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	TypeObject* oA = (TypeObject*)contact->GetFixtureA()->GetUserData();
	TypeObject* oB = (TypeObject*)contact->GetFixtureB()->GetUserData();

	if (fixtureA->GetFilterData().categoryBits == 0x03 || (fixtureB->GetFilterData().categoryBits == 0x03))
	{
		if (GameValue::getInstance()->getUsedItem() != 0)
			this->m_onSpine = true;
		else
			this->m_onSpine = false;
		this->m_onMovingPlatform = false;
		this->m_onElevator = false;
	}

	if (oA != nullptr && oA->idObject == IdChanPlayer)
	{
		//int id = experimental::AudioEngine::play2d("audios/effects/king_land.mp3");
		//experimental::AudioEngine::setVolume(id, SoundMgr::getInstance()->GetVolumeEffect());

		this->m_bPlayerEffect = true;
		this->m_numOfContact++;
		this->m_onMovingPlatform = false;
		this->m_onElevator = false;
	}

	if (oB != nullptr && oB->idObject == IdChanPlayer)
	{
		//int id = experimental::AudioEngine::play2d("audios/effects/king_land.mp3");
		//experimental::AudioEngine::setVolume(id, SoundMgr::getInstance()->GetVolumeEffect());

		this->m_bPlayerEffect = true;
		this->m_numOfContact++;
		this->m_onMovingPlatform = false;
		this->m_onElevator = false;
	}

	if (((oA != nullptr && oA->idObject == IdTayPlayer) && !this->CanJump() && fixtureB->GetFilterData().categoryBits == 0x05))
	{
		this->m_isBoucing = true;
	}
	if (((oB != nullptr && oB->idObject == IdTayPlayer) && !this->CanJump() && fixtureA->GetFilterData().categoryBits == 0x05))
	{
		this->m_isBoucing = true;
	}

	if (oA == nullptr || oB == nullptr)
		return;

	// Player dam trung con boss
	if (oA->idObject == IdBodyPlayer && oB->idObject == IdBoss)
	{
		this->m_onBoss = true;
		this->m_ptrBoss = (Boss *)oB->ptr;
	}
	else if (oA->idObject == IdBoss && oB->idObject == IdBodyPlayer)
	{
		this->m_onBoss = true;
		this->m_ptrBoss = (Boss *)oA->ptr;
	}

	// Stone dam trung con Boss
	if (oA->idObject == IdStone && oB->idObject == IdBoss)
	{
		this->m_onContactWithStone = true;
		this->m_ptrStoneContactWithBoss = (Stone *)oA->ptr;
		this->m_ptrBossContactWithStone = (Boss *)oB->ptr;
	}
	else if (oA->idObject == IdBoss && oB->idObject == IdStone)
	{
		this->m_onContactWithStone = true;
		this->m_ptrBossContactWithStone = (Boss *)oA->ptr;
		this->m_ptrStoneContactWithBoss = (Stone *)oB->ptr;
	}

	// Stone va cham voi player
	if (oA->idObject == IdStone && oB->idObject == IdBodyPlayer)
	{
		this->m_onPlayerOnContactWithStone = true;
		this->m_playerOnContactWithStone = (Player *)oB->ptr;
		this->m_stoneOnContactWithPlayer = (Stone *)oA->ptr;
	}
	else if (oA->idObject == IdBodyPlayer && oB->idObject == IdStone)
	{
		this->m_onPlayerOnContactWithStone = true;
		this->m_playerOnContactWithStone = (Player *)oA->ptr;
		this->m_stoneOnContactWithPlayer = (Stone *)oB->ptr;
	}
	
	// Player tren elevator
	if (oA->idObject == IdChanPlayer && oB->idObject == IdButtonElevator)
	{
		this->m_onElevatorButton = true;
		this->m_onElevator = true;
		this->m_ptrElevator = (Elevator *)oB->ptr;
	}
	else if (oA->idObject == IdButtonElevator && oB->idObject == IdChanPlayer)
	{
		this->m_onElevatorButton = true;
		this->m_onElevator = true;
		this->m_ptrElevator = (Elevator *)oA->ptr;
	}

	// Player dung tren moving platform
	if (oA->idObject == IdMovingPlatfrom && oB->idObject == IdChanPlayer)
	{
		this->m_onMovingPlatform = true;
		this->m_Movingplatform = (MovingPlatform *)(oA->ptr);
	}
	else if (oB->idObject == IdMovingPlatfrom && oA->idObject == IdChanPlayer)
	{
		this->m_onMovingPlatform = true;
		this->m_Movingplatform = (MovingPlatform *)(oB->ptr);
	}

	// Player va cham voi enemy
	if (oA->idObject == IdEnemy && oB->idObject == IdBodyPlayer && GameValue::getInstance()->getUsedItem() != 2)
	{
		if (GameValue::getInstance()->getUsedSlingShot() == 3 && !this->CanJump())
		{
			this->m_onEnemy = false;
		}
		else
		{
			this->m_onEnemy = true;
			this->m_Enemy = (Enemy *)oA->ptr;
		}
	}
	else if (oA->idObject == IdBodyPlayer && oB->idObject == IdEnemy && GameValue::getInstance()->getUsedItem() != 2)
	{
		if (GameValue::getInstance()->getUsedSlingShot() == 3 && !this->CanJump())
		{
			this->m_onEnemy = false;
		}
		else
		{
			this->m_onEnemy = true;
			this->m_Enemy = (Enemy *)oA->ptr;
		}
	}

	// Player va cham voi enemy voi fire slingshot
	if (oB->idObject == IdBodyPlayer && oA->idObject == IdEnemy
		&& GameValue::getInstance()->getUsedSlingShot() == 2)
	{
		this->m_onEnemy = false;
		this->m_Enemy = (Enemy *)oA->ptr;
	}
	else if (oA->idObject == IdBodyPlayer && oB->idObject == IdEnemy
		&& GameValue::getInstance()->getUsedSlingShot() == 2)
	{
		this->m_onEnemy = false;
		this->m_Enemy = (Enemy *)oB->ptr;
	}

	// Player va cham voi check point
	if (oA->idObject == IdChanPlayer && oB->idObject == IdCheckPoint)
	{
		this->m_positionCollision.x = fixtureB->GetBody()->GetPosition().x * 32.0;
		this->m_positionCollision.y = fixtureB->GetBody()->GetPosition().y * 32.0;
		CheckPoint* objectB = (CheckPoint*)oB->ptr;
		Player* objectA = (Player*)oA->ptr;
		this->m_CheckPoint = objectB;
	}
	else if (oA->idObject == IdCheckPoint && oB->idObject == IdChanPlayer)
	{
		this->m_positionCollision.x = fixtureA->GetBody()->GetPosition().x * 32.0;
		this->m_positionCollision.y = fixtureA->GetBody()->GetPosition().y * 32.0;
		CheckPoint* objectA = (CheckPoint*)oA->ptr;
		Player* objectB = (Player*)oB->ptr;
		this->m_CheckPoint = objectA;
	}

	// Player va cham voi Diamond
	if (oA->idObject == IdGold && oB->idObject == IdChanPlayer)
	{
		Player* objectB = (Player*)oB->ptr;
		Gold* objectA = (Gold*)oA->ptr;
		this->m_diamondContact = objectA;
		GameValue::getInstance()->cornScore++;
	}
	else if (oA->idObject == IdChanPlayer && oB->idObject == IdGold)
	{
		Player* objectA = (Player*)oA->ptr;
		Gold* objectB = (Gold*)oB->ptr;
		this->m_diamondContact = objectB;
		GameValue::getInstance()->cornScore++;
	}

	// Player va cham voi Ruong bau vat
	if (oA->idObject == IdTreasureChest && oB->idObject == IdBodyPlayer)
	{
		Player* objectB = (Player*)oB->ptr;
		TreasureChest* objectA = (TreasureChest*)oA->ptr;
		this->m_treasureChest = objectA;
	}
	else if (oA->idObject == IdBodyPlayer && oB->idObject == IdTreasureChest)
	{
		Player* objectA = (Player*)oA->ptr;
		TreasureChest* objectB = (TreasureChest*)oB->ptr;
		this->m_treasureChest = objectB;
	}
	//Dung cai tu`
	if (oA->idObject == IdJail && oB->idObject == IdBodyPlayer)
	{
		this->m_contactWithJail = true;
	}
	else if (oA->idObject == IdBodyPlayer && oB->idObject == IdJail)
	{
		this->m_contactWithJail = true;
	}

}

void ContacListener::EndContact(b2Contact* contact)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	TypeObject* oA = (TypeObject*)contact->GetFixtureA()->GetUserData();
	TypeObject* oB = (TypeObject*)contact->GetFixtureB()->GetUserData();

	if (oA != nullptr && oA->idObject == IdChanPlayer)
		this->m_numOfContact--;
	if (oB != nullptr && oB->idObject == IdChanPlayer)
		this->m_numOfContact--;
}

void ContacListener::PreSolve(b2Contact * contact, const b2Manifold * oldManifold)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	if ((fixtureA->GetFilterData().categoryBits == 0x98 && fixtureB->GetFilterData().categoryBits == 0x05))
		this->m_linearVelocityPlayer = fixtureA->GetBody()->GetLinearVelocity();

	if ((fixtureB->GetFilterData().categoryBits == 0x98 && fixtureA->GetFilterData().categoryBits == 0x05))
		this->m_linearVelocityPlayer = fixtureB->GetBody()->GetLinearVelocity();
}

int ContacListener::GetNumOfContact()
{
	return this->m_numOfContact;
}

Vec2 ContacListener::GetCollisionPoint()
{
	return this->m_positionCollision;
}

bool ContacListener::GetOnSpineVariable()
{
	return this->m_onSpine;
}

void ContacListener::SetOnSpineVariable(bool bOnSpineVaiable)
{
	this->m_onSpine = bOnSpineVaiable;
}

bool ContacListener::CanJump()
{
	if (this->m_numOfContact < 1)
		return false;
	return true;
}

void ContacListener::SetIsPlayerEffectLand(bool isPlayerEffectLand)
{
	this->m_bPlayerEffect = isPlayerEffectLand;
}

bool ContacListener::CheckBoucing()
{
	return this->m_isBoucing;
}

void ContacListener::ReFalseIsBoucing()
{
	this->m_isBoucing = false;
}
