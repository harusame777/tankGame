#pragma once

namespace nsK2EngineLow {
	/// <summary>
	/// レンダラー(モデルレンダー、スプライトレンダーなど)
	/// の基底クラス
	/// </summary>
	class IRenderer : public Noncopyable{
	public:
		//コンストラクタ
		IRenderer() 
		{

		}
		//デストラクタ(基底クラスなので仮想化)
		virtual ~IRenderer() 
		{

		}

		//3Dモデルの描画
		virtual void OnRenderModel(RenderContext& rc)
		{

		}

		//2D描画
		virtual void OnRender2D(RenderContext& rc)
		{

		}

		//事前2D描画
		virtual void OnPreRender2D(RenderContext& rc)
		{

		}

		//シャドウマップへの描画処理
		virtual void OnRenderShadowMap(RenderContext& rc)
		{

		}

		//GBufferの描画処理
		virtual void OnRenderToGBuffer(RenderContext& rc)
		{

		}
	};
}