#pragma once

namespace nsK2EngineLow {
	class PointLight : public Noncopyable
	{
	public:
		//�R���X�g���N�^
		PointLight();
		//�f�X�g���N�^
		~PointLight();

		//���W��ݒ�
		void SetPosition(const Vector3& position)
		{
			m_pointLight->SetPosition(position);
		}
		void SetPosition(float x, float y, float z)
		{
			m_pointLight->SetPosition(x, y, z);
		}

		//�J���[��ݒ�
		void SetColor(const Vector3& color)
		{
			m_pointLight->SetColor(color);
		}
		void SetColor(float r, float g, float b)
		{
			m_pointLight->SetColor(r, g, b);
		}

		//�͈͂�ݒ�
		void SetRange(const float range)
		{
			m_pointLight->SetRange(range);
		}

		//�e�����̗ݏ搔��ݒ�
		void SetAffectPowParam(const float powParam)
		{
			m_pointLight->SetAffectPowParam(powParam);
		}

		//���W���擾
		const Vector3& GetPosition() const
		{
			return m_pointLight->GetPosition();
		}
		//�J���[���擾
		const Vector3& GetColor() const
		{
			return m_pointLight->GetColor();
		}
		//�e���͈͂��擾
		const float GetRange() const
		{
			return m_pointLight->GetRange();
		}
		//���f�[�^���擾
		const SPointLight& GetRawData() const 
		{
			return *m_pointLight;
		}

	private:
		SPointLight* m_pointLight = nullptr;
	};
}

