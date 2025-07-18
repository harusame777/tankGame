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

	//テキスト登録
	for (int i = 0; i < m_textRenderList.size(); i++)
	{
		AddFont(i, &m_textRenderList[i]);
	}

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
	UpdateTextLogUi();
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
		//まだ未表示なら
		if (!listPtr.second.m_isNotDisplay)
		{
			itExist = true;
		}
	}

	return itExist;
}

void GameUiLog::UpdateTextLogUi()
{
	//新しいログが入ってきたか
	bool isNewLogIn = false;

	//もしも記録リスト内にまだ表示していないログがあれば表示処理に入る
	if (IsRecordListNotDisplayLog())
	{
		//表示リストがいっぱいなら
		if (m_displayLogMax < m_displayTextLogList.size())
		{
			//表示リストの末尾を削除
			m_displayTextLogList.pop_back();
		}

		//新しく表示リストに追加
		AddDisplayListInfo();

		isNewLogIn = true;
	}

	SetUpdateText();

	//ログが作成されたかログが移動中なら
	if (isNewLogIn || m_isLogMoving)
	{
		//移動更新
		UpdateTextMoving();
		//ログは現在移動中
		m_isLogMoving = true;
	}

}

void GameUiLog::AddDisplayListInfo()
{
	DysplayLogInfo newLogData;
	//記録リストから優先度の高いものを取得
	newLogData.m_logData = GetRecordListData();
	//位置はログが映らない一番下の箇所に
	newLogData.m_positionNo = 0;	
	//描画番号を設定する
	if (m_nextDrawId > m_displayLogMax - 1)
	{
		m_nextDrawId = 0;
	}
	//フォントレンダーのアドレスを登録
	newLogData.m_textPtr = &m_textRenderList[m_nextDrawId++];
	//透過させる
	Vector4 colorValue = { 0.0f,0.0f,0.0f,0.0f };
	colorValue.x = newLogData.m_logData.m_textColor.x;
	colorValue.y = newLogData.m_logData.m_textColor.y;
	colorValue.z = newLogData.m_logData.m_textColor.z;
	newLogData.m_textPtr->SetColor(colorValue); 
	//リストの空きに入れる
	m_displayTextLogList.push_front(newLogData);
}

const GameUiLog::RecordLogInfo& GameUiLog::GetRecordListData()
{
	RecordLogInfo* recordData = nullptr;

	for (auto recordIt = m_recordTextLogList.rbegin();
		recordIt != m_recordTextLogList.rend(); 
		++recordIt)
	{
		//表示しているやつは飛ばす
		if (recordIt->second.m_isNotDisplay)
		{
			continue;
		}

		//表示させるのでアドレスを格納
		recordData = &recordIt->second;
		//表示中に変更
		recordData->m_isNotDisplay = true;
	}

	return *recordData;

}

void GameUiLog::SetUpdateText()
{

	//表示中の文字の設定
	for (auto displayPtr : m_displayTextLogList)
	{
		//文字を設定
		displayPtr.m_textPtr->SetText(displayPtr.m_logData.m_textBuffe);
	}

}

void GameUiLog::UpdateTextMoving()
{
	int easingEndLogNum = 0;

	for (auto& displayPtr : m_displayTextLogList)
	{
		//位置更新
		Vector2 startPos = m_displayTextPosList[displayPtr.m_positionNo];
		Vector2 endPos = m_displayTextPosList[displayPtr.m_positionNo + 1];

		Vector3 updatePos = Vector3::Zero;

		if (LogEasing(startPos, endPos, updatePos))
		{
			easingEndLogNum++;
		}

		displayPtr.m_textPtr->SetPosition(updatePos);

		Vector4 color = { 0.0f,0.0f,0.0f,0.0f };

		color = displayPtr.m_logData.m_textColor;

		if (displayPtr.m_positionNo <= 0)
		{
			color.a = m_logMovingRatio;
		}
		else if (displayPtr.m_positionNo >= UiGameLogConstant::LOG_DISPLAY_MAX)
		{
			color.a = 1.0f - m_logMovingRatio;
		}

		displayPtr.m_textPtr->SetColor(color);
	}

	if (easingEndLogNum >= m_displayTextLogList.size())
	{
		m_logMovingRatio = 0.0f;

		m_isLogMoving = false;
	}
}

bool GameUiLog::LogEasing(
	const Vector2& startPos,
	const Vector2& endPos,
	Vector3& updatePos
)
{

	Vector2 easingPos = Vector2::Zero;

	easingPos.Lerp(
		m_logMovingRatio,
		startPos,
		endPos
	);

	updatePos.x = easingPos.x;
	updatePos.y = easingPos.y;

	if (m_logMovingRatio >= 1.0f)
	{
		updatePos.x = endPos.x;
		updatePos.y = endPos.y;

		return true;
	}

	m_logMovingRatio += g_gameTime->GetFrameDeltaTime();

	return false;

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