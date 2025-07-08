#include "stdafx.h"
#include "GameUiEnemyCount.h"

#include "WaveData.h"

//スタート関数
bool GameUiEnemyCount::Start()
{

	m_uiFrame.Init("Assets/spriteData/uiEnemyCount/EnemyCountUiV1.DDS", 288, 152);

	m_uiTankIcon.Init("Assets/spriteData/uiEnemyCount/EnemyCountUiTankIconV1.DDS", 129, 74);

	AddSprite(1,&m_uiFrame);

	AddSprite(0, &m_uiTankIcon);

	//イベントマネジャーを使用して、エネミーマネージャー側にエネミーが倒された数を通知してもらう。
	EventManager::GetEventManagerInstance()->RegisterListener<EventEnemyCount, GameUiEnemyCount>(
		this,
		[](GameUiEnemyCount* obj) {
			return true;
		},
		[](GameUiEnemyCount* obj, const EventEnemyCount& evt) {
			//イベントを受け取ったら、残りのエネミー数を更新する
			obj->m_enemyCount = evt.m_enemyEventCount;
		}
	);

	//文字更新

	//いまはテスト
	UpdateEnemyCountUi(
		m_enemyCount,
		{0.0f,0.0f}
	);

	SetState(EnGameUiState::en_application);

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
	DrawListSprites(rc);

	m_fontRender.Draw(rc);
}

//表示処理
void GameUiEnemyCount::UpdateAppearanceMove()
{
	SetState(EnGameUiState::en_updateUi);
}

//非表示処理
void GameUiEnemyCount::UpdateExtinctionMove()
{

}

//Ui更新処理
void GameUiEnemyCount::UpdateUi()
{
	UpdateEnemyCountUi(
		m_enemyCount,
		UiConstant::FONT_ON_POSITION
	);
}

//エネミーの残り数を表示するUIの更新処理
void GameUiEnemyCount::UpdateEnemyCountUi(
	int nowEnemyCount,
	const Vector2& setPosition
)
{
	//エネミーの残り数を表示するUIの更新処理をここに記述

	//位置設定

	Vector3 setPosition3vec(setPosition.x, setPosition.y,0.0);

	m_fontRender.SetPosition(setPosition3vec);

	//表示文字設定

	//文字バッファ
	wchar_t fontBuffer[256] = {};

	//エネミーの残り数を文字列に変換してバッファに格納
	swprintf(fontBuffer, 256, L"%01d", int(nowEnemyCount));

	m_fontRender.SetText(fontBuffer);

	m_fontRender.SetScale(UiConstant::ENEMY_COUNT_MAX_SIZE);

	Vector3 test(
		UiConstant::SPRITE_ON_POSITION.x,
		UiConstant::SPRITE_ON_POSITION.y,
		0.0f
	);

	m_uiFrame.SetPosition(test);

	m_uiTankIcon.SetPosition(test);

	m_uiFrame.Update();

	m_uiTankIcon.Update();
}