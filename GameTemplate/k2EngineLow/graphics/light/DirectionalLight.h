#pragma once

namespace nsK2EngineLow {
	class DirectionalLight : Noncopyable
	{
	public:
		//�R���X�g���N�^
		DirectionalLight();
		//�f�X�g���N�^
		~DirectionalLight();

		//������ݒ�
		void SetDirection(const Vector3& direction)
		{
			m_directionLight->SetDirection(direction);
		}
		void SetDirection(float x, float y, float z)
		{
			m_directionLight->SetDirection({ x,y,z });
		}
		//�������擾
		const Vector3& GetDirection()
		{
			return m_directionLight->GetDirection();
		}
		//�����𐳋K��
		void LightDirectionNormalize()
		{
			m_directionLight->LightDirectionNormalize();
		}
		//�J���[��ݒ�
		void SetColor(const Vector3& color)
		{
			m_directionLight->m_color = color;
		}
		void SetColor(float r, float g, float b)
		{
			m_directionLight->SetColor({ r,g,b });
		}
		//�J���[���擾
		const Vector3& GetColor() const
		{
			return m_directionLight->GetColor();
		}
		//�e���L���X�g����悤�ɂ���
		void CastShadow()
		{
			m_directionLight->CastShadow();
		}
		//�e���L���X�g���Ȃ��悤�ɂ���
		void UnCastShadow()
		{
			m_directionLight->UnCastShadow();
		}
		//�r���[�v���W�F�N�V�����J�����ʒu�ݒ�
		void VPCamSetPosition(const Vector3& pos)
		{
			m_vprCam.SetPosition(pos);
			m_directionLight->SetVPCamPosition(pos);
		}
		//�r���[�v���W�F�N�V�����J������]�ݒ�
		void VPCamSetRotation(const float& rot)
		{
			m_vprCam.SetViewAngle(Math::DegToRad(rot));
		}
		//�r���[�v���W�F�N�V�����J�����^�[�Q�b�g�ݒ�
		void VPCamSetTarget(const Vector3& target)
		{
			m_vprCam.SetTarget(target);
		}
		//�r���[�v���W�F�N�V�����J����������ݒ�
		void VPCamSetUp(const Vector3& up)
		{
			m_vprCam.SetUp(up);
		}
		//�r���[�v���W�F�N�V�����J�����X�V
		void VPCamUpdate()
		{
			m_vprCam.Update();

			m_directionLight->SetLightVP(m_vprCam.GetViewProjectionMatrix());
			m_directionLight->SetVPCamPosition(m_vprCam.GetPosition());
		}
	private:
		//�f�B���N�V�������C�g�̍\����
		SDirectionLight* m_directionLight = nullptr;
		//���C�g�̃r���[�v���W�F�N�V�����p�̃J����
		Camera m_vprCam;
	};
}

