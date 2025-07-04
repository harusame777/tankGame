#pragma once

namespace nsK2EngineLow {
	class GBufferRender : public Noncopyable
	{
	public:

		//GBufferの定義
		enum EnGBuffer
		{
			enGBufferAlbed,//アルベド
			enGBufferNormal,//法線

			enGBufferNum//GBufferの数
		};

		//初期化処理
		void Init();

		//GBuffer描画処理
		void RenderGBuffer(
			RenderContext& rc,
			std::vector<IRenderer*>& renderObjects
		);

		void SetRenderTargetTexture(SpriteInitData& spriteInitData)
		{
			for (int gBufferNo = 0; gBufferNo < enGBufferNum; gBufferNo++)
			{
				spriteInitData.m_textures[gBufferNo] = &m_gBuffer[gBufferNo].GetRenderTargetTexture();
			}
		}

	private:
		//GBuffer
		RenderTarget m_gBuffer[enGBufferNum];
	};
}

