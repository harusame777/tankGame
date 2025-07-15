#include "stdafx.h"
#include "GameTitleState.h"
#include "GameLoadOrDeleteState.h"
#include "GameTitle.h"
#include "GameLoadingScreen.h"

//ゲームステート初期化
void GameTitleState::Enter()
{
	//ゲームタイトルを作成
	m_gameTitle = NewGO<GameTitle>(0, "GameTitle");
	//ゲームタイトルを実行
	m_gameTitle->BootGameTitle();
	//ロード画面のインスタンスを取得
	m_gameLoad = FindGO<GameLoadingScreen>("gameLoad");
}

//ゲームステート更新
void GameTitleState::Update()
{

}

void GameTitleState::Exit()
{
	DeleteGO(m_gameTitle);
}

bool GameTitleState::RequestState(uint32_t& request)
{
	if (m_gameTitle->IsGameTitleBoot() == false)
	{
		request = GameLoadOrDeleteState::ID();

		return true;
	}

	return false;
}