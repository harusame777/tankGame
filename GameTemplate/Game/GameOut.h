#pragma once
#include "GameMain.h"

class GameTitle;

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
	/// <summary>
	/// ステート変更関数
	/// </summary>
	/// <param name="gameOutState"></param>
	void ChangeGameOutState(GameOutState gameOutState)
	{
		m_gameOutState = gameOutState;
	}
private:
	/// <summary>
	/// ゲームタイトルを作成する
	/// </summary>
	void MakeGameTitle();
	/// <summary>
	/// アウトゲームのステート
	/// </summary>
	GameOutState m_gameOutState = GameOutState::en_title;
	/// <summary>
	/// ゲームタイトルのインスタンス
	/// </summary>
	GameTitle* m_gameTitle = nullptr;
};

