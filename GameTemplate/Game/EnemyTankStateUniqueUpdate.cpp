#include "stdafx.h"
#include "EnemyTankStateUniqueUpdate.h"

#include "EnemyTankEntity.h"
#include "EnemyTankAttributeBase.h"

//初期化
void EnemyTankStateUniqueUpdate::Enter()
{
	m_enemyTankAttribute->EnterUnique();
}

//更新
void EnemyTankStateUniqueUpdate::Update()
{
	if (m_enemyTankAttribute == nullptr)
	{
		return;
	}

	Vector3 moveDir	= m_enemyTankAttribute->UpdateUnique();

	m_hostEnemyTankEntity->SetMoveDirection(moveDir);
}

//ステート遷移
bool EnemyTankStateUniqueUpdate::RequestState(uint32_t& reqest)
{
	if (m_enemyTankAttribute == nullptr)
	{
		return false;
	}

	if (m_enemyTankAttribute->RequestStateUnique(reqest) == true)
	{
		return true;
	}
	return false;
}

//終了
void EnemyTankStateUniqueUpdate::Exit()
{
	m_enemyTankAttribute->EndUnique();
}
