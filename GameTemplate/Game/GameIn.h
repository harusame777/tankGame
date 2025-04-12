#pragma once
#include "GameMain.h"
#include "GameLoad.h"

class GameLoad;

class GameIn : public GameMainStateClass
{
public:
	enum GameInState
	{
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
	/// ゲームアップデート
	/// </summary>
	void GameUpdate();
	/// <summary>
	/// ロード画面
	/// </summary>
	GameLoad* m_gameLoad = nullptr;
};

