#include "stdafx.h"
#include "GameIn.h"

#include "GameMapManager.h"
#include "GameCameraManager.h"
#include "TankShellsManager.h"
#include "GamePlayer.h"
#include "GameCollisionManager.h"

//ゲームステート初期化
void GameIn::InitGameState()
{
	//ロード画面のインスタンスを取得
	m_gameLoad = FindGO<GameLoad>("gameLoad");
}

//ゲームステート更新
void GameIn::UpdateGameState()
{
	switch (m_stateNum)
	{
	case GameIn::en_objectLoad:

		LoadGameObject();

		m_gameLoad->LoadExecutionFadeIn();

		m_gameMain->ChangeContextListState(
			GameMain::en_inGame,
			GameIn::en_gameUpdate);

		break;
	case GameIn::en_gameUpdate:

		GameUpdate();

		break;
	default:
		break;
	}
}

//オブジェクトロード
void GameIn::LoadGameObject()
{
	//ゲームプレイヤーを作成
	m_gamePlayer = NewGO<GamePlayer>(0, "gamePlayer");
	//ゲームカメラのマネージャーを作成
	GameCameraManager::GetGameCameraManagerInstance()->InitGameCameraManager();
	//ゲームマップのマネージャーを作成
	GameMapManager::GetCollisionManagerInstance()->InitGameMapManager();
	//砲弾マネージャーを作成
	TankShellsManager::GetTankShellsManagerInstance()->InitTankShellsManager();
	//コリジョンマネージャーを作成
	GameCollisionManager::GetCollisionManagerInstance()->InitCollisionManager();
}

//ゲームアップデート
void GameIn::GameUpdate()
{
	GameCameraManager::GetGameCameraManagerInstance()->UpdateGameCameraManager();

	TankShellsManager::GetTankShellsManagerInstance()->UpdateTankShellsManager();

	GameCollisionManager::GetCollisionManagerInstance()->UpdateCollisionManager();
}