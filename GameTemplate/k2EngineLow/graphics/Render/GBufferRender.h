#pragma once

namespace nsK2EngineLow {
	class GBufferRender : public Noncopyable
	{
	public:

		//初期化処理
		void Init();

		//GBuffer描画処理
		void RenderGBuffer(
			RenderContext& rc,
			std::vector<IRenderer*>& renderObjects
		);

		//GBufferの定義
		enum EnGBuffer
		{
			enGBufferAlbed,//アルベド
			enGBufferNormal,//法線

			enGBufferNum//GBufferの数
		};

	private:
		//GBuffer
		RenderTarget m_gBuffer[enGBufferNum];
	};
}

