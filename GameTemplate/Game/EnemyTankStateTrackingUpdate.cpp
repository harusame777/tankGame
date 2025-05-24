#include "stdafx.h"
#include "EnemyTankStateTrackingUpdate.h"

#include "EnemyTankEntity.h"
#include "EnemyTankAttributeBase.h"
#include "EnemyAttackPointManager.h"
#include "EnemyAttackPoint.h"
#include "GamePlayer.h"
#include "EnemyTankStateAttackMoveUpdate.h"

//コンストラクタ
//EnemyTankStateMoveUpdate::EnemyTankStateMoveUpdate(EnemyTankEntity* hostEnemyTank)
//{
//	m_hostEnemyTankEntity = hostEnemyTank;
//}

//初期化
void EnemyTankStateTrackingUpdate::Enter()
{

}

//更新
void EnemyTankStateTrackingUpdate::Update()
{
	if (m_enemyTankAttribute == nullptr)
	{
		return;
	}

	if (m_attackPoint == nullptr)
	{
		m_attackPoint = EnemyAttackPointManager::
			GetEnemyAttackPointManagerInstance()->GetEnemyNearAttackPoint(m_hostEnemyTankEntity);
	}

	//アタックポイントの座標と自身の座標で方向を計算
	Vector3 moveVec = m_enemyTankAttribute->TrackingAttribute();

	m_hostEnemyTankEntity->SetMoveDirection(moveVec);
}


//終了
void EnemyTankStateTrackingUpdate::Exit()
{

}

//ステート遷移
bool EnemyTankStateTrackingUpdate::RequestState(uint32_t& request)
{
	if (m_enemyTankAttribute == nullptr)
	{
		return false;
	}

	if (m_enemyTankAttribute->RequestStateTrackingAttribute(request) == true)
	{
		return true;
	}

	return false;
}

