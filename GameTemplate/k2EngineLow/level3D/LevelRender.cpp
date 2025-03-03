#include "k2EngineLowPreCompile.h"
#include "LevelRender.h"

namespace nsK2EngineLow {

	//�f�X�g���N�^
	LevelRender::~LevelRender()
	{

	}

	//������
	void LevelRender::Init(
		const char* filePath,
		std::function<bool(LevelObjectData_Render& objData)> hookFunc)
	{
		//tkl�t�@�C�������[�h����
		m_tklFile.Load(filePath);

		MatrixTklToLevel();

		//���[�g�{�[���͗v��Ȃ��ׁAi��1����n�߂邱�Ƃŏ��O�ł���B
		for (int i = 1; i < m_boneList.size(); i++){
			auto bone = m_boneList[i].get();
			if (bone->GetParentBoneNo() == 0)
			{
				
				//�}�b�v�`�b�v���쐬����
				//�s�񂩂�|�W�V�������쐬
				LevelObjectData_Render levelObjData;
				bone->CalcWorldTRS(levelObjData.m_position, levelObjData.m_rotation,
					levelObjData.m_scalse);

				//Zup��Yup�̕ύX
				float fix = levelObjData.m_position.y;
				levelObjData.m_position.y = levelObjData.m_position.z;
				levelObjData.m_position.z = -fix;

				fix = levelObjData.m_rotation.y;
				levelObjData.m_rotation.y = levelObjData.m_rotation.z;
				levelObjData.m_rotation.z = -fix;

				std::swap(levelObjData.m_scalse.y, levelObjData.m_scalse.z);
				//Zup��Yup�I���B

				levelObjData.name = m_boneList[i]->GetName();
				std::wstring wstr_name = levelObjData.name;
				//@�����邩�ǂ���������
				int pos = static_cast<int>(wstr_name.find('@'));
				//@�����݂��Ă���΁A@��̐������擾����
				if (pos != std::wstring::npos)
				{
					std::wstring wstr_number = wstr_name.substr(static_cast<size_t>(pos) + 1);
					//wchar�^��int�^�ɕϊ�
					levelObjData.number = std::stoi(wstr_number.c_str());
				}
				//�p�X�̍쐬
				wchar_t filePath[256];
				swprintf_s(filePath, L"Assets/modelData/%s.tkm", levelObjData.name);
				//�}���`�o�C�g�ɕϊ� wchar��char
				//�x�[�X�̕�����B
				size_t origsize = wcslen(filePath) + 1;
				//�ϊ�����������
				size_t convertedChars = 0;
				//�}���`�o�C�g�i�[�p�ϐ�
				char strCon[] = "";
				//�T�C�Y
				size_t strConSize = (strlen(strCon) + 1) * 2;
				//�ԊҌ�̃T�C�Y
				const size_t newsize = origsize * 2;
				//�A����̃T�C�Y�B
				char* cFilePath = new char[newsize + strConSize];
				//�}���`�o�C�g�ɕϊ�����(���肫��Ȃ����̂͐؂�̂Ă�)
				wcstombs_s(&convertedChars, cFilePath, newsize, filePath, _TRUNCATE);
				//�}���`�o�C�g������̘A��
				_mbscat_s((unsigned char*)cFilePath, newsize + strConSize, (unsigned char*)strCon);

				//Hook���o�^�ς݂Ȃ�΃}�b�v�`�b�v�͍쐬�s�v
				//false �̂܂܂Ȃ�쐬����B
				bool isHooked = false;
				//hookFunc�ɂȂɂ������Ă��Ȃ���Sobject�ɂ͉����Ȃ��B
				if (hookFunc != nullptr) {
					isHooked = hookFunc(levelObjData);
				}
			}
		}

		//�}�b�v�`�b�v�쐬�@�\�͖�����

	}

	void LevelRender::MatrixTklToLevel()
	{
		m_tklFile.QuaryObject([&](TklFile::SObject& tklObj) {
			//�R�s�[
			//�o�C���h�|�[�Y
			Matrix bindPoseMatrix;
			memcpy(bindPoseMatrix.m[0], &tklObj.bindPose[0], sizeof(tklObj.bindPose[0]));
			memcpy(bindPoseMatrix.m[1], &tklObj.bindPose[1], sizeof(tklObj.bindPose[1]));
			memcpy(bindPoseMatrix.m[2], &tklObj.bindPose[2], sizeof(tklObj.bindPose[2]));
			memcpy(bindPoseMatrix.m[3], &tklObj.bindPose[3], sizeof(tklObj.bindPose[3]));
			bindPoseMatrix.m[0][3] = 0.0f;
			bindPoseMatrix.m[1][3] = 0.0f;
			bindPoseMatrix.m[2][3] = 0.0f;
			bindPoseMatrix.m[3][3] = 1.0f;

			//�o�C���h�|�[�Y�̋t�s��
			//��3��vector3�ϊ��̍ۂɕs�v�Ȃ̂ŏ�����
			Matrix invBindPoseMatrix;
			memcpy(invBindPoseMatrix.m[0], &tklObj.invBindPose[0], sizeof(tklObj.invBindPose[0]));
			memcpy(invBindPoseMatrix.m[1], &tklObj.invBindPose[1], sizeof(tklObj.invBindPose[1]));
			memcpy(invBindPoseMatrix.m[2], &tklObj.invBindPose[2], sizeof(tklObj.invBindPose[2]));
			memcpy(invBindPoseMatrix.m[3], &tklObj.invBindPose[3], sizeof(tklObj.invBindPose[3]));
			invBindPoseMatrix.m[0][3] = 0.0f;
			invBindPoseMatrix.m[1][3] = 0.0f;
			invBindPoseMatrix.m[2][3] = 0.0f;
			invBindPoseMatrix.m[3][3] = 1.0f;

			wchar_t boneName[256];

			mbstowcs(boneName, tklObj.name.get(), 256);
			BonePtr bone = std::make_unique<Bone>(
				boneName,
				bindPoseMatrix,
				invBindPoseMatrix,
				tklObj.parentNo,
				tklObj.no
			);
			//�{�[���ς�
			m_boneList.push_back(std::move(bone));
			//�R�s�[�I��
		});
	}

	void LevelRender::Update()
	{

	}

	void LevelRender::Draw(RenderContext& rc)
	{

	}
}

