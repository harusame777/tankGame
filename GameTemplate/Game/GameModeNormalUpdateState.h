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
	/// ゲームのオブジェクトをロードする
	/// </summary>
	void LoadGameObject();
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
};

