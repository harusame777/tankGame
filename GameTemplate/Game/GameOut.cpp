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
	switch (m_gameOutState)
	{
	case GameOut::en_title:

		//ゲームタイトル作成
		MakeGameTitle();

		if (m_gameTitle->IsGameTitleEnd())
		{

			//ステートを変更する
			ChangeGameOutState(
				GameOutState::en_objectLoad);

		}

		break;
	case GameOut::en_objectLoad:

		m_gameMain->ChangeGameMainState(GameMain::en_inGame);

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