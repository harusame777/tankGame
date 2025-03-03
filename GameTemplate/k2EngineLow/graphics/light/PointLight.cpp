#include "k2EngineLowPreCompile.h"
#include "PointLight.h"

namespace nsK2EngineLow {

	//コンストラクタ
	PointLight::PointLight()
	{
		if (m_pointLight == nullptr)
		{
			//ポイントライトを作成し、ポインタを登録
			m_pointLight = g_sceneLight->NewPointLight();
		}
	}

	//デストラクタ
	PointLight::~PointLight()
	{
		g_sceneLight->DeletePointLight(m_pointLight);
	}

}