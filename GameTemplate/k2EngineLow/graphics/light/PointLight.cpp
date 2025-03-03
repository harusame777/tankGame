#include "k2EngineLowPreCompile.h"
#include "PointLight.h"

namespace nsK2EngineLow {

	//�R���X�g���N�^
	PointLight::PointLight()
	{
		if (m_pointLight == nullptr)
		{
			//�|�C���g���C�g���쐬���A�|�C���^��o�^
			m_pointLight = g_sceneLight->NewPointLight();
		}
	}

	//�f�X�g���N�^
	PointLight::~PointLight()
	{
		g_sceneLight->DeletePointLight(m_pointLight);
	}

}