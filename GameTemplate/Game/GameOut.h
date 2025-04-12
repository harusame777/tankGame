#pragma once
#include "GameMain.h"

class GameTitle;
class GameLoad;

class GameOut : public GameMainStateClass
{
public: 
	enum GameOutState {
		en_title,

		en_objectLoad,

		enum_Num
	};
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameOut() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~GameOut() {};
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
	/// ゲームタイトルのインスタンス
	/// </summary>
	GameTitle* m_gameTitle = nullptr;
	/// <summary>
	/// ロード画面
	/// </summary>
	GameLoad* m_gameLoad = nullptr;
};

