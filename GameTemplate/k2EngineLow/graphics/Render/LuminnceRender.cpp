#include "k2EngineLowPreCompile.h"
#include "LuminnceRender.h"

namespace nsK2EngineLow {

	//����������
	void LuminnceRender::Init(RenderTarget* mainRenderTarget)
	{
		//�t���[���o�b�t�@�[�̉����A�������擾
		int frameBuffer_w = g_graphicsEngine->GetFrameBufferWidth();
		int frameBuffer_h = g_graphicsEngine->GetFrameBufferHeight();

		//�P�x���o�p�̃����_�����O�^�[�Q�b�g���쐬
		m_luminnceRenderTarget.Create(
			frameBuffer_w,
			frameBuffer_h,
			1,
			1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);

		//�P�x���o�p�̃X�v���C�g��������
		//���������쐬
		SpriteInitData luminnceSpriteInitData;

		//�P�x���o�p�̃V�F�[�_�[�̃t�@�C���p�X���w�肷��
		luminnceSpriteInitData.m_fxFilePath = "Assets/shader/haruharuPostEffect.fx";

		//���_�V�F�[�_�[�̃G���g���[�|�C���g���w��
		luminnceSpriteInitData.m_vsEntryPointFunc = "VSMain";

		//�s�N�Z���V�F�[�_�[�̃G���g���[�|�C���g���w��
		luminnceSpriteInitData.m_psEntryPoinFunc = "PSLuminance";

		//�X�v���C�g�̍������ƍ�����ݒ�
		luminnceSpriteInitData.m_width = frameBuffer_w;
		luminnceSpriteInitData.m_height = frameBuffer_h;

		//�e�N�X�`���̓��C�������_�����O�^�[�Q�b�g�̃o�b�t�@�[
		luminnceSpriteInitData.m_textures[0] = &mainRenderTarget->GetRenderTargetTexture();

		//�������ރ����_�����O�^�[�Q�b�g�̃t�H�[�}�b�g���w�肷��
		luminnceSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

		//�쐬�����������������ƂɃX�v���C�g������������
		m_luminnceSprite.Init(luminnceSpriteInitData);

		//�K�E�V�A���u���[��������
		//m_gaussianBlur[0]�͋P�x�e�N�X�`���Ƀu���[��������
		m_gaussianBlur[0].Init(&m_luminnceRenderTarget.GetRenderTargetTexture());

		//m_gaussianBlur[1]��m_gaussianBlur[0]�̃e�N�X�`���Ƀu���[��������
		m_gaussianBlur[1].Init(&m_gaussianBlur[0].GetBokeTexture());

		//m_gaussianBlur[2]��m_gaussianBlur[1]�̃e�N�X�`���Ƀu���[��������
		m_gaussianBlur[2].Init(&m_gaussianBlur[1].GetBokeTexture());

		//m_gaussianBlur[3]��m_gaussianBlur[2]�̃e�N�X�`���Ƀu���[��������
		m_gaussianBlur[3].Init(&m_gaussianBlur[2].GetBokeTexture());

		//�{�P�摜�����Z��������X�v���C�g��������
		//����������ݒ肷��
		SpriteInitData finalSpriteInitData;

		for (int i = 0; i < MAX_GAUSSIAN_BLUR; i++){
			finalSpriteInitData.m_textures[i] = &m_gaussianBlur[i].GetBokeTexture();
		}

		//�𑜓x��mainRenderTarGet�̕��ƍ���
		finalSpriteInitData.m_width = frameBuffer_w;
		finalSpriteInitData.m_height = frameBuffer_h;

		//�{�P�摜�����p�̃V�F�[�_�[��ݒ�
		finalSpriteInitData.m_fxFilePath = "Assets/shader/haruharuPostEffect.fx";
		//�������̃G���g���[�|�C���g��ݒ�
		finalSpriteInitData.m_psEntryPoinFunc = "PSBloomFinal";

		//���Z�����ŕ`�悷��̂ŁA�A���t�@�u�����f�B���O���[�h�����Z�ɂ���
		finalSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;

		//�J���[�o�b�t�@�[�̃t�H�[�}�b�g��32�r�b�g���������_�o�b�t�@�[
		finalSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

		//�������������Ƃɉ��Z�����p�̃X�v���C�g������������
		m_AddSynthesisSprite.Init(finalSpriteInitData);
	}

	//�P�x���o
	void LuminnceRender::LuminnceExtraction(RenderContext& rc)
	{
		//�P�x���o�p�̃����_�����O�^�[�Q�b�g�ɕύX
		rc.WaitUntilToPossibleSetRenderTarget(m_luminnceRenderTarget);

		//�����_�����O�^�[�Q�b�g��ݒ�
		rc.SetRenderTargetAndViewport(m_luminnceRenderTarget);

		//�����_�����O�^�[�Q�b�g���N���A
		rc.ClearRenderTargetView(m_luminnceRenderTarget);

		//�P�x���o���s��
		m_luminnceSprite.Draw(rc);

		//�����_�����O�^�[�Q�b�g�̏������ݏI���҂�
		rc.WaitUntilFinishDrawingToRenderTarget(m_luminnceRenderTarget);

		//�K�E�V�A���u���[�����s
		for (int i = 0; i < MAX_GAUSSIAN_BLUR; i++) {
			m_gaussianBlur[i].ExecuteOnGPU(rc, 50);
		}
	}
}