#include "stdafx.h"
#include "EnemyTankEntity.h"

#include "EnemyTankStateMachine.h"
#include "StateMachineBase.h"
#include "TankCrawkerMovingComponent.h"
#include "TankTurretMovingComponent.h"
#include "GameCollisionManager.h"

//スタート関数
bool EnemyTankEntity::Start()
{
	//履帯モデル設定
	m_tankCrawkerTrack.Init(
		"Assets/modelData/tankModel/tankModelV1_crawlerTrack.tkm",
		nullptr,
		0,
		enModelUpAxisZ,
		ModelRender::en_usuallyShader
	);

	//砲塔モデル設定
	m_tankTurret.Init(
		"Assets/modelData/tankModel/tankModelV1_turret.tkm",
		nullptr,
		0,
		enModelUpAxisZ,
		ModelRender::en_usuallyShader
	);

	//ステートマシン生成
	m_stateMashine = new EnemyTankStateMachine(this);
	//履帯コンポーネント生成
	m_tankCrawkerMovingCom = new TankCrawkerMovingComponent;
	//砲塔コンポーネント生成
	m_tankTurretMovingCom = new TankTurretMovingComponent;

	//履帯コンポーネント設定
	m_tankCrawkerMovingCom->InitTankCrawkerMoveingData(
		m_moveForward,
		m_forward,
		maxMoveSpeed,
		characterController,
		rotSpeed,
		m_tankCrawkerTrack
	);

	//砲塔コンポーネント設定
	m_tankTurretMovingCom->InitTankTurretMovingData(
		m_targetForward,
		m_position,
		m_forward,
		rotSpeed,
		m_tankTurret
	);

	//当たり判定作成
	m_collision = GameCollisionManager::GetCollisionManagerInstance()->CreateSphereCollision(
		m_position,
		m_rotation,
		1.0f,
		"EnemyCollision"
	);

	return true;
}

//アップデート関数
void EnemyTankEntity::Update()
{
	//ステートマシン更新
	m_stateMashine->Update();

	//履帯移動更新
	m_tankCrawkerMovingCom->CalcCrawkerMovingDataAndModelUpdate();
	//砲塔移動更新
	m_tankTurretMovingCom->CalcTurretMovingDataAndModelUpdate();
	
	//モデル更新
	m_tankCrawkerTrack.Update();
	m_tankTurret.Update();

	//当たり判定位置更新
	m_collision->SetPosition(m_position);
	m_collision->Update();
}

//レンダリング関数
void EnemyTankEntity::Render(RenderContext& rc)
{
	m_tankCrawkerTrack.Draw(rc);

	m_tankTurret.Draw(rc);
}