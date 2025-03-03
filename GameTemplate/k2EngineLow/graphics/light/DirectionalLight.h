#pragma once

namespace nsK2EngineLow {
	class DirectionalLight : Noncopyable
	{
	public:
		//コンストラクタ
		DirectionalLight();
		//デストラクタ
		~DirectionalLight();

		//方向を設定
		void SetDirection(const Vector3& direction)
		{
			m_directionLight->SetDirection(direction);
		}
		void SetDirection(float x, float y, float z)
		{
			m_directionLight->SetDirection({ x,y,z });
		}
		//方向を取得
		const Vector3& GetDirection()
		{
			return m_directionLight->GetDirection();
		}
		//方向を正規化
		void LightDirectionNormalize()
		{
			m_directionLight->LightDirectionNormalize();
		}
		//カラーを設定
		void SetColor(const Vector3& color)
		{
			m_directionLight->m_color = color;
		}
		void SetColor(float r, float g, float b)
		{
			m_directionLight->SetColor({ r,g,b });
		}
		//カラーを取得
		const Vector3& GetColor() const
		{
			return m_directionLight->GetColor();
		}
		//影をキャストするようにする
		void CastShadow()
		{
			m_directionLight->CastShadow();
		}
		//影をキャストしないようにする
		void UnCastShadow()
		{
			m_directionLight->UnCastShadow();
		}
		//ビュープロジェクションカメラ位置設定
		void VPCamSetPosition(const Vector3& pos)
		{
			m_vprCam.SetPosition(pos);
			m_directionLight->SetVPCamPosition(pos);
		}
		//ビュープロジェクションカメラ回転設定
		void VPCamSetRotation(const float& rot)
		{
			m_vprCam.SetViewAngle(Math::DegToRad(rot));
		}
		//ビュープロジェクションカメラターゲット設定
		void VPCamSetTarget(const Vector3& target)
		{
			m_vprCam.SetTarget(target);
		}
		//ビュープロジェクションカメラ上方向設定
		void VPCamSetUp(const Vector3& up)
		{
			m_vprCam.SetUp(up);
		}
		//ビュープロジェクションカメラ更新
		void VPCamUpdate()
		{
			m_vprCam.Update();

			m_directionLight->SetLightVP(m_vprCam.GetViewProjectionMatrix());
			m_directionLight->SetVPCamPosition(m_vprCam.GetPosition());
		}
	private:
		//ディレクションライトの構造体
		SDirectionLight* m_directionLight = nullptr;
		//ライトのビュープロジェクション用のカメラ
		Camera m_vprCam;
	};
}

