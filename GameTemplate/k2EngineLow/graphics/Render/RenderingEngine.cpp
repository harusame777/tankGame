#include "k2EngineLowPreCompile.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow {

	//コンストラクタ
	RenderingEngine::RenderingEngine()
	{

	}

	//デストラクタ
	RenderingEngine::~RenderingEngine()
	{

	}

	//登録処理
	void RenderingEngine::Init()
	{
		//フレームバッファーの横幅、高さを取得
		int frameBuffer_w = g_graphicsEngine->GetFrameBufferWidth();
		int frameBuffer_h = g_graphicsEngine->GetFrameBufferHeight();

		float clearColor[4] = { 0.7f, 0.7f, 1.0f, 1.0f };
		//メインレンダリングターゲット
		mainRenderTargert.Create(
			frameBuffer_w,
			frameBuffer_h,
			1,
			1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT,
			clearColor
		);

		//フレームバッファーにテクスチャを張り付けるためのスプライトを初期化
		//初期化オブジェクトを作成
		SpriteInitData spriteInitData;

		//テクスチャはメインレンダリングターゲットのカラーバッファー
		spriteInitData.m_textures[0] = &mainRenderTargert.GetRenderTargetTexture();
		spriteInitData.m_width = frameBuffer_w;
		spriteInitData.m_height = frameBuffer_h;

		//スプライト表示用のシェーダーのファイルパスを指定する
		spriteInitData.m_fxFilePath = "Assets/shader/haruharuSprite.fx";

		//初期化オブジェクトを使用してスプライトを初期化
		m_copyToFrameBufferSprite.Init(spriteInitData);

		//GBufferの初期化
		//m_gBufferRender.Init();
		//輝度抽出初期化
		m_luminnceRender.Init(&mainRenderTargert);
		//シャドウマップの初期化
		m_shadowMapRender.Init();
	}

	void RenderingEngine::Execute(RenderContext& rc)
	{
		//シャドウマップ描画処理
		m_shadowMapRender.RenderShadowMap(
			rc,
			m_renderObjects
		);

		//G-Bufferへのレンダリング
		//m_gBufferRender.RenderGBuffer(
		//	rc,
		//	m_renderObjects
		//);

		//レンダリングターゲットをメインレンダリングターゲットに変更
		rc.WaitUntilToPossibleSetRenderTarget(mainRenderTargert);

		//レンダリングターゲットを設定
		rc.SetRenderTargetAndViewport(mainRenderTargert);

		//レンダリングターゲットをクリア
		rc.ClearRenderTargetView(mainRenderTargert);

		//モデルを描画
		Render3DModel(rc);

		EffectEngine::GetInstance()->Draw();

		//レンダリングターゲットへの書き込み終了待ち
		rc.WaitUntilFinishDrawingToRenderTarget(mainRenderTargert);

		//ココから輝度抽出～ボケ画像を作成
		m_luminnceRender.LuminnceExtraction(rc);

		//LuminnceExtractionで作成したボケ画像をメインレンダリングターゲットに
		//加算合成する
		//レンダリングターゲットとして利用できるまで待つ
		rc.WaitUntilToPossibleSetRenderTarget(mainRenderTargert);

		//レンダリングターゲットを設定
		rc.SetRenderTargetAndViewport(mainRenderTargert);

		//最終合成
		m_luminnceRender.AddSynthesisSpriteDraw(rc);

		//レンダリングターゲットの書き込み終了待ち
		rc.WaitUntilFinishDrawingToRenderTarget(mainRenderTargert);

		//メインレンダリングターゲットの絵をフレームバッファーにコピー
		rc.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);
		m_copyToFrameBufferSprite.Draw(rc);

		Render2DSprite(rc);

		// 登録されている描画オブジェクトをクリア
		m_renderObjects.clear();
	}

	//3Dモデル描画処理
	void RenderingEngine::Render3DModel(RenderContext& rc)
	{
		for (auto& renderObj : m_renderObjects)
		{
			renderObj->OnRenderModel(rc);
		}
	}

	//2D描画処理
	void RenderingEngine::Render2DSprite(RenderContext& rc)
	{
		for (auto& renderObj : m_renderObjects)
		{
			renderObj->OnRender2D(rc);
		}
	}

}