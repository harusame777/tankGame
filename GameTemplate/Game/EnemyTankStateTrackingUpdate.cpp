#include "stdafx.h"
#include "EnemyTankStateTrackingUpdate.h"

#include "EnemyTankEntity.h"
#include "EnemyTankAttributeBase.h"

//初期化
void EnemyTankStateTrackingUpdate::Enter()
{
	m_enemyTankAttribute->EnterTracking();
}

//更新
void EnemyTankStateTrackingUpdate::Update()
{
	if (m_enemyTankAttribute == nullptr)
	{
		return;
	}

	m_hostEnemyTankEntity->SetMoveDirection(
		m_enemyTankAttribute->UpdateTracking());
}


//終了
void EnemyTankStateTrackingUpdate::Exit()
{
	m_enemyTankAttribute->EndTracking();
}

//ステート遷移
bool EnemyTankStateTrackingUpdate::RequestState(uint32_t& request)
{
	if (m_enemyTankAttribute == nullptr)
	{
		return false;
	}

	if (m_enemyTankAttribute->RequestStateTracking(request) == true)
	{
		return true;
	}

	return false;
}

