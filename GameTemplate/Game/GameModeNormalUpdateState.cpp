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

	std::shared_ptr<GameModeNormalUpdateState> initShared(this);

	m_gameModeNormalSharedPtr = initShared;

	SetWaveEndFlag(false);
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

		//ウェーブを生成
		WaveManager::GetWaveManagerInstance()
			->CreateAndStartWaveData(
			30,
			5.0f,
			10,
			5,
			3
		);

		//演出などが終わったらステートを変更
		m_gameState = GameNormalState::en_waveUpdate;

		break;
	case GameModeNormalUpdateState::GameNormalState::en_waveUpdate:

		WaveManager::GetWaveManagerInstance()->UpdateWaveManager();
		//ウェーブ終了イベントが発行されるまで
		SetWaveEndFlag(true);

		break;
	case GameModeNormalUpdateState::GameNormalState::en_waveEnd:

		m_gameState = GameNormalState::en_waveStandby;

		break;
	default:
		break;
	}

	m_testDirectionalLight.SetColor(1.0f, 1.0f, 1.0f);
	m_testDirectionalLight.SetDirection(1.0, 1.0f, 1.0f);
	m_testDirectionalLight.LightDirectionNormalize();
	m_testDirectionalLight.CastShadow();
	m_testDirectionalLight.VPCamSetRotation(80.0f);
	m_testDirectionalLight.VPCamSetPosition({ -10.0, 2000, 0.0 });

	Vector3 m_sunPos = { -900.0, 900, 900.0 };

	m_testDirectionalLight.VPCamSetPosition(m_sunPos);
	m_testDirectionalLight.VPCamSetTarget({0.0f,0.0f,0.0f});
	m_testDirectionalLight.VPCamUpdate();

	//ゲームを更新
	GameUpdate();
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
	//外部イベント、ウェーブ終了時に実行
	EventManager::GetEventManagerInstance()->RegisterListener<WaveEndEvent, GameModeNormalUpdateState>(
		m_gameModeNormalSharedPtr,
		[](std::shared_ptr<GameModeNormalUpdateState> obj) {
			return obj->m_waveEndGoFlag;
		},
		[](std::shared_ptr<GameModeNormalUpdateState> obj, const WaveEndEvent &evt) {
			
			obj->m_addtest = evt.m_eventEndTime;

			obj->SetWaveEndFlag(false);

			obj->m_gameState = GameNormalState::en_waveEnd;
		}
	);
}

void GameModeNormalUpdateState::GameUpdate()
{

	GameCameraManager::GetGameCameraManagerInstance()->UpdateGameCameraManager();

	TankShellsManager::GetTankShellsManagerInstance()->UpdateTankShellsManager();

	EnemyTankManager::GetEnemyTankManagerInstance()->UpdateEnemyTankManager();

	GameCollisionManager::GetCollisionManagerInstance()->UpdateCollisionManager();
}




