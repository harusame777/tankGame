#include "k2EngineLowPreCompile.h"
#include "ShadowMapRender.h"

namespace nsK2EngineLow {

	//初期化処理
	void ShadowMapRender::Init()
	{
		float clearColor[4] = { 1.0f,1.0f,1.0f,1.0f };

		//シャドウマップ用のレンダリングターゲットを作成
		m_shadowMap.Create(
			4096,
			4096,
			1,
			1,
			//DXGI_FORMAT_R32_FLOAT,デプスシャドウ用の設定
			DXGI_FORMAT_R32G32_FLOAT,
			DXGI_FORMAT_D32_FLOAT,
			clearColor
		);

		m_shadowMapModelGaussianBlur.Init(
			&m_shadowMap.GetRenderTargetTexture()
		);
	}

	//シャドウマップ描画
	void ShadowMapRender::RenderShadowMap(
		RenderContext& renderContext,
		std::vector<IRenderer*>& renderObjects
	)
	{
		//シャドウマップ用レンダリングターゲットが使用可能になるまで待機
		renderContext.WaitUntilToPossibleSetRenderTarget(m_shadowMap);
		//レンダリングターゲットをシャドウマップに変更
		renderContext.SetRenderTargetAndViewport(m_shadowMap);
		//レンダリングターゲットをクリア
		renderContext.ClearRenderTargetView(m_shadowMap);

		for (auto& renderObj : renderObjects)
		{
			renderObj->OnRenderShadowMap(renderContext);
		}

		renderContext.WaitUntilFinishDrawingToRenderTarget(m_shadowMap);

		ShadouMapBlurExecute(renderContext);

		renderContext.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);

		renderContext.SetViewportAndScissor(g_graphicsEngine->GetFrameBufferViewport());
	}
}