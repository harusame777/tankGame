#include "stdafx.h"
#include "EnemyTankStateMoveUpdate.h"

#include "EnemyTankEntity.h"
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
void EnemyTankStateMoveUpdate::Enter()
{

}

//更新
void EnemyTankStateMoveUpdate::Update()
{
	if (m_attackPoint == nullptr)
	{
		//アタックポイントを取得
		m_attackPoint = EnemyAttackPointManager::GetEnemyAttackPointManagerInstance()
			->GetEnemyNearAttackPoint(m_hostEnemyTankEntity);
	}

	//アタックポイントの座標と自身の座標で方向を計算
	Vector3 moveVec = m_attackPoint->GetPosition() - m_hostEnemyTankEntity->GetPosition();
	moveVec.Normalize();

	m_hostEnemyTankEntity->SetMoveDirection(moveVec);
}


//終了
void EnemyTankStateMoveUpdate::Exit()
{
	//アタックポイントを初期化
	m_attackPoint = nullptr;
}

//ステート遷移
bool EnemyTankStateMoveUpdate::RequestState(uint32_t& request)
{
	if (IsAttackPointInRadius() == true)
	{
		request = EnemyTankStateAttackMoveUpdate::ID();

		return true;
	}

	return false;
}

//アタックポイント内にホストタンクが入っているかどうか
bool EnemyTankStateMoveUpdate::IsAttackPointInRadius()
{
	const float attackPointRadiusSq = m_attackPoint->GetRadiusSq();

	//ホストタンクのポジション
	const Vector3 hostEnemyTankPos = m_hostEnemyTankEntity->GetPosition();
	//プレイヤーのポジション
	const Vector3 attackPointPos = m_attackPoint->GetPosition();
	//ホストタンクからプレイヤーへ向かうベクトル(2Dベクトルとして考える)
	const float distX = attackPointPos.x - hostEnemyTankPos.x;
	const float distY = attackPointPos.y - hostEnemyTankPos.y;
	//ホストタンクとプレイヤーの半径
	const float hostEnemyTankToAttackPointRangeSq = distX * distX + distY * distY;


	if (attackPointRadiusSq >= hostEnemyTankToAttackPointRangeSq)
	{
		return true;
	}

	return false;
}
