#include "stdafx.h"
#include "GamePlayer.h"

#include "TankMovingComponent.h"
#include "TankTurretMovingComponent.h"

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

	m_tankMovingComponent = new TankMovingComponent;

	m_tankTurretMovingComponent = new TankTurretMovingComponent;

	characterController.Init(5.0f, 5.0f, m_position);

	m_tankMovingComponent->InitTankMoveingData(
		padLVector,
		m_forward,
		maxMoveSpeed,
		acceleration,
		deceleration,
		friction,
		characterController,
		rotSpeed,
		m_tankCrawkerTrack
	);

	m_tankTurretMovingComponent->InitTankTurretMovingData(
		padRVector,
		m_position,
		m_forward,
		m_turretForward,
		rotSpeed,
		m_tankTurret
	);

	return true;
}

//アップデート関数
void GamePlayer::Update()
{
	float pad_x = g_pad[0]->GetLStickXF();
	float pad_y = g_pad[0]->GetLStickYF();

	padLVector.x = pad_x;
	padLVector.z = pad_y;

	m_position = m_tankMovingComponent->CalcValueAndModelUpdate();

	pad_x = g_pad[0]->GetRStickXF();
	pad_x = g_pad[0]->GetRStickYF();

	padRVector.x = pad_x;
	padRVector.z = pad_y;

	m_turretPosition = m_tankTurretMovingComponent->CalcValueAndModelUpdate();

	m_tankCrawkerTrack.Update();

	m_tankTurret.Update();
}

//レンダリング関数
void GamePlayer::Render(RenderContext& rc)
{

	//履帯描画
	m_tankCrawkerTrack.Draw(rc);

	m_tankTurret.Draw(rc);

}
