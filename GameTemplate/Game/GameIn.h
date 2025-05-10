#pragma once
#include "GameMain.h"
#include "GameLoad.h"

class GameLoad;

class GameMapManager;
class GamePlayer;
class TankShellsManager;

class GameIn : public GameMainStateClass
{
public:
	enum GameInState
	{
		en_objectLoad,

		en_gameUpdate,

		enum_Num
	};
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameIn() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~GameIn() {};
	/// <summary>
	/// ステート初期化
	/// </summary>
	void InitGameState() override;
	/// <summary>
	/// ステートアップデート
	/// </summary>
	void UpdateGameState() override;
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
	GameLoad* m_gameLoad = nullptr;
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

