#include "stdafx.h"
#include "GameOut.h"
#include "GameTitle.h"

//ゲームステート初期化
void GameOut::InitGameState()
{
	//ゲームタイトルを作成
	m_gameTitle = NewGO<GameTitle>(0, "GameTitle");
	//ゲームタイトルを実行
	m_gameTitle->BootGameTitle();
}

//ゲームステート更新
void GameOut::UpdateGameState()
{
	//ゲームアウトのステート
	switch (m_gameOutState)
	{
	case GameOut::en_title:

		if (m_gameTitle->IsGameTitleBoot() == false)
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
