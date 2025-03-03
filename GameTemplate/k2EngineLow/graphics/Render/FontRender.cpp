#include "k2EngineLowPreCompile.h"
#include "FontRender.h"

namespace nsK2EngineLow {

	//描画
	void FontRender::Draw(RenderContext& rc)
	{
		//テキストが設定されていなかったら
		if (m_text == nullptr)
		{
			//描画しない
			return;
		}
		g_renderingEngine->AddRenderObject(this);
	}

	//2D描画
	void FontRender::OnRender2D(RenderContext& rc)
	{
		//テキストが設定されていなかったら
		if (m_text == nullptr)
		{
			//描画しない
			return;
		}

		m_font.Begin(rc);
		m_font.Draw(
			m_text,
			Vector2(m_position.x, m_position.y),
			m_color,
			m_rotation,
			m_scale,
			m_pivot
		);
		m_font.End(rc);
	}
}