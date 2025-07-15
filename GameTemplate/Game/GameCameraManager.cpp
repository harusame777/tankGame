#include "stdafx.h"
#include "GameCameraManager.h"

//カメラのインクルード
#include "GameMainCamera.h"
#include "GameCameraObjectBase.h"

//インスタンスを初期化
GameCameraManager* GameCameraManager::m_gameCameraManagerInstance = nullptr;

//スタート関数
void GameCameraManager::InitGameCameraManager()
{
	//カメラのインスタンス化とリスト登録
	//メインカメラ
	GameMainCamera* mainCamera = new GameMainCamera(&m_cameraUpdateData,g_camera3D);
	AddGameCameraList(mainCamera);

	//リストのインスタンスの初期化を行う
	for (auto& listPtr : m_gameCameraList)
	{
		listPtr->InitCamera();
	}

	//ステートによって実行された更新情報から得た数値でカメラを更新する
	g_camera3D->SetTarget(m_cameraUpdateData.m_targetPosition);
	g_camera3D->SetPosition(m_cameraUpdateData.m_position);
	g_camera3D->SetNear(m_cameraUpdateData.m_near);
	g_camera3D->SetFar(m_cameraUpdateData.m_far);
	g_camera3D->Update();
}

//アップデート関数
void GameCameraManager::UpdateGameCameraManager()
{
	//ステートによって座標等を更新する
	m_gameCameraList[m_cameraModeState]->UpdateCamera();

	//ステートによって実行された更新情報から得た数値でカメラを更新する
	g_camera3D->SetTarget(m_cameraUpdateData.m_targetPosition);
	g_camera3D->SetPosition(m_cameraUpdateData.m_position);
	g_camera3D->SetNear(m_cameraUpdateData.m_near);
	g_camera3D->SetFar(m_cameraUpdateData.m_far);
	g_camera3D->Update();
}