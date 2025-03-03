#include "k2EngineLowPreCompile.h"
#include "DirectionalLight.h"

namespace nsK2EngineLow {

	//コンストラクタ
	DirectionalLight::DirectionalLight()
	{
		if (m_directionLight == nullptr)
		{
			//ディレクションライトを作成し、ポインタを登録
			m_directionLight = g_sceneLight->NewDirectionLight();

			m_vprCam.SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);
			m_vprCam.SetWidth(2000.0f);
			m_vprCam.SetHeight(2000.0f);
			m_vprCam.SetAspectOneFlag(true);

			m_directionLight->SetLightVP(m_vprCam.GetViewProjectionMatrix());

			m_directionLight->SetVPCamPosition(m_vprCam.GetPosition());
		}
	}

	//デストラクタ
	DirectionalLight::~DirectionalLight()
	{
		g_sceneLight->DeleteDirectionLight(m_directionLight);
	}

}