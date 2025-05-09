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
	//ゲームカメラのマネージャーを作成
	m_gameCameraManager = NewGO<GameCameraManager>(0, "gameCamManager");
	//ゲームマップのマネージャーを作成
	m_gameMapManager = NewGO<GameMapManager>(0, "gameMapManager");
	//ゲームプレイヤーを作成
	m_gamePlayer = NewGO<GamePlayer>(0, "gamePlayer");
	//砲弾マネージャーを作成
	m_tankShellsManager = NewGO<TankShellsManager>(0, "tankShellsManager");

	GameCollisionManager::GetCollisionManagerInstance()->InitCollisionManager();
}

//ゲームアップデート
void GameIn::GameUpdate()
{

	GameCollisionManager::GetCollisionManagerInstance()->UpdateCollisionManager();

}