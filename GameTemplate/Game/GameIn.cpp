#include "stdafx.h"
#include "GameIn.h"

//ゲームステート初期化
void GameIn::InitGameState()
{
	
}

//ゲームステート更新
void GameIn::UpdateGameState()
{
	switch (m_stateNum)
	{
	case GameIn::en_gameUpdate:

		GameUpdate();

		break;
	default:
		break;
	}
}

//ゲームアップデート
void GameIn::GameUpdate()
{



}