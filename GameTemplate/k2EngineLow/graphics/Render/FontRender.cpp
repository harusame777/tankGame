#include "k2EngineLowPreCompile.h"
#include "FontRender.h"

namespace nsK2EngineLow {

	//�`��
	void FontRender::Draw(RenderContext& rc)
	{
		//�e�L�X�g���ݒ肳��Ă��Ȃ�������
		if (m_text == nullptr)
		{
			//�`�悵�Ȃ�
			return;
		}
		g_renderingEngine->AddRenderObject(this);
	}

	//2D�`��
	void FontRender::OnRender2D(RenderContext& rc)
	{
		//�e�L�X�g���ݒ肳��Ă��Ȃ�������
		if (m_text == nullptr)
		{
			//�`�悵�Ȃ�
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