#pragma once

#include "GameUiBase.h"

#include "EventManager.h"

namespace UiGameLogConstant
{

	const Vector2 BASE_ON_POSITION = { 650.0f,300.0f };

	const Vector2 BASE_OFF_POSITION = { 1000.0f,300 };

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
		wchar_t m_textBuffe[256];
		/// <summary>
		/// 文字カラー
		/// </summary>
		Vector4 m_textColor = { 1.0f,1.0f,1.0f,1.0f };
		/// <summary>
		/// 文字のx軸の位置
		/// </summary>
		float m_textXPos = 0.0f;
	};

	struct FontLogInfo
	{
		/// <summary>
		/// イベントによって他クラスから送られてくる情報
		/// </summary>
		EventGameLog m_logData;
		/// <summary>
		/// フォントレンダー
		/// </summary>
		FontRender m_text;
		/// <summary>
		/// アクティブかどうか
		/// </summary>
		bool m_isActive = false;
		/// <summary>
		/// 位置
		/// </summary>
		Vector2 m_pos = Vector2::Zero;
	};

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
	/// 記録フォントログ
	/// </summary>
	std::map<int,RecordLogInfo> m_recordFontLog;
	/// <summary>
	/// 表示フォントログ
	/// </summary>
	FontLogInfo m_displayFontLog[6];
	/// <summary>
	/// 上部分フレーム
	/// </summary>
	SpriteRender m_spriteUpFrame;
	/// <summary>
	/// 下部分フレーム
	/// </summary>
	SpriteRender m_spriteDownFrame;

};

