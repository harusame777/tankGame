#pragma once

#include "CRC32.h"
#include "GameUiManager.h"

#define appState(name)	\
public:\
	static constexpr uint32_t ID() { return Hash32(#name); }


class GameUiBase
{
public:
	/// <summary>
	/// GameUiBase クラスのデフォルトコンストラクタです。
	/// </summary>
	GameUiBase() = default;
	/// <summary>
	/// GameUiBase クラスの仮想デストラクタです。
	/// </summary>
	virtual ~GameUiBase() = default;
	/// <summary>
	/// Uiの表示移動を更新する純粋仮想関数です。
	/// </summary>
	virtual void UpdateAppearanceMove() = 0;
	/// <summary>
	/// Uiの非表示移動を更新する純粋仮想関数です。
	/// </summary>
	virtual void UpdateExtinctionMove() = 0;
	/// <summary>
	/// UI を更新するための純粋仮想関数です。
	/// </summary>
	virtual void UpdateUi() = 0;
	/// <summary>
	/// 現在の状態に応じて適切な更新処理を実行します。
	/// </summary>
	void UpdateState()
	{
		switch (m_state)
		{
		case en_init:

			//初期化中なので待機

			break;
		case en_application:

			//表示移行の更新を行う
			UpdateAppearanceMove();

			break;
		case en_updateUi:

			//表示後の更新を行う
			UpdateUi();

			break;
		case en_extinction:

			//非表示移行の更新を行う
			UpdateExtinctionMove();

			break;
		default:
			break;
		}
	}
	/// <summary>
	/// 描画フラグを設定します。
	/// </summary>
	/// <param name="isDraw">描画フラグとして設定する値。trueの場合は描画を有効にし、falseの場合は無効にします。</param>
	void SetDrawFlag(bool isDraw)
	{
		m_drawFlag = isDraw;
	}
	/// <summary>
	/// 描画フラグの状態を取得します。
	/// </summary>
	/// <returns>描画フラグが有効な場合は true、無効な場合は false を返します。</returns>
	bool GetDrawFlag() const
	{
		return m_drawFlag;
	}
	/// <summary>
	/// 基準位置を設定します。
	/// </summary>
	/// <param name="pos">設定する基準位置（Vector2 型の参照）。</param>
	void SetBasePosition(const Vector2& pos)
	{
		m_basePosition = pos;
	}
	/// <summary>
	/// 基準位置を取得します。
	/// </summary>
	/// <returns>メンバー変数 m_basePosition への定数参照。</returns>
	const Vector2& GetBasePosition() const
	{
		return m_basePosition;
	}
	/// <summary>
	/// EnGameUiState の値で UI の状態を設定します。
	/// </summary>
	/// <param name="state">設定する EnGameUiState の値。</param>
	void SetState(EnGameUiState state)
	{
		m_state = state;
	}
	/// <summary>
	/// 現在のゲームUIの状態を取得します。
	/// </summary>
	/// <returns>現在のEnGameUiState値。</returns>
	EnGameUiState GetState() const
	{
		return m_state;
	}
private:
	/// <summary>
	/// 描画フラグを示すブール値の変数です。
	/// </summary>
	bool m_drawFlag = false;
	/// <summary>
	/// 2次元ベクトルの基準位置をゼロベクトルで初期化します。
	/// </summary>
	Vector2 m_basePosition = Vector2::Zero;
	/// <summary>
	/// EnGameUiState 型の変数 m_state を en_init で初期化します。
	/// </summary>
	EnGameUiState m_state = en_init; 
};

