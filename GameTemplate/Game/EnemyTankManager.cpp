#include "stdafx.h"
#include "EnemyTankManager.h"

#include "EnemyTankEntity.h"

//インスタンス初期化
EnemyTankManager* EnemyTankManager::m_enemyTankManagerInstance = nullptr;

void EnemyTankManager::CreateNewEnemyTank(

)
{

	EnemyTankEntity* newTankPtr = NewGO<EnemyTankEntity>(0, "enemyTank");

}

//初期化
void EnemyTankManager::InitEnemyTankManager()
{

}

//更新
void EnemyTankManager::UpdateEnemyTankManager()
{

}