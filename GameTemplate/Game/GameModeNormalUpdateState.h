#pragma once

#include "StateBase.h"

class GameLoadingScreen;

class GameMapManager;
class GamePlayer;
class TankShellsManager;

class WaveData;

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

	bool IsUiSetUp();

	/// <summary>
	/// ウェーブ終了フラグを設定します。
	/// </summary>
	/// <param name="is">ウェーブ終了フラグとして設定する値。trueの場合、ウェーブが終了可能なことを示しています。</param>
	void SetWaveEndFlag(bool is)
	{
		m_waveEndGoFlag = is;
	}
	/// <summary>
	/// ウェーブ終了フラグを取得します。
	/// </summary>
	/// <returns>ウェーブが終了可能な場合は true、そうでない場合は false を返します。</returns>
	bool GetWaveEndFlag() const
	{
		return m_waveEndGoFlag;
	}
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
	/// <summary>
	/// ゲームモードの通常更新状態を管理するための std::shared_ptr 型のメンバ変数です。
	/// </summary>
	std::shared_ptr<GameModeNormalUpdateState> m_gameModeNormalSharedPtr;
	/// <summary>
	/// ウェーブ終了の進行フラグを示すブール値です。
	/// </summary>
	bool m_waveEndGoFlag = false;
	/// <summary>
	/// WaveData 型のポインタ m_waveData です。
	/// </summary>
	WaveData* m_waveData = nullptr;

	float m_addtest = 0.0f;
};

