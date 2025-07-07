#pragma once
 
#include "GameUiBase.h"

namespace UiConstant
{
	Vector2 const ENEMY_COUNT_POSITION = Vector2(800.0f, 500.0f);

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
		int nowEnemyCount,
		const Vector2& setPosition
	);
	/// <summary>
	/// フォントレンダー
	/// </summary>
	FontRender m_fontRender; 
	/// <summary>
	/// 敵の数を表す整数型のメンバー変数です。
	/// </summary>
	int m_enemyCount; 
	/// <summary>
	/// 敵の数を管理するGameUiEnemyCountオブジェクトへの共有ポインタです。
	/// </summary>
	std::shared_ptr<GameUiEnemyCount> m_uiEnemyCountSharedPtr;
};

