#include "stdafx.h"
#include "GamePlayerManager.h"
#include "GamePlayer.h"

//インスタンス初期化
GamePlayerManager* GamePlayerManager::m_gamePlayerManagerInstance = nullptr;

//ゲームプレイヤーマネージャー初期化
void GamePlayerManager::GamePlayerManager::InitGamePlayerManager()
{
	
}

//プレイヤーを生成
void GamePlayerManager::CreateGamePlayer()
{
	m_gamePlayer = NewGO<GamePlayer>(0, "gamePlayer");
}

//プレイヤーが移動可能か設定
void GamePlayerManager::SetIsGamePlayerCanMoving(const bool isCanMoving)
{
	if (m_gamePlayer != nullptr)
	{
		m_gamePlayer->SetIsPlayerCanMoving(isCanMoving);
	}
}

//プレイヤーが移動可能か取得
bool GamePlayerManager::IsGamePlayerCanMoving() const
{
	if (m_gamePlayer != nullptr)
	{
		return m_gamePlayer->IsPlayerCanMoving();
	}
	return false;
}

//ゲームプレイヤーマネージャー更新
void GamePlayerManager::UpdateGamePlayerManager()
{
	
}

