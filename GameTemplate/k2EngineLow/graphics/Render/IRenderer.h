#pragma once

namespace nsK2EngineLow {
	/// <summary>
	/// �����_���[(���f�������_�[�A�X�v���C�g�����_�[�Ȃ�)
	/// �̊��N���X
	/// </summary>
	class IRenderer : public Noncopyable{
	public:
		//�R���X�g���N�^
		IRenderer() 
		{

		}
		//�f�X�g���N�^(���N���X�Ȃ̂ŉ��z��)
		virtual ~IRenderer() 
		{

		}

		//3D���f���̕`��
		virtual void OnRenderModel(RenderContext& rc)
		{

		}

		//2D�`��
		virtual void OnRender2D(RenderContext& rc)
		{

		}

		//���O2D�`��
		virtual void OnPreRender2D(RenderContext& rc)
		{

		}

		//�V���h�E�}�b�v�ւ̕`�揈��
		virtual void OnRenderShadowMap(RenderContext& rc)
		{

		}

		//GBuffer�̕`�揈��
		virtual void OnRenderToGBuffer(RenderContext& rc)
		{

		}
	};
}