#pragma once
#include "level3D/TklFile.h"

namespace nsK2EngineLow {
	/*!
	* @brief	�I�u�W�F�N�g���B
	*/
	//Level�N���X��LevelObjectData�Ƃ��Ԃ�̂�_Render��t���Ă���
	struct LevelObjectData_Render
	{
		/// <summary>
		/// ���W
		/// </summary>
		Vector3 m_position;
		/// <summary>
		/// ��]
		/// </summary>
		Quaternion m_rotation;
		/// <summary>
		/// �g�嗦
		/// </summary>
		Vector3 m_scalse;
		/// <summary>
		/// ���O
		/// </summary>
		const wchar_t* name;
		/// <summary>
		/// �i���o�[
		/// </summary>
		int number = 0;
		/// <summary>
		/// �����œn�����I�u�W�F�N�g���̃I�u�W�F�N�g�����ׂ�B
		/// </summary>
		/// <param name="objName = ���ׂ閼�O�B"></param>
		/// <returns></returns>
		bool EqualObjectName(const wchar_t* objName)
		{
			return wcscmp(objName, name) == 0;
		}
		bool ForwardMatchName(const wchar_t* n)
		{
			auto len = wcslen(n);
			auto namelen = wcslen(name);
			if (len > namelen)
			{
				//���O�������̂ŕs��v
				return false;
			}
			return wcsncmp(n, name, len) == 0;
		}
	};
	/// <summary>
	/// ���x��
	/// </summary>
	class LevelRender
	{
	public:
		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		~LevelRender();
		/// <summary>
		/// ���x����������	
		///�t�b�N���Ȃ��Ȃ�nullptr���w�肷��΂悢�A
		///���̊֐��I�u�W�F�N�g��false��Ԃ��ƁA�I�u�W�F�N�g�̏�񂩂�A
		///�ÓI�I�u�W�F�N�g��MapChip�N���X�̃C���X�^���X����������܂��B
		///�I�u�W�F�N�g�̖��O�ȂǂŁA�h�A��W�����v��A�A�C�e���Ȃǂ̓���ȃN���X�̃C���X�^���X�𐶐������Ƃ��ɁA
		///�f�t�H���g�ō쐬�����MapChip�N���X�̃C���X�^���X���s�v�ȏꍇ��true��Ԃ��Ă��������B
		///�Ⴆ�΁A�t�b�N�֐��̒��ŁA�n���ꂽ�I�u�W�F�N�g�f�[�^�̖��O�̃��f����`�悷��N���X�̃C���X�^���X��
		///���������Ƃ��ɁAfalse��Ԃ��Ă��܂��ƁA�������f������`�悳��邱�ƂɂȂ�܂��B
		/// </summary>
		/// <param name="filePath = tkl�t�@�C���̃t�@�C���p�X�B"></param>
		/// <param name="hookFunc = �I�u�W�F�N�g���쐬���鎞�̏������t�b�N���邽�߂̊֐��I�u�W�F�N�g�B"></param>
		void Init(const char* filePath, std::function<bool(LevelObjectData_Render& objData)> hookFunc);
		/// <summary>
		/// �X�V����
		/// </summary>
		void Update();
		/// <summary>
		/// ���f����`��
		/// </summary>
		/// <param name="rc = �����_�[�R���e�L�X�g�B"></param>
		void Draw(RenderContext& rc);
	private:
		/// <summary>
		/// Tkl�t�@�C���̍s���ϊ�����B
		/// </summary>
		void MatrixTklToLevel();
	private:
		using BonePtr = std::unique_ptr<Bone>;
		std::vector<BonePtr> m_boneList;
		std::unique_ptr<Matrix[]> m_matrixList;
		TklFile m_tklFile;
	};
}

