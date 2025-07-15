#include "stdafx.h"
#include "GameUiLog.h"

//スタート関数
bool GameUiLog::Start()
{

	//表示するフォントレンダーを登録
	for (auto& ptr : m_displayFontLog)
	{
		AddFont(0, &m_displayFontLog->m_text);
	}

	//イベントリスナーに登録
	EventManager::GetEventManagerInstance()->RegisterListener<EventGameLog, GameUiLog>(
		this,
		[](GameUiLog* obj) {
			return true;
		},
		[](GameUiLog* obj, const EventGameLog& evt) {
			//イベントの情報を記録
			RecordLogInfo newLogInfo;
			//テキストをコピー
			wcscpy(newLogInfo.m_textBuffe, evt.m_textBuffe);
			//カラーを設定
			newLogInfo.m_textColor = evt.m_textColor;
			//x値を設定
			newLogInfo.m_textXPos = evt.m_textXPos;
			//配列に設定
			obj->m_recordFontLog.insert({ evt.m_priorityNum, newLogInfo });
		}
	);

	return true;
}

//更新関数
void GameUiLog::Update()
{
	//ログの更新処理をここに記述
	UpdateState();
}

//描画処理
void GameUiLog::Render(RenderContext& rc)
{

}

//表示処理
void GameUiLog::UpdateAppearanceMove()
{

}

//非表示処理
void GameUiLog::UpdateExtinctionMove()
{

}

//Ui更新処理
void GameUiLog::UpdateUi()
{

}

bool GameUiLog::SpriteEasing(
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