#include "stdafx.h"
#include "GamePlayer.h"

#include "TankMovingComponent.h"

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

	characterController.Init(5.0f, 5.0f, m_pos);

	

	m_tankMovingComponent->InitTankMoveingData(
		padVector,
		m_forward,
		maxMoveSpeed,
		acceleration,
		deceleration,
		friction,
		characterController,
		rotSpeed,
		m_tankCrawkerTrack
	);

	return true;
}

//アップデート関数
void GamePlayer::Update()
{
	float pad_x = g_pad[0]->GetLStickXF();
	float pad_y = g_pad[0]->GetLStickYF();

	padVector.x = pad_x;
	padVector.z = pad_y;

	m_tankMovingComponent->CalcValueAndModelUpdate();

	m_tankCrawkerTrack.Update();
}

//レンダリング関数
void GamePlayer::Render(RenderContext& rc)
{

	//履帯描画
	m_tankCrawkerTrack.Draw(rc);

}
