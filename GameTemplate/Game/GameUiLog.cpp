#include "stdafx.h"
#include "GameUiLog.h"

//スタート関数
bool GameUiLog::Start()
{
	//上部分フレーム初期化
	m_spriteUpFrame.Init("Assets/spriteData/uiGameLog/GameLogUiUpFrameV1.DDS", 234, 19);
		
	//下部分フレーム初期化
	m_spriteDownFrame.Init("Assets/spriteData/uiGameLog/GameLogUiDownFrameV1.DDS", 234, 19);

	//表示位置初期化
	InitTextPosList(m_displayLogMax + 1);
	//上部分フレーム登録
	AddSprite(m_displayLogMax + 1, &m_spriteUpFrame);
	//位置設定
	SetSpriteOrFontAddPosition(m_displayLogMax + 1, { 0.0f,25.0f * 6.0f });
	//下部分フレーム登録
	AddSprite(m_displayLogMax + 2, &m_spriteDownFrame);

	//文字のサイズは0.7fフレームの1文字スペースを確保するための
	//数値はy+25または-25で1文字分となる。

	//位置設定
	SetSpriteOrFontAddPosition(m_displayLogMax + 2, { 0.0f,0.0f });
	//基本位置設定
	SetBasePosition(UiGameLogConstant::BASE_OFF_POSITION);

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
			obj->m_recordTextLogList.insert({ evt.m_priorityNum, newLogInfo });
		}
	);

	SetState(EnGameUiState::en_standby);

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
	DrawListSprites(rc);
}

//表示処理
void GameUiLog::UpdateAppearanceMove()
{

	//UIを出す
	if (SpriteEasing(
		UiGameLogConstant::BASE_OFF_POSITION,
		UiGameLogConstant::BASE_ON_POSITION
	))
	{
		SetState(EnGameUiState::en_updateUi);
	}
}

//非表示処理
void GameUiLog::UpdateExtinctionMove()
{

}

//Ui更新処理
void GameUiLog::UpdateUi()
{
	
	//文字の位置は+30または-30で１スペース確保


}

void GameUiLog::InitTextPosList(int displayTextNum)
{
	for (int listNo = 0; listNo < displayTextNum; listNo++)
	{
		Vector2 initPos = Vector2::Zero;

		initPos.x = 0.0f;

		initPos.y = UiGameLogConstant::TEXT_INIT_POSITION.y + 30.0f * listNo;

		m_displayTextPosList[listNo] = initPos;
	}
}

bool GameUiLog::IsRecordListNotDisplayLog()
{
	bool itExist = false;

	//記録リスト分回す
	for (auto& listPtr : m_recordTextLogList)
	{
		if (listPtr.second.m_isNotDisplay)
		{
			itExist = true;
		}
	}

	return itExist;
}

void GameUiLog::UpdateTextLogUi()
{

	//もしも記録リスト内にまだ表示していないログがあれば表示処理に入る
	if (IsRecordListNotDisplayLog())
	{
		//表示リストがいっぱいなら
		if (m_displayLogMax < m_displayTextLogList.size())
		{
			//表示リストの末尾を削除
			DeleteDisplayListBack();
		}

		//新しく表示リストに追加
		AddDisplayListInfo();
	}

}

void GameUiLog::AddDisplayListInfo()
{
	DysplayLogInfo newLogData;
	//記録リストから優先度の高いものを取得
	newLogData.m_logData = GetRecordListData();
	//位置はログが映らない一番下の箇所に
	newLogData.m_pos = m_displayTextPosList[0];
	//描画番号を設定する
	if (m_nextDrawId < m_displayLogMax - 1)
	{
		m_nextDrawId = 0;
	}
	newLogData.m_drawId = m_nextDrawId++;
	//リストの空きに入れる
	m_displayTextLogList.push_front(newLogData);
	//フォントを登録
	//AddFont(newLogData.m_drawId,
	//	&m_displayTextLogList[newLogData.m_drawId].m_text
	//);
}

void GameUiLog::DeleteDisplayListBack()
{
	//描画Idを取得
	int deleteDrawId = m_displayTextLogList[m_displayLogMax - 1].m_drawId;
	//描画Idのfontを削除
	DeleteFont(deleteDrawId);
	//配列から削除
	m_displayTextLogList.pop_back();
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