#include "k2EngineLowPreCompile.h"
#include "SpriteRender.h"

namespace nsK2EngineLow {
	
	//�R���X�g���N�^
	SpriteRender::SpriteRender()
	{

	}

	//�f�X�g���N�^
	SpriteRender::~SpriteRender()
	{

	}

	//�X�v���C�g����������
	void SpriteRender::Init(const char* filePath, const float w, const float h, AlphaBlendMode alphaBlendMode)
	{
		SpriteInitData initData;
		//DDS�t�@�C��(�摜�f�[�^)�̃t�@�C���p�X���w�肷��
		initData.m_ddsFilePath[0] = filePath;
		//�X�v���C�g�\���p�̃V�F�[�_�[�̃t�@�C���p�X���w�肷��
		initData.m_fxFilePath = "Assets/shader/haruharuSprite.fx";
		//�X�v���C�g�̕��ƍ�����ݒ肷��
		initData.m_width = static_cast<UINT>(w);
		initData.m_height = static_cast<UINT>(h);
		initData.m_alphaBlendMode = alphaBlendMode;

		//�X�v���C�g�����I�u�W�F�N�g���g�p���āA�X�v���C�g������������
		m_sprite.Init(initData);
	}

	//�`��֐�
	void SpriteRender::Draw(RenderContext& rc)
	{
		g_renderingEngine->AddRenderObject(this);
	}
}