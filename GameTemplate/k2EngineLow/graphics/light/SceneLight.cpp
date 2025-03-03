#include "k2EngineLowPreCompile.h"
#include "SceneLight.h"

namespace nsK2EngineLow {

	//コンストラクタ
	SceneLight::SceneLight()
	{

	}

	//デストラクタ
	SceneLight::~SceneLight()
	{
		
	}

	void SceneLight::Init()
	{
		//太陽光
		//m_light.m_directionalLight[0].m_color.x = 1.0f;
		//m_light.m_directionalLight[0].m_color.y = 1.0f;
		//m_light.m_directionalLight[0].m_color.z = 1.0f;

		//m_light.m_directionalLight[0].m_direction.x = 1.0f;
		//m_light.m_directionalLight[0].m_direction.y = -1.0f;
		//m_light.m_directionalLight[0].m_direction.z = -1.0f;
		//m_light.m_directionalLight[0].m_direction.Normalize();
		//m_light.m_directionalLight[0].m_castShadow = true;

		m_light.m_ambientLight.x = 0.3f;
		m_light.m_ambientLight.y = 0.3f;
		m_light.m_ambientLight.z = 0.3f;
		m_light.m_eyePos = g_camera3D->GetPosition();

		//全てのディレクションライトを未使用にする
		for (auto& pt : m_light.m_directionalLight)
		{
			pt.UnUse();
		}
		m_light.m_numDirectionLight = 0;

		//全てのポイントライトを未使用にする
		for (auto& pt : m_light.m_pointLights) {
			pt.UnUse();
			pt.SetAffectPowParam(1.0f);
		}
		m_light.m_numPointLight = 0;

		//全てのスポットライトを未使用にする
		for (auto& pt : m_light.m_spotLights){
			pt.UnUse();
		}
		m_light.m_numSpotLight = 0;
	}

	void SceneLight::Update()
	{
		m_light.m_numDirectionLight = 0;
		for (int i = 0; i < MAX_DIRECTIONAL_LIGHT; i++)
		{
			if (m_light.m_directionalLight[i].GetUse())
			{
				m_light.m_numDirectionLight++;
			}
		}

		m_light.m_numPointLight = 0;
		for (int i = 0; i < MAX_POINT_LIGHT; i++)
		{
			if (m_light.m_pointLights[i].GetUse())
			{
				m_light.m_numPointLight++;
			}
		}

		m_light.m_numSpotLight = 0;
		for (int i = 0; i < MAX_SPOT_LIGHT; i++)
		{
			if (m_light.m_spotLights[i].GetUse())
			{
				m_light.m_numSpotLight++;
			}
		}
	}

	//新規ディレクションライトを作成
	SDirectionLight* SceneLight::NewDirectionLight()
	{
		if (m_light.m_numDirectionLight)
		{
			return nullptr;
		}

		for (int i = 0; i < MAX_DIRECTIONAL_LIGHT; i++)
		{
			if (m_light.m_directionalLight[i].m_isUse != true)
			{
				m_light.m_directionalLight[i].Use();
				return &m_light.m_directionalLight[i];
			}
		}
	}

	void SceneLight::DeleteDirectionLight(SDirectionLight* directionlight)
	{
		//ポインタにアドレスが何も入ってなかったら何もせずに返す
		if (directionlight == nullptr)
		{
			return;
		}
		//万が一シーンライトが管理していないディレクションライトに対して削除処理を実行すると管理がバグる(特に使用中のライトの数)ので
		//本当に削除処理をしていいか確認する 
		//送られてきたポインタに入っているアドレスと、配列の各要素のアドレスを照らし合わせて、
		//アドレスが同じものを見つけたら、削除処理を実行する
		for (int i = 0; i < MAX_DIRECTIONAL_LIGHT; i++)
		{
			if (directionlight == &m_light.m_directionalLight[i])
			{
				//初期化
				directionlight->UnUse();
				directionlight->SetColor(0.0f, 0.0f, 0.0f);
				directionlight->SetDirection(0.0f, 0.0f, 0.0f);
			}
		}
	}

	//新規ポイントライトを作成
	SPointLight* SceneLight::NewPointLight()
	{
		if (m_light.m_numPointLight >= MAX_POINT_LIGHT)
		{
			return nullptr;
		}

		for (int i = 0; i < MAX_POINT_LIGHT; i++)
		{
			if (m_light.m_pointLights[i].GetUse() != true)
			{
				m_light.m_pointLights[i].Use();
				return &m_light.m_pointLights[i];
			}
		}
	}

	//ポイントライトを削除
	void SceneLight::DeletePointLight(SPointLight* m_pointlight)
	{
		//ポインタにアドレスが入ってなかったら何もせず返す
		if (m_pointlight == nullptr)
		{
			return;
		}
		//万が一シーンライトが管理していないポイントライトに対して削除処理を実行すると管理がバグる(特に使用中のライトの数)ので
		//本当に削除処理をしていいか確認する 
		//送られてきたポインタに入っているアドレスと、配列の各要素のアドレスを照らし合わせて、
		//アドレスが同じものを見つけたら、削除処理を実行する
		for (int i = 0; i < MAX_POINT_LIGHT; i++)
		{

			if (m_pointlight == &m_light.m_pointLights[i])
			{
				//初期化
				m_pointlight->UnUse();
				m_pointlight->SetColor(0.0f, 0.0f, 0.0f);
				m_pointlight->SetPosition(0.0f, 0.0f, 0.0f);
				m_pointlight->SetRange(0.0f);
				m_pointlight->SetAffectPowParam(1.0f);
			}
		}
	}

	//新規スポットライトを作成
	SSpotLight* SceneLight::NewSpotLight()
	{
		if (m_light.m_numSpotLight >= MAX_SPOT_LIGHT)
		{
			return nullptr;
		}

		for (int i = 0; i < MAX_SPOT_LIGHT; i++)
		{
			if (m_light.m_spotLights[i].GetUse() != true)
			{
				m_light.m_spotLights[i].Use();
				return &m_light.m_spotLights[i];
			}
		}
	}

	//スポットライトを削除
	void SceneLight::DeleteSpotLight(SSpotLight* spotlight)
	{
		if (spotlight == nullptr)
		{
			return;
		}

		for (int i = 0; i < MAX_SPOT_LIGHT; i++)
		{

			if (spotlight == &m_light.m_spotLights[i])
			{
				spotlight->UnUse();
				spotlight->SetColor(0.0f, 0.0f, 0.0f);
				spotlight->SetPosition(0.0f, 0.0f, 0.0f);
				spotlight->SetRange(0.0f);
				spotlight->SetRangeAffectPowParam(1.0f);
				spotlight->SetAngleAffectPowParam(1.0f);
			}
		}
	}
}