#include "stdafx.h"
#include "GameOut.h"
#include "GameTitle.h"

//ゲームステート初期化
void GameOut::InitGameState()
{

	

}

//ゲームステート更新
void GameOut::UpdateGameState()
{
	//ゲームアウトのステート
	switch (m_outGameState)
	{
	case GameOut::en_title:

		//ゲームタイトル作成
		MakeGameTitle();

		break;
	case GameOut::en_objectLoad:
		break;
	case GameOut::enum_Num:
		break;
	default:
		break;
	}

}

//ゲームタイトル作成
void GameOut::MakeGameTitle()
{
	//ゲームタイトルが作成されていたら
	if (m_gameTitle != nullptr)
	{
		//実行しない
		return;
	}

	//ゲームタイトルを作成
	m_gameTitle = NewGO<GameTitle>(0, "GameTitle");
}