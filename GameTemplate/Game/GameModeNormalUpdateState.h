#pragma once

#include "StateBase.h"

class GameLoadingScreen;

class GameMapManager;
class GamePlayer;
class TankShellsManager;

class GameModeNormalUpdateState : public StateBase
{
	appState(GameModeNormalUpdateState);
public:
	/// <summary>
	/// ゲーム通常モードの状態を表す列挙型です。
	/// </summary>
	enum class GameNormalState
	{
		en_waitLoadEnd,

		en_waveStandby,

		en_waveUpdate,

		en_waveEnd
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameModeNormalUpdateState() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~GameModeNormalUpdateState() {};
	/// <summary>
	/// 初期化
	/// </summary>
	void Enter() override;
	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;
	/// <summary>
	/// 終了
	/// </summary>
	void Exit() override;
	/// <summary>
	/// ステート遷移
	/// </summary>
	/// <param name="request"></param>
	/// <returns></returns>
	bool RequestState(uint32_t& request) override;
private:
	/// <summary>
	/// ゲームモードで
	/// </summary>
	void GameModeInit();
	/// <summary>
	/// ゲームアップデート
	/// </summary>
	void GameUpdate();
	/// <summary>
	/// ロード画面
	/// </summary>
	GameLoadingScreen* m_gameLoad = nullptr;
	/// <summary>
	/// ゲームマップのマネージャー
	/// </summary>
	GameMapManager* m_gameMapManager = nullptr;
	/// <summary>
	/// ゲームプレイヤー
	/// </summary>
	GamePlayer* m_gamePlayer = nullptr;
	/// <summary>
	/// 砲弾のマネージャー
	/// </summary>
	TankShellsManager* m_tankShellsManager = nullptr;
	/// <summary>
	/// ゲームのステート
	/// </summary>
	GameNormalState m_gameState = GameNormalState::en_waitLoadEnd;

	std::shared_ptr<GameModeNormalUpdateState> m_test;

	float m_addtest = 0.0f;
};

