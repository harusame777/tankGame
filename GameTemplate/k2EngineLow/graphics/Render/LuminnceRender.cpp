#include "k2EngineLowPreCompile.h"
#include "LuminnceRender.h"

namespace nsK2EngineLow {

	//初期化処理
	void LuminnceRender::Init(RenderTarget* mainRenderTarget)
	{
		//フレームバッファーの横幅、高さを取得
		int frameBuffer_w = g_graphicsEngine->GetFrameBufferWidth();
		int frameBuffer_h = g_graphicsEngine->GetFrameBufferHeight();

		//輝度抽出用のレンダリングターゲットを作成
		m_luminnceRenderTarget.Create(
			frameBuffer_w,
			frameBuffer_h,
			1,
			1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);

		//輝度抽出用のスプライトを初期化
		//初期化情報作成
		SpriteInitData luminnceSpriteInitData;

		//輝度抽出用のシェーダーのファイルパスを指定する
		luminnceSpriteInitData.m_fxFilePath = "Assets/shader/haruharuPostEffect.fx";

		//頂点シェーダーのエントリーポイントを指定
		luminnceSpriteInitData.m_vsEntryPointFunc = "VSMain";

		//ピクセルシェーダーのエントリーポイントを指定
		luminnceSpriteInitData.m_psEntryPoinFunc = "PSLuminance";

		//スプライトの高さ幅と高さを設定
		luminnceSpriteInitData.m_width = frameBuffer_w;
		luminnceSpriteInitData.m_height = frameBuffer_h;

		//テクスチャはメインレンダリングターゲットのバッファー
		luminnceSpriteInitData.m_textures[0] = &mainRenderTarget->GetRenderTargetTexture();

		//書き込むレンダリングターゲットのフォーマットを指定する
		luminnceSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

		//作成した初期化情報をもとにスプライトを初期化する
		m_luminnceSprite.Init(luminnceSpriteInitData);

		//ガウシアンブラーを初期化
		//m_gaussianBlur[0]は輝度テクスチャにブラーをかける
		m_gaussianBlur[0].Init(&m_luminnceRenderTarget.GetRenderTargetTexture());

		//m_gaussianBlur[1]はm_gaussianBlur[0]のテクスチャにブラーをかける
		m_gaussianBlur[1].Init(&m_gaussianBlur[0].GetBokeTexture());

		//m_gaussianBlur[2]はm_gaussianBlur[1]のテクスチャにブラーをかける
		m_gaussianBlur[2].Init(&m_gaussianBlur[1].GetBokeTexture());

		//m_gaussianBlur[3]はm_gaussianBlur[2]のテクスチャにブラーをかける
		m_gaussianBlur[3].Init(&m_gaussianBlur[2].GetBokeTexture());

		//ボケ画像を加算合成するスプライトを初期化
		//初期化情報を設定する
		SpriteInitData finalSpriteInitData;

		for (int i = 0; i < MAX_GAUSSIAN_BLUR; i++){
			finalSpriteInitData.m_textures[i] = &m_gaussianBlur[i].GetBokeTexture();
		}

		//解像度はmainRenderTarGetの幅と高さ
		finalSpriteInitData.m_width = frameBuffer_w;
		finalSpriteInitData.m_height = frameBuffer_h;

		//ボケ画像合成用のシェーダーを設定
		finalSpriteInitData.m_fxFilePath = "Assets/shader/haruharuPostEffect.fx";
		//合成時のエントリーポイントを設定
		finalSpriteInitData.m_psEntryPoinFunc = "PSBloomFinal";

		//加算合成で描画するので、アルファブレンディングモードを加算にする
		finalSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;

		//カラーバッファーのフォーマットは32ビット浮動小数点バッファー
		finalSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

		//初期化情報をもとに加算合成用のスプライトを初期化する
		m_AddSynthesisSprite.Init(finalSpriteInitData);
	}

	//輝度抽出
	void LuminnceRender::LuminnceExtraction(RenderContext& rc)
	{
		//輝度抽出用のレンダリングターゲットに変更
		rc.WaitUntilToPossibleSetRenderTarget(m_luminnceRenderTarget);

		//レンダリングターゲットを設定
		rc.SetRenderTargetAndViewport(m_luminnceRenderTarget);

		//レンダリングターゲットをクリア
		rc.ClearRenderTargetView(m_luminnceRenderTarget);

		//輝度抽出を行う
		m_luminnceSprite.Draw(rc);

		//レンダリングターゲットの書き込み終了待ち
		rc.WaitUntilFinishDrawingToRenderTarget(m_luminnceRenderTarget);

		//ガウシアンブラーを実行
		for (int i = 0; i < MAX_GAUSSIAN_BLUR; i++) {
			m_gaussianBlur[i].ExecuteOnGPU(rc, 50);
		}
	}
}