#pragma once

namespace nsK2EngineLow {

	static const int MAX_DIRECTIONAL_LIGHT = 4;
	static const int MAX_POINT_LIGHT = 32;
	static const int MAX_SPOT_LIGHT = 32;

	//�f�B���N�V�������C�g�̍\����
	struct SDirectionLight
	{
		//���C�g�̕���
		Vector3 m_direction;
		//�e���L���X�g���邩���Ȃ���
		int m_castShadow = true;
		//�J���[
		Vector3 m_color;
		//�g�p���ꂢ�Ă��邩�ǂ���
		int m_isUse = false;
		//���C�g�̃r���[�v���W�F�N�V����
		Matrix m_mt;
		//�r���[�v���W�F�N�V�����J�����̃|�W�V����
		Vector3 m_vPCamPosition;
	public:
		//������ݒ�
		void SetDirection(const Vector3& direction)
		{
			m_direction = direction;
		}
		void SetDirection(float x, float y, float z)
		{
			SetDirection({ x,y,z });
		}
		//�������擾
		const Vector3& GetDirection()
		{
			return m_direction;
		}
		//�����𐳋K��
		void LightDirectionNormalize()
		{
			m_direction.Normalize();
		}
		//�J���[��ݒ�
		void SetColor(const Vector3& color)
		{
			this->m_color = color;
		}
		void SetColor(float r, float g, float b)
		{
			SetColor({ r,g,b });
		}
		//�J���[���擾
		const Vector3& GetColor() const
		{
			return this->m_color;
		}
		//�e���L���X�g����悤�ɂ���
		void CastShadow()
		{
			m_castShadow = true;
		}
		//�e���L���X�g���Ȃ��悤�ɂ���
		void UnCastShadow()
		{
			m_castShadow = false;
		}
		//�f�B���N�V�������C�g���g�p���ɂ���
		//�G���W���Ŏg�p���邽�߂̊֐��Ȃ̂ŃQ�[��������Ăяo���Ȃ��悤����
		void Use()
		{
			m_isUse = true;
		}
		//�f�B���N�V�������C�g�𖢎g�p�ɂ���
		//�G���W���Ŏg�p���邽�߂̊֐��Ȃ̂ŃQ�[��������Ăяo���Ȃ��悤����
		void UnUse()
		{
			m_isUse = false;
		}
		//�f�B���N�V�������C�g���g�p�������ׂ�
		const int GetUse() const
		{
			return m_isUse;
		}
		//���C�g�̃r���[�v���W�F�N�V������o�^
		void SetLightVP(const Matrix& vp)
		{
			m_mt = vp;
		}
		//���C�g�̃r���[�v���W�F�N�V�������擾
		const Matrix& GetLightVP() const
		{
			return m_mt;
		}
		/// <summary>
		/// �r���[�v���W�F�N�V�����J�����̈ʒu�ݒ�
		/// </summary>
		/// <param name="vPCamPos"></param>
		void SetVPCamPosition(const Vector3& vPCamPos)
		{
			m_vPCamPosition = vPCamPos;
		}
		/// <summary>
		/// �r���[�v���W�F�N�V�����J�����̈ʒu�擾
		/// </summary>
		/// <returns></returns>
		const Vector3& GetVPCamPosition()const
		{
			return m_vPCamPosition;
		}
		
	};

	struct SPointLight 
	{
	private:
		Vector3 m_position = g_vec3Zero;
	    int m_isUse = false;
		Vector3 m_color = g_vec3One;
		float m_pad1;
		Vector3 attn = { 1.0f,1.0f,0.0f };
		float m_pad2;
	public:
		//���W��ݒ�
		void SetPosition(const Vector3& position)
		{
			this->m_position = position;
		}
		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x,y,z });
		}
		//���W���擾
		const Vector3& GetPosition()
		{
			return this->m_position;
		}
		//�J���[��ݒ�
		void SetColor(const Vector3& color)
		{
			this->m_color = color;
		}
		void SetColor(float r, float g, float b)
		{
			SetColor({ r,g,b });
		}
		//�J���[���擾
		const Vector3& GetColor() const
		{
			return this->m_color;
		}
		//�e���͈͂�ݒ�
		void SetRange(float range)
		{
			attn.x = range;
		}
		//�e���͈͂��擾
		float GetRange() const
		{
			return attn.x;
		}
		//�e�����̗ݏ搔
		void SetAffectPowParam(float powParam)
		{
			attn.y = powParam;
		}
		//�|�C���g���C�g���g�p���ɂ���
		//�G���W���Ŏg�p���邽�߂̊֐��Ȃ̂ŃQ�[��������Ăяo���Ȃ��悤����
		void Use()
		{
			m_isUse = true;
		}
		//�|�C���g���C�g�𖢎g�p�ɂ���
		//�G���W���Ŏg�p���邽�߂̊֐��Ȃ̂ŃQ�[��������Ăяo���Ȃ��悤����
		void UnUse()
		{
			m_isUse = false;
		}
		//�|�C���g���C�g���g�p�������ׂ�
		const int GetUse() const
		{
			return m_isUse;
		}
	};

	struct SSpotLight
	{
	private:
		Vector3 m_position = g_vec3Zero;
		int m_isUse = false;
		Vector3 m_color = g_vec3One;
		float m_range = 0.0f;
		Vector3 m_direction = g_vec3Down;
		float m_angle;
		Vector3 m_pow = { 1.0f,1.0f,1.0f };
		float m_pad;
	public:
		//���W��ݒ�
		void SetPosition(const Vector3& position)
		{
			this->m_position = position;
		}
		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x,y,z });
		}
		//���W���擾
		const Vector3& GetPosition()
		{
			return this->m_position;
		}
		//�J���[��ݒ�
		void SetColor(const Vector3& color)
		{
			this->m_color = color;
		}
		void SetColor(float r, float g, float b)
		{
			SetColor({ r,g,b });
		}
		//�J���[���擾
		const Vector3& GetColor() const
		{
			return this->m_color;
		}
		//�ˏo������ݒ�
		void SetDirection(const Vector3& direction)
		{
			m_direction = direction;
			m_direction.Normalize();
		}
		void SetDirection(float x, float y, float z)
		{
			m_direction.Set(x, y, z);
			m_direction.Normalize();
		}
		//�ˏo�������擾
		const Vector3& GetDirection() const
		{
			return m_direction;
		}
		//�ˏo�p�x��ݒ�
		void SetAngle(const float angle)
		{
			m_angle = angle;
		}
		//�ˏo�p�x���擾
		const float GetAngle() const
		{
			return m_angle;
		}
		//�e���͈͂�ݒ�
		void SetRange(const float range)
		{
			m_range = range;
		}
		//�e���͈͂��擾
		const float GetRange() const
		{
			return m_range;
		}
		//���̋����ɂ��e�����ɗݏ悷��l��ݒ�
		void SetRangeAffectPowParam(const float powParam)
		{
			m_pow.x = powParam;
		}
		//���̊p�x�ɂ��e�����ɗݏ悷��l��ݒ�
		void SetAngleAffectPowParam(const float powParam)
		{
			m_pow.y = powParam;
		}
		//�X�|�b�g���C�g���g�p���ɂ���
		//�G���W���Ŏg�p���邽�߂̊֐��Ȃ̂ŃQ�[��������Ăяo���Ȃ��悤����
		void Use()
		{
			m_isUse = true;
		}
		//�X�|�b�g���C�g�𖢎g�p�ɂ���
		//�G���W���Ŏg�p���邽�߂̊֐��Ȃ̂ŃQ�[��������Ăяo���Ȃ��悤����
		void UnUse()
		{
			m_isUse = false;
		}
		//�X�|�b�g���C�g���g�p�������ׂ�
		const int GetUse() const
		{
			return m_isUse;
		}
	};

	struct Light
	{
		//�f�B���N�V�������C�g�̔z��
		SDirectionLight m_directionalLight[MAX_DIRECTIONAL_LIGHT];
		//�|�C���g���C�g�̔z��
		SPointLight m_pointLights[MAX_POINT_LIGHT];
		//�X�|�b�g���C�g�̔z��
		SSpotLight m_spotLights[MAX_SPOT_LIGHT];
		//���_�̈ʒu
		Vector3 m_eyePos;
		//�g�p���̃|�C���g���C�g�̐�
		int m_numPointLight;
		//����
		Vector3 m_ambientLight;
		//�g�p���̃X�|�b�g���C�g�̐�
		int m_numSpotLight;
		Vector3 pad;
		//�g�p���̃f�B���N�V�������C�g�̐�
		int m_numDirectionLight;
		//�f�B���N�V�������C�g�̃r���[�v���W�F�N�V����
	};

	//�V�[�����C�g�N���X
	class SceneLight : public Noncopyable
	{
	public:
		//�R���X�g���N�^
		SceneLight();
		//�f�X�g���N�^
		~SceneLight();

		//������
		void Init();

		//�V�[�����C�g���擾
		Light& GetSceneLight()
		{
			return m_light;
		}

		//�e���L���X�g���邩
		bool IsCastShadow(int ligNo)
		{
			return m_light.m_directionalLight[ligNo].m_castShadow;
		}

		//������ݒ�
		void SetAmbient(Vector3 ambient)
		{
			m_light.m_ambientLight = ambient;
		}

		//�X�V����
		void Update();

		//�f�B���N�V�������C�g�z�񂩂疢�g�p�̃��C�g�̃|�C���^���
		SDirectionLight* NewDirectionLight();

		//�g�p���̃f�B���N�V�������C�g���폜(�A�h���X�ƍ�)
		void DeleteDirectionLight(SDirectionLight* directionlight);

		//�|�C���g���C�g�z�񂩂疢�g�p�̃��C�g�̃|�C���^���
		SPointLight* NewPointLight();

		//�g�p���̃|�C���g���C�g���폜(�A�h���X�ƍ�)
		void DeletePointLight(SPointLight* pointlight);

		//�X�|�b�g���C�g�z�񂩂疢�g�p�̃��C�g�̃|�C���^���
		SSpotLight* NewSpotLight();

		//�g�p���̃X�|�b�g���C�g���폜
		void DeleteSpotLight(SSpotLight* spotlight);
		
		//���C�g�̃f�[�^���擾
		Light* GetLightData()
		{
			return &m_light;
		}

		//�V�[�����C�g
		Light m_light;
	};
}

