#include "stdafx.h"
#include "GameModeNormalUpdateState.h"

#include "GameLoadingScreen.h"

#include "GameMapManager.h"
#include "GameCameraManager.h"
#include "TankShellsManager.h"
#include "GamePlayerManager.h"
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
	if (m_gameLoad->IsLoadCompletion() == true)
	{
		GamePlayerManager::GetGamePlayerManagerInstance()->SetIsGamePlayerCanMoving(true);
	}
	else
	{
		GamePlayerManager::GetGamePlayerManagerInstance()->SetIsGamePlayerCanMoving(false);
	}

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

