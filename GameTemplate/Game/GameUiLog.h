#pragma once

#include "GameUiBase.h"



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
	/// フォントレンダリング情報のリストを格納するベクターです。
	/// </summary>
	std::vector<FontRender> m_LogTextList;
};

