#pragma once
#include "GameMain.h"

class GameTitle;

class GameOut : public GameMainStateClass
{
public: 
	enum OutGameState {
		en_title,

		en_objectLoad,

		enum_Num
	};
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
	/// ゲームタイトルを作成する
	/// </summary>
	void MakeGameTitle();
	/// <summary>
	/// アウトゲームのステート
	/// </summary>
	OutGameState m_outGameState = OutGameState::en_title;
	/// <summary>
	/// ゲームタイトルのインスタンス
	/// </summary>
	GameTitle* m_gameTitle = nullptr;
};

