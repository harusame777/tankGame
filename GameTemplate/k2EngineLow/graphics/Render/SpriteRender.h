#pragma once

namespace nsK2EngineLow {
	class SpriteRender : public IRenderer
	{
	public: 
		SpriteRender();
		~SpriteRender();

		//������
		void Init(const char* filePath, const float w, const float h, AlphaBlendMode alphaBlendMode = AlphaBlendMode_Trans);

		//���[�U�[���p�ӂ����f�[�^�ŏ�����
		void Init(SpriteInitData initData)
		{
			m_sprite.Init(initData);
		}

		//���W��ݒ�
		void SetPosition(const Vector3& position)
		{
			m_position = position;
		}
		//���W���擾
		const Vector3& GetPosition() const
		{
			return m_position;
		}

		//�X�P�[����ݒ�
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}
		//�X�P�[�����擾
		const Vector3& GetScale() const
		{
			return m_scale;
		}

		//��]��ݒ�
		void SetRotation(const Quaternion& rotation)
		{
			m_rotation = rotation;
		}
		//��]���擾
		const Quaternion& GetRotation() const
		{
			return m_rotation;
		}

		//�s�{�b�g��ݒ�
		void SetPivot(const Vector2& pivot)
		{
			m_pivot = pivot;
		}
		//�s�{�b�g���擾
		const Vector2& GetPivot() const
		{
			return m_pivot;
		}

		//��Z�J���[��ݒ�
		void SetMulColor(const Vector4& mulColor)
		{
			m_sprite.SetMulColor(mulColor);
		}
		//��Z�J���[���擾
		const Vector4& GetMulColor() const
		{
			return m_sprite.GetMulColor();
		}

		//�X�V����
		void Update()
		{
			m_sprite.Update(
				m_position,
				m_rotation,
				m_scale,
				m_pivot
			);
		}

		//�`�揈��
		void Draw(RenderContext& rc);

	private:
		//2D�`��p�X����Ă΂�鏈��
		void OnRender2D(RenderContext& rc) override
		{
			m_sprite.Draw(rc);
		}

	private:
		//�X�v���C�g
		Sprite m_sprite;
		//���W
		Vector3 m_position = Vector3::Zero;
		//��]
		Quaternion m_rotation = Quaternion::Identity;
		//�傫��
		Vector3 m_scale = Vector3::One;
		//�s�{�b�g(��_)
		Vector2 m_pivot = Sprite::DEFAULT_PIVOT;
	};
}

