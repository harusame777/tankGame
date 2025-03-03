#pragma once
#include "graphics/GaussianBlur.h"

namespace nsK2EngineLow {
	class IRenderer;

	class ShadowMapRender : Noncopyable
	{
	public:

		//シャドウマップ初期化処理
		void Init();

		//描画処理
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
		//レンダリングターゲット(影)
		RenderTarget m_shadowMap;
		//ガウシアンブラー
		GaussianBlur m_shadowMapModelGaussianBlur;
	};
}

