#pragma once
#include "physics/PhysicsGhostObject.h"

namespace nsK2EngineLow {

	//���̃R���W�����Ɠ����蔻����s���N���X
	class CollisionObject : public IGameObject
	{
	public:
		//�R���X�g���N�^
		CollisionObject();
		//�f�X�g���N�^
		~CollisionObject();
		//�X�^�[�g�֐�
		bool Start();
		//�A�b�v�f�[�g�֐�
		void Update();

		/// <summary>
		/// �{�b�N�X�`��̃S�[�X�g�I�u�W�F�N�g���쐬
		/// </summary>
		/// <param name="pos"></param>
		/// <param name="rot"></param>
		/// <param name="size"></param>
		void CreateBox(Vector3 pos, Quaternion rot, Vector3 size)
		{
			m_psysicsGhostObject.CreateBox(pos, rot, size);
		}
		/// <summary>
		/// �J�v�Z���`��̃S�[�X�g�I�u�W�F�N�g���쐬
		/// </summary>
		/// <param name="pos"></param>
		/// <param name="rot"></param>
		/// <param name="radius"></param>
		/// <param name="height"></param>
		void CreateCapsule(Vector3 pos, Quaternion rot, float radius, float height)
		{
			m_psysicsGhostObject.CreateCapsule(pos, rot, radius, height);
		}
		/// <summary>
		/// ���`��̃S�[�X�g�I�u�W�F�N�g���쐬
		/// </summary>
		/// <param name="pos"></param>
		/// <param name="rot"></param>
		/// <param name="radius"></param>
		void CreateSphere(Vector3 pos, Quaternion rot, float radius)
		{
			m_psysicsGhostObject.CreateSphere(pos, rot, radius);
		}
		/// <summary>
		/// ���b�V���`��̃S�[�X�g�I�u�W�F�N�g���쐬
		/// </summary>
		/// <param name="pos"></param>
		/// <param name="rot"></param>
		/// <param name="model"></param>
		/// <param name="worldMatrix"></param>
		void CreateMesh(Vector3 pos, Quaternion rot, const Model& model, const Matrix& worldMatrix)
		{
			m_psysicsGhostObject.CreateMesh(pos, rot, model, worldMatrix);
		}
		/// <summary>
		/// �ݒ肵������(�b)���o�߂���Ǝ����ō폜����܂��B0.0f��ݒ肵����1�t���[���o�߂ō폜����܂��B
		/// </summary>
		/// <param name="timeLimit"></param>
		void SetTimeLimit(const float timeLimit)
		{
			m_timeLimit = timeLimit;
		}
		/// <summary>
		/// ���O��ݒ�
		/// </summary>
		/// <param name="name"></param>
		void SetName(const char* name)
		{
			m_name = name;
		}
		/// <summary>
		/// ���O���擾
		/// </summary>
		/// <returns></returns>
		const char* GetName() const
		{
			return m_name;
		}
		/// <summary>
		/// ���W��ݒ�
		/// </summary>
		/// <param name="position"></param>
		void SetPosition(const Vector3& position)
		{
			m_psysicsGhostObject.SetPosition(position);
		}
		/// <summary>
		/// ��]��ݒ�
		/// </summary>
		/// <param name="rotation"></param>
		void SetRotation(const Quaternion& rotation)
		{
			m_psysicsGhostObject.SetRotation(rotation);
		}
		/// <summary>
		/// �s���ݒ�
		/// </summary>
		/// <param name="matrix"></param>
		void SetWorldMatrix(const Matrix& matrix)
		{
			Vector3 position;
			position.x = matrix.m[3][0];
			position.y = matrix.m[3][1];
			position.z = matrix.m[3][2];
			SetPosition(position);
			Quaternion rotation;
			rotation.SetRotation(matrix);
			SetRotation(rotation);
		}
		/// <summary>
		/// �����ō폜���邩�ǂ�����ݒ肷��B
		/// </summary>
		/// <param name="isFlag"></param>
		void SetIsEnableAutoDelete(bool isFlag)
		{
			m_isEnableAutoDelete = isFlag;
		}
		/// <summary>
		/// �R���W�����I�u�W�F�N�g�ƃL�����R���̓����蔻��B
		/// </summary>
		/// <param name="characterController"></param>
		/// <returns></returns>
		const bool IsHit(CharacterController& characterController) const
		{
			bool isCollision = false;
			PhysicsWorld::GetInstance()->ContactTest(characterController, [&](const btCollisionObject& contactObject) {
				if (m_psysicsGhostObject.IsSelf(contactObject) == true) {
					isCollision = true;
				}
				});
			return isCollision;
		}
		/// <summary>
		/// �S�[�X�g�I�u�W�F�N�g���擾
		/// </summary>
		/// <returns></returns>
		PhysicsGhostObject& GetGhostObject()
		{
			return m_psysicsGhostObject;
		}
		/// <summary>
		/// bt�R���W�����I�u�W�F�N�g���擾
		/// </summary>
		/// <returns></returns>
		btCollisionObject& GetCollisionObject()
		{
			return m_psysicsGhostObject.GetbtCollisionObject();
		}
		/// <summary>
		/// �����蔻�肪�L�����ǂ����ݒ肷��
		/// </summary>
		/// <param name="isEnable"></param>
		void SetIsEnable(bool isEnable)
		{
			m_isEnable = isEnable;
		}
		/// <summary>
		/// �����蔻�肪�L�����ǂ����𒲂ׂ�
		/// </summary>
		/// <returns></returns>
		const bool IsEnable() const
		{
			return m_isEnable;
		}

	private:
		PhysicsGhostObject		m_psysicsGhostObject;	//�S�[�X�g�I�u�W�F�N�g
		const char*				m_name = nullptr;		//���O
		float					m_timer = 0.0f;			//�^�C�}�[
		float					m_timeLimit = 0.0f;		//�폜�����܂ł̎���
		bool					m_isEnableAutoDelete;	//�����ō폜�����Ȃ�true
		bool					m_isEnable = true;		//true�Ȃ炠���蔻��L��
	};

	class CollisionObjectManager
	{
	public:
		CollisionObjectManager();
		~CollisionObjectManager();
		/// <summary>
		/// �R���W�����I�u�W�F�N�g��ǉ�
		/// </summary>
		/// <param name="collisionObject"></param>
		void AddCollisionObject(CollisionObject* collisionObject)
		{
			m_collisionObjectVector.push_back(collisionObject);
		}
		/// <summary>
		/// ���O�����S��v����R���W�����I�u�W�F�N�g����������
		/// �A�������1����
		/// </summary>
		/// <param name="name"></param>
		/// <returns></returns>
		CollisionObject* FindCollisionObject(const char* name)
		{
			for (auto collisionObject : m_collisionObjectVector)
			{
				//���O����v������
				if (strcmp(collisionObject->GetName(),name) == 0)
				{
					//�����蔻�肪�L���Ȃ�
					if (collisionObject->IsEnable() == true)
					{
						return collisionObject;
					}
				}
			}
			//��v���閼�O�������ꍇ��NULL��Ԃ�
			return nullptr;
		}
		/// <summary>
		/// ���O�����S��v����R���W�����I�u�W�F�N�g����������
		/// �A������͕���
		/// </summary>
		/// <param name="name"></param>
		/// <returns></returns>
		const std::vector<CollisionObject*>& FindCollisionObjects(const char* name)
		{
			m_findMatchForwardNameCollisionObjectVector.clear();
			for (auto collisionObject : m_collisionObjectVector)
			{
				//���O����v������
				if (strcmp(collisionObject->GetName(),name) == 0)
				{
					//�����蔻�肪�L���Ȃ�
					if (collisionObject->IsEnable() == true)
					{
						m_findMatchForwardNameCollisionObjectVector.push_back(collisionObject);
					}
				}
			}
			return m_findMatchForwardNameCollisionObjectVector;
		}
		/// <summary>
		/// ���O���O����v����R���W�����I�u�W�F�N�g����������
		/// �A�������1����
		/// </summary>
		/// <param name="name"></param>
		/// <returns></returns>
		const CollisionObject* FindMatchForwardNameCollisionObject(const char* name)
		{
			for (auto collisionObject : m_collisionObjectVector)
			{
				auto len = strlen(name);
				auto namelen = strlen(collisionObject->GetName());
				if (len > namelen)
				{
					//�R���W�����̖��O����������蒷���̂ŁA�s��v
					continue;
				}
				//
				if (strncmp(name,collisionObject->GetName(),len) == 0)
				{
					//�����蔻�肪�L���Ȃ�
					if (collisionObject->IsEnable() == 0)
					{
						return collisionObject;
					}
				}
			}
			return nullptr;
		}
		/// <summary>
		/// ���O���O����v����R���W�����I�u�W�F�N�g����������
		/// �A������͕���
		/// </summary>
		/// <param name="name"></param>
		/// <returns></returns>
		const std::vector<CollisionObject*>& FindMatchForwardNameCollisionObjects(const char* name)
		{
			m_findsCollisionObjectVector.clear();
			for (auto collisionObject : m_collisionObjectVector)
			{
				auto len = strlen(name);
				auto namelen = strlen(collisionObject->GetName());
				if (len > namelen)
				{
					//�R���W�����̖��O����������蒷���̂ŁA�s��v
					continue;
				}
				//
				if (strncmp(name, collisionObject->GetName(), len) == 0)
				{
					//�����蔻�肪�L���Ȃ�
					if (collisionObject->IsEnable() == 0)
					{
						m_findsCollisionObjectVector.push_back(collisionObject);
					}
				}
			}
			return m_findsCollisionObjectVector;
		}
		/// <summary>
		/// �z�񂩂�R���W�����I�u�W�F�N�g���폜
		/// </summary>
		/// <param name="deleteCollisionObject"></param>
		void RemoveCollisionObject(CollisionObject* deleteCollisionObject)
		{
			for (auto it = m_collisionObjectVector.begin(); it != m_collisionObjectVector.end();)
			{
				//��������v�����v�f���폜����
				if (*it == deleteCollisionObject)
				{
					//�폜���ꂽ�v�f�̎����w���C�e���[�^���Ԃ����
					it = m_collisionObjectVector.erase(it);
				}
				//�v�f�폜�����Ȃ��ꍇ�ɁA�C�e���[�^�[��i�߂�
				else
				{
					++it;
				}
			}
		}
	private:
		std::vector<CollisionObject*> m_collisionObjectVector;
		std::vector<CollisionObject*> m_findsCollisionObjectVector;
		std::vector<CollisionObject*> m_findMatchForwardNameCollisionObjectVector;
	};
}
