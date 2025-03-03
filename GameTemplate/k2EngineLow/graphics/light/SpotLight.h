#pragma once
namespace nsK2EngineLow {
	class SpotLight : public Noncopyable
	{
	public:
		//�R���X�g���N�^
		SpotLight();
		//�f�X�g���N�^
		~SpotLight();

		//���W��ݒ�
		void SetPosition(const Vector3& position)
		{
			m_spotLight->SetPosition(position);
		}
		void SetPosition(float x, float y, float z)
		{
			m_spotLight->SetPosition(x, y, z);
		}
		//���W���擾
		const Vector3& GetPosition() const
		{
			return m_spotLight->GetPosition();
		}
		//�J���[��ݒ�
		void SetColor(const Vector3& color)
		{
			m_spotLight->SetColor(color);
		}
		void SetColor(float r, float g, float b)
		{
			m_spotLight->SetColor(r, g, b);
		}
		//�J���[���擾
		const Vector3& GetColor() const
		{
			return m_spotLight->GetColor();
		}
		//�ˏo������ݒ�
		void SetDirection(const Vector3& direction)
		{
			m_spotLight->SetDirection(direction);
		}
		void SetDirection(float x, float y, float z)
		{
			m_spotLight->SetDirection(x, y, z);
		}
		//�ˏo�������擾
		const Vector3& GetDirection() const
		{
			return m_spotLight->GetDirection();
		}
		//�e���͈͂�ݒ�
		void SetRange(const float range)
		{
			m_spotLight->SetRange(range);
		}
		//�e���͈͂��擾
		float GetRange() const
		{
			return m_spotLight->GetRange();
		}
		//�ˏo�p�x��ݒ�
		//�P�ʂ�Degree�A�v����ɕ��i�g���Ă遛���x
		void SetAngle(float angle)
		{
			//Deg��Rad�ɕϊ�
			angle = Math::DegToRad(angle);
			m_spotLight->SetAngle(angle);
		}
		//�ˏo�p�x���擾
		//�P�ʂ�Degree�A�v����ɕ��i�g���Ă遛���x
		const float GetAngle()const
		{
			//Rad��Deg�ɕϊ����Ă���n��
			return Math::DegToRad(m_spotLight->GetAngle());
		}
		//�����ɂ��e�����̗ݏ搔��ݒ�
		void SetRangeAffectPowParam(float powParam)
		{
			m_spotLight->SetRangeAffectPowParam(powParam);
		}
		//�p�x�ɂ��e�����̗ݏ搔��ݒ�
		void SetAngleAffectPowParam(float powParam)
		{
			m_spotLight->SetAngleAffectPowParam(powParam);
		}
		//���f�[�^���擾
		const SSpotLight& GetRawData() const
		{
			return *m_spotLight;
		}
	private:
		SSpotLight* m_spotLight = nullptr;
	};
}

