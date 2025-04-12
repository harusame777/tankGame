#include "stdafx.h"
#include "GameOut.h"
#include "GameTitle.h"
#include "GameIn.h"
#include "GameLoad.h"

//ゲームステート初期化
void GameOut::InitGameState()
{
	//ゲームタイトルを作成
	m_gameTitle = NewGO<GameTitle>(0, "GameTitle");
	//ゲームタイトルを実行
	m_gameTitle->BootGameTitle();
	//ロード画面のインスタンスを取得
	m_gameLoad = FindGO<GameLoad>("gameLoad");
}

//ゲームステート更新
void GameOut::UpdateGameState()
{
	//ゲームアウトのステート
	switch (m_stateNum)
	{
	case GameOut::en_title:

		if (m_gameTitle->IsGameTitleBoot() == false)
		{

			m_gameLoad->LoadExecutionFadeOut({
				GameLoad::en_loadOrdinary,
				GameLoad::en_loadOrdinary },
				6.0f
			);

			if (m_gameLoad->IsLoadBlackout() == false)
				return;

			m_gameMain->ChangeContextListState(
				GameMain::en_outGame,
				GameOut::en_objectLoad
			);

		}

		break;
	case GameOut::en_objectLoad:

		LoadGameObject();

		m_gameLoad->LoadExecutionFadeIn();

		m_gameMain->ChangeContextListState(
			GameMain::en_inGame,
			GameIn::en_gameUpdate);

		break;
	default:
		break;
	}

}

//オブジェクトロード
void GameOut::LoadGameObject()
{

}
