#include "stdafx.h"
#include "GameUiEnemyCount.h"

#include "WaveData.h"

//スタート関数
bool GameUiEnemyCount::Start()
{

	m_uiFrame.Init("Assets/spriteData/uiEnemyCount/EnemyCountUiV1.DDS", 288, 152);

	m_uiTankIcon.Init("Assets/spriteData/uiEnemyCount/EnemyCountUiTankIconV1.DDS", 129, 74);

	AddSprite(0,&m_uiFrame);

	AddFont(1, &m_fontRender);

	AddSprite(2, &m_uiTankIcon);

	SetBasePosition(UiEnemyCountConstant::BASE_OFF_POSITION);

	SetSpriteOrFontAddPosition(0,{0.0f,0.0f});

	SetSpriteOrFontAddPosition(1, UiEnemyCountConstant::COUNT_ADD_POSITION);

	SetSpriteOrFontAddPosition(2, UiEnemyCountConstant::TANKICON_ADD_POSITION);

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
		m_enemyCount
	);

	SetState(EnGameUiState::en_standby);

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
}

//表示処理
void GameUiEnemyCount::UpdateAppearanceMove()
{

	//UIを出す
	if (SpriteEasing(
		UiEnemyCountConstant::BASE_OFF_POSITION,
		UiEnemyCountConstant::BASE_ON_POSITION
		))
	{
		SetState(EnGameUiState::en_updateUi);
	}

}

//非表示処理
void GameUiEnemyCount::UpdateExtinctionMove()
{

	//UIをしまう
	if (SpriteEasing(
		UiEnemyCountConstant::BASE_OFF_POSITION,
		UiEnemyCountConstant::BASE_ON_POSITION
	))
	{
		SetState(EnGameUiState::en_updateUi);
	}

}

//Ui更新処理
void GameUiEnemyCount::UpdateUi()
{
	UpdateEnemyCountUi(
		m_enemyCount
	);
}

//エネミーの残り数を表示するUIの更新処理
void GameUiEnemyCount::UpdateEnemyCountUi(
	int nowEnemyCount
)
{
	//表示文字設定

	//文字バッファ
	wchar_t fontBuffer[256] = {};

	//エネミーの残り数を文字列に変換してバッファに格納
	swprintf(fontBuffer, 256, L"%01d", int(nowEnemyCount));

	GetFontAddres(1).SetText(fontBuffer);

	GetFontAddres(1).SetScale(UiEnemyCountConstant::ENEMY_COUNT_MAX_SIZE);
}

bool GameUiEnemyCount::SpriteEasing(
	const Vector2& startPos,
	const Vector2& endPos
)
{

	Vector2 easingPos = Vector2::Zero;

	easingPos.Lerp(
		m_uiMoveRatio,
		startPos,
		endPos
	);

	SetBasePosition(easingPos);

	if (m_uiMoveRatio >= 1.0f)
	{
		m_uiMoveRatio = 0.0f;

		SetBasePosition(endPos);

		return true;
	}

	m_uiMoveRatio += g_gameTime->GetFrameDeltaTime() * 1.2;

	return false;
}
