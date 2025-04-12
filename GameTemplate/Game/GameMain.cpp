#include "stdafx.h"
#include "GameMain.h"
#include "GameOut.h"
#include "GameIn.h"
#include "GameLoad.h"

//スタート関数
bool GameMain::Start()
{
	//ロード作成
	m_gameLoad = NewGO<GameLoad>(1, "gameLoad");

	//コンテキスト設定アウトゲーム
	m_contextList[GameMainState::en_outGame]
		= new GameMainContextClass(new GameOut,this,GameOut::enum_Num);

	//コンテキスト設定インゲーム
	m_contextList[GameMainState::en_inGame]
		= new GameMainContextClass(new GameIn,this,GameIn::enum_Num);

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

//ステート変更
void GameMain::ChangeContextListState(GameMainState changeState, int changeNum)
{
	//メインのステートを変更
	m_gameMainState = changeState;
	//リストのステートを変更
	m_contextList[changeState]->RequestGameStateChange(changeNum);
}

