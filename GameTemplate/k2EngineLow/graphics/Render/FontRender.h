#pragma once
namespace nsK2EngineLow {
	class FontRender : public IRenderer
	{
	public:
		static const int MAX_TEXT_SIZE = 256;

		//コンストラクタ
		FontRender() {};
		//デストラクタ
		~FontRender() {};

		//表示する文字を設定
		void SetText(const wchar_t* text)
		{
			swprintf_s(m_text, text);
		}
		//表示する文字を取得
		const wchar_t* GetText() const
		{
			return m_text;
		}

		//座標を設定
		void SetPosition(const Vector3& position)
		{
			m_position = position;
		}
		//座標を取得
		const Vector3& GetPosition() const
		{
			return m_position;
		}

		//拡大率を設定
		void SetScale(const float scale)
		{
			m_scale = scale;
		}
		//拡大率を取得
		const float GetScale() const
		{
			return m_scale;
		}

		//回転を設定
		//数字が増えると反時計回り、数字が減ると時計回りに回転する
		void SetRotation(const float rotation)
		{
			m_rotation = rotation;
		}
		//回転値を取得
		const float GetRotation() const
		{
			return m_rotation;
		}

		//色を設定
		void SetColor(const Vector4& color)
		{
			m_color = color;
		}
		//色を取得
		const Vector4& GetColor() const
		{
			return m_color;
		}

		//ピボットを設定
		void SetPivot(const Vector2& pivot)
		{
			m_pivot = pivot;
		}
		//ピボットを取得
		const Vector2& GetPivot() const
		{
			return m_pivot;
		}

		/// <summary>
		/// 影のパラメータを設定。
		/// </summary>
		/// <param name="isDrawShadow">影を描画する？</param>
		/// <param name="shadowOffset">影を描画するときのピクセルのオフセット量。</param>
		/// <param name="shadowColor">影の色。</param>
		void SetShadowParam(bool isDrawShadow, float shadowOffset, const Vector4& shadowColor)
		{
			m_font.SetShadowParam(isDrawShadow, shadowOffset, shadowColor);
		}

		//描画処理
		void Draw(RenderContext& rc);

		//2Dの描画処理
		void OnRender2D(RenderContext& rc) override;

	private:
		//座標
		Vector3		m_position = Vector3::Zero;
		//回転
		float		m_rotation = 0.0f;
		//文字の大きさ
		float		m_scale = 1.0f;
		//文字の色、デフォルトは白
		Vector4		m_color = g_vec4White;
		//ピボット、基点
		Vector2		m_pivot = Sprite::DEFAULT_PIVOT;
		//表示する文字
		wchar_t		m_text[MAX_TEXT_SIZE];
		Font		m_font;
	};
}