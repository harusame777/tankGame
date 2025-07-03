#include "stdafx.h"
#include "GameUiEnemyCount.h"

#include "WaveData.h"

//スタート関数
bool GameUiEnemyCount::Start()
{

	std::shared_ptr<GameUiEnemyCount> initShared(this);

	m_uiEnemyCountSharedPtr = initShared;

	//イベントマネジャーを使用して、エネミーマネージャー側にエネミーが倒された数を通知してもらう。
	EventManager::GetEventManagerInstance()->RegisterListener<EventEnemyDead, GameUiEnemyCount>(
		m_uiEnemyCountSharedPtr,
		[](std::shared_ptr<GameUiEnemyCount> obj) {
			return true;
		},
		[](std::shared_ptr<GameUiEnemyCount> obj, const EventEnemyDead& evt) {
			//イベントを受け取ったら、残りのエネミー数を更新する
			obj->m_enemyCount = evt.m_enemyRemainingNum;
		}
	);

	return true;
}

//更新関数
void GameUiEnemyCount::Update()
{
	//ログの更新処理をここに記述
	UpdateState();
}

//描画処理
void GameUiEnemyCount::Render(RenderContext& rc)
{

}

//表示処理
void GameUiEnemyCount::UpdateAppearanceMove()
{

}

//非表示処理
void GameUiEnemyCount::UpdateExtinctionMove()
{

}

//Ui更新処理
void GameUiEnemyCount::UpdateUi()
{

}