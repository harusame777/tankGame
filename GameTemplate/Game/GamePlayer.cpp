#include "stdafx.h"
#include "GamePlayer.h"

#include "TankCrawkerMovingComponent.h"
#include "TankTurretMovingComponent.h"
#include "TankShellsManager.h"
#include "TankShellsAttribute.h"

#include "GameCollisionManager.h"

#include "EnemyAttackPointManager.h"

#include "EnemyTankManager.h"

#include "EnemyTankAttribute.h"

namespace GamePlayerTankConstant 
{
}

//スタート関数
bool GamePlayer::Start()
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

	m_tankMovingComponent = new TankCrawkerMovingComponent;

	m_tankTurretMovingComponent = new TankTurretMovingComponent;

	characterController.Init(5.0f, 5.0f, m_position);

	m_tankMovingComponent->InitTankCrawkerMoveingData(
		padLVector,
		m_forward,
		maxMoveSpeed,
		characterController,
		rotSpeed,
		m_tankCrawkerTrack
	);

	m_tankTurretMovingComponent->InitTankTurretMovingData(
		padRVector,
		m_position,
		m_forward,
		rotSpeed,
		m_tankTurret
	);

	EnemyAttackPointManager::GetEnemyAttackPointManagerInstance()->CreateEnemyAttackPoints(
		m_position,
		100.0f,
		150.0f,
		100
	);

	return true;
}

//アップデート関数
void GamePlayer::Update()
{
	//ロード中等では動かないように
	if (m_playerState == EnPlayerState::en_standby)
	{
		return;
	}

	float pad_x = g_pad[0]->GetLStickXF();
	float pad_y = g_pad[0]->GetLStickYF();

	padLVector.x = pad_x;
	padLVector.z = pad_y;

	m_position = m_tankMovingComponent->CalcCrawkerMovingDataAndModelUpdate();

	pad_x = g_pad[0]->GetRStickXF();
	pad_y = g_pad[0]->GetRStickYF();

	padRVector.x = pad_x;
	padRVector.z = pad_y;

	m_turretPosition = m_tankTurretMovingComponent->CalcTurretMovingDataAndModelUpdate();

	if (g_pad[0]->IsTrigger(enButtonB))
	{
		TankShellsManager::GetTankShellsManagerInstance()->RequestFiringTankShells(
			EnTankShellsAttribute::en_normal,
			m_tankTurretMovingComponent->GetCannonFiringPosition(),
			m_tankTurretMovingComponent->GetTurretForward()
		);
	}

	m_tankCrawkerTrack.Update();
	m_tankTurret.Update();

	EnemyAttackPointManager::GetEnemyAttackPointManagerInstance()->UpdateEnemyAttackPoints();

	if (g_pad[0]->IsTrigger(enButtonDown))
	{
		EnemyTankManager::GetEnemyTankManagerInstance()->CreateNewEnemyTank(
			EnEnemyTankAttribute::en_tankNormal,
			{ 400.0f,0.0f,400.0f }
		);
	}
}

//レンダリング関数
void GamePlayer::Render(RenderContext& rc)
{

	//履帯描画
	m_tankCrawkerTrack.Draw(rc);
	//砲塔描画
	m_tankTurret.Draw(rc);

}
