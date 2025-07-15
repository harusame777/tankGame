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
protected:
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
		case en_standby:

			//待機
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

		//位置更新
		UpdateSpritePosition();
		//描画情報更新
		UpdateSpriteDrawInfo();
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
	/// リスト内のスプライトを描画コンテキストに描画します。
	/// </summary>
	/// <param name="rc">スプライトを描画するためのレンダーコンテキスト。</param>
	void DrawListSprites(RenderContext& rc);
	/// <summary>
	/// スプライトをスプライトリストに追加します。
	/// </summary>
	/// <param name="sprite">追加するSpriteRender型のスプライトへのポインタ。</param>
	void AddSprite(
		int drawOrderNum,
		SpriteRender* sprite
	)
	{
		SpriteListData newData;

		newData.m_isDraw = true;

		newData.m_spritePtr = sprite;

		m_spriteList.insert({ drawOrderNum,newData});
	}
	/// <summary>
	/// フォントを描画順序番号に従ってリストに追加します。
	/// </summary>
	/// <param name="drawOrderNum">フォントを追加する際の描画順序番号。</param>
	/// <param name="font">追加するFontRender型のフォントへのポインタ。</param>
	void AddFont(
		int drawOrderNum,
		FontRender* font
	)
	{
		FontListData newData;

		newData.m_isDraw = true;

		newData.m_fontPtr = font;

		m_fontList.insert({ drawOrderNum,newData });
	}
	/// <summary>
	/// 指定した描画順序番号のスプライトの描画状態を設定します。
	/// </summary>
	/// <param name="drawOrderNum">描画状態を変更するスプライトの描画順序番号。</param>
	/// <param name="isDraw">スプライトを描画する場合は true、描画しない場合は false。</param>
	void IsDrawSprite(
		int drawOrderNum,
		bool isDraw
	)
	{
		auto iter = m_spriteList.find(drawOrderNum);
		if (iter != m_spriteList.end())
		{
			iter->second.m_isDraw = isDraw;
		}
	}
	/// <summary>
	/// 指定した描画順IDに対応するスプライトまたはフォントの追加位置を設定します。
	/// </summary>
	/// <param name="drawOrderId">位置を設定する対象のスプライトまたはフォントの描画順ID。</param>
	/// <param name="addPos">新しく設定する追加位置（2次元ベクトル）。</param>
	void SetSpriteOrFontAddPosition(
		int drawOrderId,
		const Vector2& addPos
	)
	{
		auto iterSprite = m_spriteList.find(drawOrderId);
		if (iterSprite != m_spriteList.end())
		{
			iterSprite->second.m_spritePosition = addPos;

			return;
		}

		auto iterFont = m_fontList.find(drawOrderId);
		if (iterFont != m_fontList.end())
		{
			iterFont->second.m_spritePosition = addPos;

			return;
		}
	}
	/// <summary>
	/// 指定した描画順番号のフォントの描画フラグを設定します。
	/// </summary>
	/// <param name="drawOrderNum">描画順番号。対象となるフォントを識別します。</param>
	/// <param name="isDraw">フォントを描画するかどうかを示すフラグ。trueの場合は描画し、falseの場合は描画しません。</param>
	void IsDrawFont(
		int drawOrderNum,
		bool isDraw
	)
	{
		auto iter = m_fontList.find(drawOrderNum);
		if (iter != m_fontList.end())
		{
			iter->second.m_isDraw = isDraw;
		}
	}
	/// <summary>
	/// 指定された描画順IDに対応するスプライト情報への参照を取得します。
	/// </summary>
	/// <param name="drawOrderId"></param>
	/// <returns></returns>
	SpriteRender& GetSpriteAddres(
		int drawOrderId
	)
	{
		auto iter = m_spriteList.find(drawOrderId);
		if (iter != m_spriteList.end())
		{
			return *iter->second.m_spritePtr;
		}
	}
	/// <summary>
	/// 指定された描画順IDに対応するフォント情報への参照を取得します。
	/// </summary>
	/// <param name="drawOrderId">フォントを取得するための描画順ID。</param>
	/// <returns>対応するFontRenderオブジェクトへの定数参照。</returns>
	FontRender& GetFontAddres(
		int drawOrderId
	)
	{
		auto iter = m_fontList.find(drawOrderId);
		if (iter != m_fontList.end())
		{
			return *iter->second.m_fontPtr;
		}
	}
private:
	/// <summary>
	/// スプライトの位置を更新します。
	/// </summary>
	void UpdateSpritePosition();
	/// <summary>
	/// スプライトとフォントの描画情報を更新
	/// </summary>
	void UpdateSpriteDrawInfo();
	/// <summary>
	/// 個々のスプライトの描画フラグを保持する構造体です。
	/// </summary>
	struct SpriteListData
	{
		/// <summary>
		/// 個別の描画フラグを示すブール値の変数です。
		/// </summary>
		bool m_isDraw = false;
		/// <summary>
		/// スプライト描画用のポインタを格納するメンバー変数です。
		/// </summary>
		SpriteRender* m_spritePtr = nullptr; 
		/// <summary>
		/// スプライトの位置を表す3次元ベクトルを初期化します。
		/// </summary>
		Vector2 m_spritePosition = Vector2::Zero;
	};
	/// <summary>
	/// フォントリストのデータを保持する構造体です。
	/// </summary>
	struct FontListData
	{
		/// <summary>
		/// 個別のフォント描画フラグを示すブール値の変数です。
		/// </summary>
		bool m_isDraw = false;
		/// <summary>
		/// フォント描画用のポインタを格納するメンバー変数です。
		/// </summary>
		FontRender* m_fontPtr = nullptr;
		/// <summary>
		/// スプライトの位置をゼロベクトルで初期化します。
		/// </summary>
		Vector2 m_spritePosition = Vector2::Zero; 
	};
	/// <summary>
	/// 描画フラグを示すブール値の変数です。
	/// </summary>
	bool m_drawFlag = true;
	/// <summary>
	/// 2次元ベクトルの基準位置をゼロベクトルで初期化します。
	/// </summary>
	Vector2 m_basePosition = Vector2::Zero;
	/// <summary>
	/// EnGameUiState 型の変数 m_state を en_init で初期化します。
	/// </summary>
	EnGameUiState m_state = en_standby; 
	/// <summary>
	/// int型のキーとSpriteRenderポインタを関連付けるマップです。
	/// </summary>
	std::map<int,SpriteListData> m_spriteList;
	/// <summary>
	/// フォントレンダリングオブジェクトへのポインタを格納するマップです。
	/// </summary>
	std::map<int, FontListData> m_fontList;
};

