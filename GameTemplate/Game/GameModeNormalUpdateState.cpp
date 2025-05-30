#include "stdafx.h"
#include "GameModeNormalUpdateState.h"

#include "GameLoadingScreen.h"

#include "GameMapManager.h"
#include "GameCameraManager.h"
#include "TankShellsManager.h"
#include "GamePlayer.h"
#include "GameCollisionManager.h"
#include "EnemyTankManager.h"

//ゲームステート初期化
void GameModeNormalUpdateState::Enter()
{
	//ロード画面のインスタンスを取得
	m_gameLoad = FindGO<GameLoadingScreen>("gameLoad");
}

//ゲームステート更新
void GameModeNormalUpdateState::Update()
{
	GameCameraManager::GetGameCameraManagerInstance()->UpdateGameCameraManager();

	TankShellsManager::GetTankShellsManagerInstance()->UpdateTankShellsManager();

	EnemyTankManager::GetEnemyTankManagerInstance()->UpdateEnemyTankManager();

	GameCollisionManager::GetCollisionManagerInstance()->UpdateCollisionManager();
}

void GameModeNormalUpdateState::Exit()
{
	
}

bool GameModeNormalUpdateState::RequestState(uint32_t& request)
{
	return false;
}

//オブジェクトロード
void GameModeNormalUpdateState::LoadGameObject()
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
}

