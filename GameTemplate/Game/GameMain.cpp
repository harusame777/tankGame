#include "stdafx.h"
#include "GameMain.h"
#include "GameOut.h"

bool GameMain::Start()
{
	//コンテキスト設定アウトゲーム
	m_contextList[GameMainState::en_outGame]
		= new GameMainContextClass(new GameOut);

	return true;
}