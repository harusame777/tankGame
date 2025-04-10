#pragma once

class GameLoad : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameLoad(){}
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameLoad(){}
	/// <summary>
	/// ロード種類ステート
	/// </summary>
	enum LoadTypeState
	{
		//通常ロード
		en_loadOrdinary,
		//円形ロード
		en_loadCircular,
		//即時明暗ロード
		en_loadImmediately
	};
	/// <summary>
	/// フェードアウトしきったか？
	/// </summary>
	/// <returns></returns>
	bool IsLoadBlackout() const
	{
		if (m_loadProccesState == LoadProccesState::en_loadBlackoutStandby)
		{
			return true;
		}
		return false;
	}
	/// <summary>
	/// フェードインしきったか？
	/// </summary>
	/// <returns></returns>
	bool IsLoadCompletion() const 
	{
		return m_loadCompletionFlag;
	}
private:
	/// <summary>
	/// ロードの処理順
	/// </summary>
	enum LoadOrder
	{
		//フェードアウト実行状態(暗くなる方)
		en_FadeOut,
		//フェードイン実行状態(明るくなる方)
		en_FadeIn,
	};
	/// <summary>
	/// ロードの実行ステート
	/// </summary>
	enum LoadProccesState
	{
		//ロード待機状態
		en_loadStandby,
		//フェードイン実行状態(明るくなる方)
		en_loadExecutionFadeIn,
		//フェードアウト実行状態(暗くなる方)
		en_loadExecutionFadeOut,
		//時間経過で自動的にフェードインするロード
		en_loadExecutionTimeLapse,
		//ロード暗転待機
		en_loadBlackoutStandby,
		//ロード時間待機
		en_loadWaitTime,
		//ロード完了
		en_loadCompletion
	};
	LoadProccesState m_loadProccesState = LoadProccesState::en_loadStandby;
	/// <summary>
	/// ロード種類ステート格納変数
	/// </summary>
	LoadTypeState m_loadTypeState[2];
public:
	struct LoadOrderData
	{
		//フェードアウトするロード
		LoadTypeState m_fadeOutLoad;
		//フェードインするロード
		LoadTypeState m_fadeInLoad;
	};
	/// <summary>
	/// フェードアウトを実行する
	/// </summary>
	/// <param name="loadType"></param>
	void LoadExecutionFadeOut(const LoadOrderData& loadType,const float loadTime);
	/// <summary>
	/// フェードインを実行する
	/// </summary>
	void LoadExecutionFadeIn();
private:
	/// <summary>
	/// ロードのデータ
	/// </summary>
	struct LoadDatas
	{
	private:
		/// <summary>
		/// 距離値
		/// </summary>
		float m_loadIndex = 0.0f;
		/// <summary>
		/// ロードのステートをシェーダーに送る変数
		/// </summary>
		int m_loadState = 0;
	public:
		/// <summary>
		/// ロード数値を設定
		/// </summary>
		/// <param name="value"></param>
		void SetLoadIndex(const float& value)
		{
			m_loadIndex = value;
		}
		/// <summary>
		/// ロード数値を取得
		/// </summary>
		/// <returns></returns>
		const float& GetLoadIndex() const
		{
			return m_loadIndex;
		}
		/// <summary>
		/// 送るデータのステートを設定
		/// </summary>
		/// <param name="stateValue"></param>
		void SetLoadTypeState(const LoadTypeState& stateValue)
		{
			m_loadState = stateValue;
		}
	};
	LoadDatas m_loadDatas;
	/// <summary>
	/// スタート関数
	/// </summary>
	bool Start();
	/// <summary>
	/// アップデート関数
	/// </summary>
	void Update();
	/// <summary>
	/// ロードステートアップデート
	/// </summary>
	void LoadStateUpdate();
	/// <summary>
	/// ロード計算
	/// </summary>
	/// <returns></returns>
	const float& LoadCalc(const float& index);
	void LoadOptionSpriteUpdate();
	/// <summary>
	/// ロード待ち時間
	/// </summary>
	/// <param name="time"></param>
	/// <returns></returns>
	const bool LoadWaitTime();
	/// <summary>
	/// 時間関係
	/// </summary>
	float m_loadTime = 0.0f;
	float m_timer = 0.0f;
	/// <summary>
	/// レンダー関数
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// ロード割合
	/// </summary>
	float m_loadRatio = 0.0f;
	/// <summary>
	/// イージングに使用する変数
	/// </summary>
	float m_loadEasingMax = 0.0f;
	float m_loadEasingMin = 0.0f;
	float m_loadSpeedAttenuationRate[2];
	/// <summary>
	/// ロードが完了したかどうか
	/// </summary>
	bool m_loadCompletionFlag = false;
	/// <summary>
	/// オプションスプライトの回転大
	/// </summary>
	Quaternion m_loadOptionLargeRotation;
	/// <summary>
	/// オプションスプライトの回転小
	/// </summary>
	Quaternion m_loadOptionSmallRotation;
	/// <summary>
	/// ロード後ろ側スプライト
	/// </summary>
	SpriteRender m_loadBackSideSprite;
	/// <summary>
	/// ロードのオプションスプライト大
	/// </summary>
	SpriteRender m_loadOptionSpriteLarge;
	/// <summary>
	/// ロードのオプションスプライト大
	/// </summary>
	SpriteRender m_loadOptionSpriteSmall;
	/// <summary>
	/// flaot用線形補間
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <param name="t"></param>
	/// <returns></returns>
	const float Leap(const float a, const float b, const float t)
	{
		return (1.0f - t) * a + t * b;
	}
};

