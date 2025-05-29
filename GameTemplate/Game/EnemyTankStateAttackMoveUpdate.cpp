#include "stdafx.h"
#include "EnemyTankStateAttackMoveUpdate.h"

#include "EnemyTankEntity.h"
#include "EnemyTankAttributeBase.h"

//初期化
void EnemyTankStateAttackMoveUpdate::Enter()
{
	m_enemyTankAttribute->EnterAttackMove();
}

//更新
void EnemyTankStateAttackMoveUpdate::Update()
{
	if (m_enemyTankAttribute == nullptr)
	{
		return;
	}

	Vector3 moveDir = m_enemyTankAttribute->UpdateAttackMove();

	m_hostEnemyTankEntity->SetMoveDirection(moveDir);
}

//終了
void EnemyTankStateAttackMoveUpdate::Exit()
{
	m_enemyTankAttribute->EndAttackMove();
}

//ステート遷移
bool EnemyTankStateAttackMoveUpdate::RequestState(uint32_t& request)
{
	if (m_enemyTankAttribute == nullptr)
	{
		return false;
	}

	if (m_enemyTankAttribute->RequestStateAttackMove(request) == true)
	{
		return true;
	}

	return false;
}