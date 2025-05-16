#include "stdafx.h"
#include "GameIn.h"

#include "GameMapManager.h"
#include "GameCameraManager.h"
#include "TankShellsManager.h"
#include "GamePlayer.h"
#include "GameCollisionManager.h"
#include "EnemyTankManager.h"

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
	//エネミータンクマネージャークラスを作成
	EnemyTankManager::GetEnemyTankManagerInstance()->InitEnemyTankManager();
	//コリジョンマネージャーを作成
	GameCollisionManager::GetCollisionManagerInstance()->InitCollisionManager();

	EnemyTankManager::GetEnemyTankManagerInstance()->CreateNewEnemyTank({ 400.0f,0.0f,400.0f });
}

//ゲームアップデート
void GameIn::GameUpdate()
{
	GameCameraManager::GetGameCameraManagerInstance()->UpdateGameCameraManager();

	TankShellsManager::GetTankShellsManagerInstance()->UpdateTankShellsManager();

	EnemyTankManager::GetEnemyTankManagerInstance()->UpdateEnemyTankManager();

	GameCollisionManager::GetCollisionManagerInstance()->UpdateCollisionManager();
}