#include "stdafx.h"
#include "GameMain.h"
#include "GameTitleState.h"
#include "GameLoadingScreen.h"

#include "GameMainStateMachine.h"
#include "GameModeNormalUpdateState.h"
#include "GameLoadOrDeleteState.h"

//スタート関数
bool GameMain::Start()
{
	//ロード作成
	m_gameLoad = NewGO<GameLoadingScreen>(1, "gameLoad");

	//ステートマシン生成
	m_gameMainStateMachine = new GameMainStateMachine();

	m_gameMainStateMachine->RegisterState<GameTitleState>();
	m_gameMainStateMachine->RegisterState<GameModeNormalUpdateState>();
	m_gameMainStateMachine->RegisterState<GameLoadOrDeleteState>(&m_loadOrDelete);
	m_gameMainStateMachine->InitilizeState<GameTitleState>();
	m_gameMainStateMachine->InitState();

	return true;
}

//アップデート関数
void GameMain::Update()
{
	//ステートマシン更新
	m_gameMainStateMachine->Update();
}
