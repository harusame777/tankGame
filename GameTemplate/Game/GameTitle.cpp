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

	if (g_pad[0]->IsTrigger(enButtonB))
	{
		m_isGameTitleEnd = true;
	}

}

//レンダー関数
void GameTitle::Render(RenderContext& rc)
{

}