#include "stdafx.h"
#include "GameLoadOrDeleteState.h"
#include "GameLoadingScreen.h"

#include "GameMapManager.h"
#include "GameCameraManager.h"
#include "TankShellsManager.h"
#include "GamePlayerManager.h"
#include "GameCollisionManager.h"
#include "EnemyTankManager.h"
#include "WaveManager.h"
#include "GameUiManager.h"

#include "GameModeNormalUpdateState.h"

#include "GameUiLog.h"
#include "GameUiEnemyCount.h"

//初期化
void GameLoadOrDeleteState::Enter()
{
	//ロード画面のインスタンスを取得
	m_gameLoad = FindGO<GameLoadingScreen>("gameLoad");
	//ロード完了
	m_processEndFlag = false;
}

//更新
void GameLoadOrDeleteState::Update()
{
	switch (*m_loadOrDelete)
	{
	case GameMain::LoadOrDelete::en_modeLoad:

		LoadProcces();

		break;
	case GameMain::LoadOrDelete::en_modeDelete:

		DeleteProcces();

		break;
	default:
		break;
	}

}

void GameLoadOrDeleteState::Exit()
{

}

bool GameLoadOrDeleteState::RequestState(uint32_t& request)
{
	if (*m_loadOrDelete == GameMain::LoadOrDelete::en_modeLoad &&
		m_processEndFlag == true)
	{
		m_gameLoad->LoadExecutionFadeIn();

		request = GameModeNormalUpdateState::ID();

		return true;
	}

	if (*m_loadOrDelete == GameMain::LoadOrDelete::en_modeDelete &&
		m_processEndFlag == true)
	{


		return true;
	}

	return false;
}

void GameLoadOrDeleteState::LoadProcces()
{
	//ゲームプレイヤーを作成
	GamePlayerManager::GetGamePlayerManagerInstance()->CreateGamePlayer();
	//ゲームカメラのマネージャーを作成
	GameCameraManager::GetGameCameraManagerInstance()->InitGameCameraManager();
	//ゲームマップのマネージャーを作成
	GameMapManager::GetCollisionManagerInstance()->InitGameMapManager();
	//砲弾マネージャーを作成
	TankShellsManager::GetTankShellsManagerInstance()->InitTankShellsManager();
	//エネミータンクマネージャークラスを作成
	EnemyTankManager::GetEnemyTankManagerInstance()->InitEnemyTankManager();
	//ウェーブマネージャークラスを作成
	WaveManager::GetWaveManagerInstance()->InitWaveManager();
	//コリジョンマネージャーを作成
	GameCollisionManager::GetCollisionManagerInstance()->InitCollisionManager();

	//テスト：UIの作成
	GameUiManager::GetGameUiManagerInstance()->CreateGameUi<GameUiEnemyCount>(0);

	//ロード完了
	m_processEndFlag = true;
}

void GameLoadOrDeleteState::DeleteProcces()
{

}