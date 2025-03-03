#include "k2EngineLowPreCompile.h"
#include "GBufferRender.h"

namespace nsK2EngineLow {

	//����������
	void GBufferRender::Init()
	{
		//�t���[���o�b�t�@�[�̉����A�������擾
		int frameBuffer_w = g_graphicsEngine->GetFrameBufferWidth();
		int frameBuffer_h = g_graphicsEngine->GetFrameBufferHeight();


		//�A���x�h�p�̃����_�����O�^�[�Q�b�g��������
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

		//�@���p�̃����_�����O�^�[�Q�b�g��������
		m_gBuffer[enGBufferNormal].Create(
			frameBuffer_w,
			frameBuffer_h,
			1,
			1,
			DXGI_FORMAT_R8G8B8A8_SNORM,
			DXGI_FORMAT_UNKNOWN
		);
	}

	//�`�揈��
	void GBufferRender::RenderGBuffer(
		RenderContext& rc, 
		std::vector<IRenderer*>& renderObjects
	)
	{
		//�����_�����O�^�[�Q�b�g��GBuffer�ɕύX
		RenderTarget* rts[enGBufferNum] = {
			&m_gBuffer[enGBufferAlbed], // 0�Ԗڂ̃����_�����O�^�[�Q�b�g
			&m_gBuffer[enGBufferNormal],// 1�Ԗڂ̃����_�����O�^�[�Q�b�g
		};

		// �܂��A�����_�����O�^�[�Q�b�g�Ƃ��Đݒ�ł���悤�ɂȂ�܂ő҂�
		rc.WaitUntilToPossibleSetRenderTargets(ARRAYSIZE(rts), rts);

		//�����_�����O�^�[�Q�b�g��ݒ�
		rc.SetRenderTargets(ARRAYSIZE(rts), rts);

		//�����_�����O�^�[�Q�b�g���N���A
		rc.ClearRenderTargetViews(ARRAYSIZE(rts), rts);

		for (auto& renderObj : renderObjects){
			renderObj->OnRenderToGBuffer(rc);
		}

		//�����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
		rc.WaitUntilFinishDrawingToRenderTargets(ARRAYSIZE(rts), rts);
	}
}