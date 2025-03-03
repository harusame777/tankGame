#include "k2EngineLowPreCompile.h"
#include "SpriteRender.h"

namespace nsK2EngineLow {
	
	//コンストラクタ
	SpriteRender::SpriteRender()
	{

	}

	//デストラクタ
	SpriteRender::~SpriteRender()
	{

	}

	//スプライト初期化処理
	void SpriteRender::Init(const char* filePath, const float w, const float h, AlphaBlendMode alphaBlendMode)
	{
		SpriteInitData initData;
		//DDSファイル(画像データ)のファイルパスを指定する
		initData.m_ddsFilePath[0] = filePath;
		//スプライト表示用のシェーダーのファイルパスを指定する
		initData.m_fxFilePath = "Assets/shader/haruharuSprite.fx";
		//スプライトの幅と高さを設定する
		initData.m_width = static_cast<UINT>(w);
		initData.m_height = static_cast<UINT>(h);
		initData.m_alphaBlendMode = alphaBlendMode;

		//スプライト初期オブジェクトを使用して、スプライトを初期化する
		m_sprite.Init(initData);
	}

	//描画関数
	void SpriteRender::Draw(RenderContext& rc)
	{
		g_renderingEngine->AddRenderObject(this);
	}
}