#pragma once

#include "GameUiBase.h"

#include "EventManager.h"

namespace UiGameLogConstant
{

	const Vector2 BASE_ON_POSITION = { 677.5f,100.0f };

	const Vector2 BASE_OFF_POSITION = { 1000.0f,100.0f };

	const Vector2 TEXT_INIT_POSITION = { 0.0f,30.0f };

	const int LOG_DISPLAY_MAX = 6;

	const int LOG_TEXT_MAX = 20;
};

struct EventGameLog : public EventManager::StructEventBase
{
	/// <summary>
	/// 文字バッファー
	/// </summary>
	wchar_t m_textBuffe[256];
	/// <summary>
	/// 文字カラー
	/// </summary>
	Vector4 m_textColor = { 1.0f,1.0f,1.0f,1.0f };
	/// <summary>
	/// 文字のx軸の位置
	/// </summary>
	float m_textXPos = 0.0f;
	/// <summary>
	/// 優先度
	/// </summary>
	int m_priorityNum = 0;
};

class GameUiLog : 
	public GameUiBase ,
	public IGameObject
{
	appState(GameUiLog);
public:
	/// <summary>
	/// 処理を開始します。
	/// </summary>
	/// <returns>処理の開始に成功した場合は true、失敗した場合は false を返します。</returns>
	bool Start() override;
	/// <summary>
	/// オブジェクトの状態を更新します。
	/// </summary>
	void Update() override;
	/// <summary>
	/// レンダリングコンテキストを使用して描画処理を実行します。
	/// </summary>
	/// <param name="rc">描画処理に使用するRenderContextオブジェクトへの参照。</param>
	void Render(RenderContext& rc) override;
	/// <summary>
	/// Uiの表示移動を更新する関数です。
	/// </summary>
	void UpdateAppearanceMove() override;
	/// <summary>
	/// Uiの非表示移動を更新する関数です。
	/// </summary>
	void UpdateExtinctionMove() override;
	/// <summary>
	/// UI を更新します。
	/// </summary>
	void UpdateUi() override;
private:
	/// <summary>
	/// ログの記録構造体
	/// </summary>
	struct RecordLogInfo
	{
		/// <summary>
		/// 文字バッファー
		/// </summary>
		wchar_t m_textBuffe[256] = L"";
		/// <summary>
		/// 文字カラー
		/// </summary>
		Vector4 m_textColor = { 1.0f,1.0f,1.0f,1.0f };
		/// <summary>
		/// 文字のx軸の位置
		/// </summary>
		float m_textXPos = 0.0f;
		/// <summary>
		/// 未表示かどうか
		/// </summary>
		bool m_isNotDisplay = false;
	};
	struct DysplayLogInfo
	{
		/// <summary>
		/// イベントによって他クラスから送られてくる情報
		/// </summary>
		RecordLogInfo* m_logData;
		/// <summary>
		/// フォントレンダー
		/// </summary>
		FontRender* m_textPtr;
		/// <summary>
		/// 位置番号
		/// </summary>
		int m_positionNo = 0;

	};
	/// <summary>
	/// テキスト位置の初期化
	/// </summary>
	void InitTextPosList(int displayTextNum);
	/// <summary>
	/// 記録リスト内に未表示のログが存在するかどうか
	/// </summary>
	/// <returns></returns>
	bool IsRecordListNotDisplayLog();
	/// <summary>
	/// テキストログの更新
	/// </summary>
	void UpdateTextLogUi();
	/// <summary>
	/// 表示リストに表示情報を追加
	/// </summary>
	void AddDisplayListInfo();
	/// <summary>
	/// 記録リストからデータを取得
	/// </summary>
	RecordLogInfo* GetRecordListData();
	/// <summary>
	/// 更新するテキストを設定
	/// </summary>
	void SetUpdateText();
	/// <summary>
	/// 移動更新
	/// </summary>
	void UpdateTextMoving();
	/// <summary>
	/// ログのイージング
	/// </summary>
	/// <param name="startPos"></param>
	/// <param name="endPos"></param>
	/// <param name="ratio"></param>
	bool LogEasing(
		const Vector2& startPos,
		const Vector2& endPos,
		Vector3& updatePos
	);
	/// <summary>
	/// スプライトのイージング
	/// </summary>
	/// <returns></returns>
	bool SpriteEasing(
		const Vector2& startPos,
		const Vector2& endPos
	);
	/// <summary>
	/// 移動比率を表す浮動小数点型の変数です。
	/// </summary>
	float m_uiMoveRatio = 0.0f;
	/// <summary>
	/// ログの移動比率
	/// </summary>
	float m_logMovingRatio = 0.0f;
	/// <summary>
	/// 記録フォントログ
	/// </summary>
	std::multimap<int,RecordLogInfo> m_recordTextLogList;
	/// <summary>
	/// 表示フォントログ
	/// </summary>
	std::deque<DysplayLogInfo> m_displayTextLogList;
	/// <summary>
	/// テキスト表示用のフォントレンダーのリスト
	/// </summary>
	std::array<FontRender, UiGameLogConstant::LOG_DISPLAY_MAX + 1> m_textRenderList;
	/// <summary>
	/// 表示するログの最大数
	/// </summary>
	int m_displayLogMax = UiGameLogConstant::LOG_DISPLAY_MAX + 1;
	/// <summary>
	/// 次の描画番号
	/// </summary>
	int m_nextDrawId = 0;
	/// <summary>
	/// ログが動いているかどうか
	/// </summary>
	bool m_isLogMoving = false;
	/// <summary>
	/// 表示位置記録配列(出現位置も込み)
	/// </summary>
	Vector2 m_displayTextPosList[UiGameLogConstant::LOG_DISPLAY_MAX + 2];
	/// <summary>
	/// 上部分フレーム
	/// </summary>
	SpriteRender m_spriteUpFrame;
	/// <summary>
	/// 下部分フレーム
	/// </summary>
	SpriteRender m_spriteDownFrame;
};

