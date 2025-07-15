#pragma once
 
#include "GameUiBase.h"

namespace UiEnemyCountConstant
{
	const Vector2 BASE_ON_POSITION = Vector2(650.0f, 360.0f);

	const Vector2 BASE_OFF_POSITION = Vector2(1000.0f, 360.0f);

	const Vector2 TANKICON_ADD_POSITION = Vector2(-60.0f,0.0f);

	const Vector2 COUNT_ADD_POSITION = Vector2(160.0f, 120.0f);

	const float ENEMY_COUNT_MAX_SIZE = 2.0f;
}

class GameUiEnemyCount :
	public GameUiBase,
	public IGameObject
{
	appState(GameUiEnemyCount);
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameUiEnemyCount() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameUiEnemyCount() {};
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
	/// 現在の敵の数をUIに表示します。
	/// </summary>
	/// <param name="nowEnemyCount">現在存在する敵の数。</param>
	void UpdateEnemyCountUi(
		int nowEnemyCount
	);
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	bool SpriteEasing(
		const Vector2& startPos,
		const Vector2& endPos
	);
	/// <summary>
	/// フォントレンダー
	/// </summary>
	FontRender m_fontRender; 
	/// <summary>
	/// メインUIのスプライトレンダラーを表す変数です。
	/// </summary>
	SpriteRender m_uiFrame;
	/// <summary>
	/// 戦車アイコンを描画するためのSpriteRender型のメンバー変数です。
	/// </summary>
	SpriteRender m_uiTankIcon;
	/// <summary>
	/// 移動比率を表す浮動小数点型の変数です。
	/// </summary>
	float m_uiMoveRatio = 0.0f;
	/// <summary>
	/// 敵の数を表す整数型のメンバー変数です。
	/// </summary>
	int m_enemyCount; 
};

