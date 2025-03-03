#include "k2EngineLowPreCompile.h"
#include "GBufferRender.h"

namespace nsK2EngineLow {

	//初期化処理
	void GBufferRender::Init()
	{
		//フレームバッファーの横幅、高さを取得
		int frameBuffer_w = g_graphicsEngine->GetFrameBufferWidth();
		int frameBuffer_h = g_graphicsEngine->GetFrameBufferHeight();


		//アルベド用のレンダリングターゲットを初期化
		float clearColor[] = { 0.5f, 0.5f, 0.5f, 1.0f };
		m_gBuffer[enGBufferAlbed].Create(
			frameBuffer_w,
			frameBuffer_h,
			1,
			1,
			DXGI_FORMAT_R8G8B8A8_UNORM,
			DXGI_FORMAT_D32_FLOAT,
			clearColor
		);

		//法線用のレンダリングターゲットを初期化
		m_gBuffer[enGBufferNormal].Create(
			frameBuffer_w,
			frameBuffer_h,
			1,
			1,
			DXGI_FORMAT_R8G8B8A8_SNORM,
			DXGI_FORMAT_UNKNOWN
		);
	}

	//描画処理
	void GBufferRender::RenderGBuffer(
		RenderContext& rc, 
		std::vector<IRenderer*>& renderObjects
	)
	{
		//レンダリングターゲットをGBufferに変更
		RenderTarget* rts[enGBufferNum] = {
			&m_gBuffer[enGBufferAlbed], // 0番目のレンダリングターゲット
			&m_gBuffer[enGBufferNormal],// 1番目のレンダリングターゲット
		};

		// まず、レンダリングターゲットとして設定できるようになるまで待つ
		rc.WaitUntilToPossibleSetRenderTargets(ARRAYSIZE(rts), rts);

		//レンダリングターゲットを設定
		rc.SetRenderTargets(ARRAYSIZE(rts), rts);

		//レンダリングターゲットをクリア
		rc.ClearRenderTargetViews(ARRAYSIZE(rts), rts);

		for (auto& renderObj : renderObjects){
			renderObj->OnRenderToGBuffer(rc);
		}

		//レンダリングターゲットへの書き込み終了待ち
		rc.WaitUntilFinishDrawingToRenderTargets(ARRAYSIZE(rts), rts);
	}
}