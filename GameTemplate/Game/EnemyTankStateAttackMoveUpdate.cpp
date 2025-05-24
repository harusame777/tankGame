#include "stdafx.h"
#include "EnemyTankStateAttackMoveUpdate.h"

#include "EnemyTankEntity.h"
#include "EnemyTankAttributeBase.h"
#include "GamePlayer.h"
#include "EnemyAttackPointManager.h"
#include "EnemyAttackPoint.h"

//初期化
void EnemyTankStateAttackMoveUpdate::Enter()
{

}

//更新
void EnemyTankStateAttackMoveUpdate::Update()
{
	if (m_enemyTankAttribute == nullptr)
	{
		return;
	}

	Vector3 moveDir = m_enemyTankAttribute->AttackMoveAttribute();

	m_hostEnemyTankEntity->SetMoveDirection(moveDir);
}

//終了
void EnemyTankStateAttackMoveUpdate::Exit()
{

}

//ステート遷移
bool EnemyTankStateAttackMoveUpdate::RequestState(uint32_t& request)
{
	if (m_enemyTankAttribute == nullptr)
	{
		return false;
	}

	if (m_enemyTankAttribute->RequestStateAttackMoveAttribute(request) == true)
	{
		return true;
	}

	return false;
}