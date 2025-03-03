#pragma once

namespace nsK2EngineLow {
	class GBufferRender : public Noncopyable
	{
	public:

		//����������
		void Init();

		//GBuffer�`�揈��
		void RenderGBuffer(
			RenderContext& rc,
			std::vector<IRenderer*>& renderObjects
		);

		//GBuffer�̒�`
		enum EnGBuffer
		{
			enGBufferAlbed,//�A���x�h
			enGBufferNormal,//�@��

			enGBufferNum//GBuffer�̐�
		};

	private:
		//GBuffer
		RenderTarget m_gBuffer[enGBufferNum];
	};
}

