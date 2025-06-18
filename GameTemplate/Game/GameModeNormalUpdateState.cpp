#include "stdafx.h"
#include "GameModeNormalUpdateState.h"

#include "GameLoadingScreen.h"

#include "GameMapManager.h"
#include "GameCameraManager.h"
#include "TankShellsManager.h"
#include "GamePlayerManager.h"
#include "GameCollisionManager.h"
#include "EnemyTankManager.h"
#include "WaveManager.h"

#include "EventManager.h"

#include "WaveData.h"

//ゲームステート初期化
void GameModeNormalUpdateState::Enter()
{
	//ロード画面のインスタンスを取得
	m_gameLoad = FindGO<GameLoadingScreen>("gameLoad");
}

//ゲームステート更新
void GameModeNormalUpdateState::Update()
{
	switch (m_gameState)
	{
	case GameModeNormalUpdateState::GameNormalState::en_waitLoadEnd:

		//ロードが終わるまではプレイヤーは動けない
		GamePlayerManager::GetGamePlayerManagerInstance()->SetIsGamePlayerCanMoving(false);

		if (m_gameLoad->IsLoadCompletion() == true)
		{
			//ステート初期化
			GameModeInit();

			m_gameState = GameNormalState::en_waveStandby;
		}

		break;
	case GameModeNormalUpdateState::GameNormalState::en_waveStandby:

		//ここにウェーブの演出などを入れる

		//この時点でプレーヤーは移動可能
		GamePlayerManager::GetGamePlayerManagerInstance()->SetIsGamePlayerCanMoving(true);

		//演出などが終わったらステートを変更
		m_gameState = GameNormalState::en_waveUpdate;

		break;
	case GameModeNormalUpdateState::GameNormalState::en_waveUpdate:

		//ゲームを更新
		GameUpdate();

		//ウェーブ終了イベントが発光されるまで

		break;
	case GameModeNormalUpdateState::GameNormalState::en_waveEnd:
		break;
	default:
		break;
	}


}

void GameModeNormalUpdateState::Exit()
{
	
}

bool GameModeNormalUpdateState::RequestState(uint32_t& request)
{
	return false;
}

void GameModeNormalUpdateState::GameModeInit()
{
	EventManager::GetEventManagerInstance()->Subscribe<WaveData::WaveEndEvent>(
		[](const WaveData::WaveEndEvent& eventData)
		{
			m_gameState = GameNormalState::en_waveEnd;
		}
	);
}

void GameModeNormalUpdateState::GameUpdate()
{

	GameCameraManager::GetGameCameraManagerInstance()->UpdateGameCameraManager();

	TankShellsManager::GetTankShellsManagerInstance()->UpdateTankShellsManager();

	EnemyTankManager::GetEnemyTankManagerInstance()->UpdateEnemyTankManager();

	WaveManager::GetWaveManagerInstance()->UpdateWaveManager();

	GameCollisionManager::GetCollisionManagerInstance()->UpdateCollisionManager();
}




