#include "stdafx.h"
#include "GameMain.h"
#include "GameOut.h"
#include "GameIn.h"

//スタート関数
bool GameMain::Start()
{
	//コンテキスト設定アウトゲーム
	m_contextList[GameMainState::en_outGame]
		= new GameMainContextClass(new GameOut,this);

	//コンテキスト設定インゲーム
	m_contextList[GameMainState::en_inGame]
		= new GameMainContextClass(new GameIn,this);

	//コンテキスト配列初期化
	for (int listNo = 0; 
		listNo < GameMainState::enum_Num; 
		listNo++)
	{
		//コンテキスト初期化
		m_contextList[listNo]->RequestGameStateInit();
	}

	return true;
}

//アップデート関数
void GameMain::Update()
{
	//ゲームアップデートを現在のステートで行う
	m_contextList[m_gameMainState]
		->RequestGameStateUpdate();
}

