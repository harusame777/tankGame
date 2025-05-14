#include "stdafx.h"
#include "EnemyTankStateMoveUpdate.h"

#include "EnemyTankEntity.h"

//コンストラクタ
EnemyTankStateMoveUpdate::EnemyTankStateMoveUpdate(EnemyTankEntity* hostEnemyTank)
{
	m_hostEnemyTankEntity = hostEnemyTank;
}

//初期化
void EnemyTankStateMoveUpdate::Enter()
{

}

//更新
void EnemyTankStateMoveUpdate::Update()
{

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