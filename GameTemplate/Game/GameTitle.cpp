#include "stdafx.h"
#include "GameTitle.h"

//スタート関数
bool GameTitle::Start()
{
	return true;
}

//アップデート関数
void GameTitle::Update()
{
	//待機ステートであれば
	if (m_gameTitleState == GameTitleState::en_standby)
	{
		//実行しない
		return;
	}

	//ゲームタイトル更新
	GameTitleUpdate();
}

void GameTitle::GameTitleUpdate()
{
	if (g_pad[0]->IsTrigger(enButtonB))
	{
		StopGameTitle();
	}
}

//レンダー関数
void GameTitle::Render(RenderContext& rc)
{

}