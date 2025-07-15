#include "stdafx.h"
#include "GameMainCamera.h"
#include "GamePlayer.h"
#include "GamePlayerManager.h"

//定数
namespace GameMainCameraConstant
{
	
}

//カメラ初期化
bool GameMainCamera::InitCamera()
{
	m_gamePlayer = GamePlayerManager::GetGamePlayerManagerInstance()->GetGamePlayerInstance();

	float cameraNear = 1.0f;
	float cameraFar = 10000.0f;

	m_cameraUpdateData->m_near = cameraNear;
	m_cameraUpdateData->m_far = cameraFar;

	Vector3 target = m_gamePlayer->GetPosition();
	Vector3 add = { 0.0f, 1000.0f, -100.0f };

	Vector3 cameraPos = target + add;

	m_cameraUpdateData->m_position = cameraPos;
	m_cameraUpdateData->m_targetPosition = target;

	return true;
}

//カメラ更新
void GameMainCamera::UpdateCamera()
{
	Vector3 target = m_gamePlayer->GetPosition();
	Vector3 add = { 0.0f, 1000.0f, -100.0f };

	Vector3 cameraPos = target + add;

	m_cameraUpdateData->m_position = cameraPos;
	m_cameraUpdateData->m_targetPosition = target;
}

