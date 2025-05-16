#include "stdafx.h"
#include "EnemyTankStateMoveUpdate.h"

#include "EnemyTankEntity.h"
#include "EnemyAttackPointManager.h"
#include "EnemyAttackPoint.h"

//コンストラクタ
//EnemyTankStateMoveUpdate::EnemyTankStateMoveUpdate(EnemyTankEntity* hostEnemyTank)
//{
//	m_hostEnemyTankEntity = hostEnemyTank;
//}

//初期化
void EnemyTankStateMoveUpdate::Enter()
{

}

//更新
void EnemyTankStateMoveUpdate::Update()
{
	EnemyAttackPoint* attackPoint = nullptr;

	attackPoint = EnemyAttackPointManager::GetTankShellsManagerInstance()
		->GetEnemyNearAttackPoint(m_hostEnemyTankEntity);

	if (attackPoint == nullptr)
	{
		return;
	}

	Vector3 moveVec = attackPoint->GetPosition() - m_hostEnemyTankEntity->GetPosition();
	moveVec.Normalize();

	m_hostEnemyTankEntity->SetMoveDirection(moveVec);
}

//終了
void EnemyTankStateMoveUpdate::Exit()
{

}

//ステート遷移
bool EnemyTankStateMoveUpdate::RequestState(uint32_t& request)
{
	return false;
}