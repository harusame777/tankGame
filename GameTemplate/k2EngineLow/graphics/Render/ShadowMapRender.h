#pragma once
#include "graphics/GaussianBlur.h"

namespace nsK2EngineLow {
	class IRenderer;

	class ShadowMapRender : Noncopyable
	{
	public:

		//�V���h�E�}�b�v����������
		void Init();

		//�`�揈��
		void RenderShadowMap(
			RenderContext& rc,
			std::vector<IRenderer*>& renderObjects
		);

		RenderTarget* GetShadowMapRenderTarget()
		{
			return &m_shadowMap;
		}

		Texture& GetShadowMapBokeTexture()
		{
			return m_shadowMapModelGaussianBlur.GetBokeTexture();
		}

		void ShadouMapBlurExecute(RenderContext& rc)
		{
			m_shadowMapModelGaussianBlur.ExecuteOnGPU(rc, 5.0f);
		}

	protected:
		//�����_�����O�^�[�Q�b�g(�e)
		RenderTarget m_shadowMap;
		//�K�E�V�A���u���[
		GaussianBlur m_shadowMapModelGaussianBlur;
	};
}

