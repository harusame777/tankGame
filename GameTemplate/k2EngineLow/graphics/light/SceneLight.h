#pragma once

namespace nsK2EngineLow {

	static const int MAX_DIRECTIONAL_LIGHT = 4;
	static const int MAX_POINT_LIGHT = 32;
	static const int MAX_SPOT_LIGHT = 32;

	//ディレクションライトの構造体
	struct SDirectionLight
	{
		//ライトの方向
		Vector3 m_direction;
		//影をキャストするかしないか
		int m_castShadow = true;
		//カラー
		Vector3 m_color;
		//使用されいているかどうか
		int m_isUse = false;
		//ライトのビュープロジェクション
		Matrix m_mt;
		//ビュープロジェクションカメラのポジション
		Vector3 m_vPCamPosition;
	public:
		//方向を設定
		void SetDirection(const Vector3& direction)
		{
			m_direction = direction;
		}
		void SetDirection(float x, float y, float z)
		{
			SetDirection({ x,y,z });
		}
		//方向を取得
		const Vector3& GetDirection()
		{
			return m_direction;
		}
		//方向を正規化
		void LightDirectionNormalize()
		{
			m_direction.Normalize();
		}
		//カラーを設定
		void SetColor(const Vector3& color)
		{
			this->m_color = color;
		}
		void SetColor(float r, float g, float b)
		{
			SetColor({ r,g,b });
		}
		//カラーを取得
		const Vector3& GetColor() const
		{
			return this->m_color;
		}
		//影をキャストするようにする
		void CastShadow()
		{
			m_castShadow = true;
		}
		//影をキャストしないようにする
		void UnCastShadow()
		{
			m_castShadow = false;
		}
		//ディレクションライトを使用中にする
		//エンジンで使用するための関数なのでゲーム側から呼び出さないよう注意
		void Use()
		{
			m_isUse = true;
		}
		//ディレクションライトを未使用にする
		//エンジンで使用するための関数なのでゲーム側から呼び出さないよう注意
		void UnUse()
		{
			m_isUse = false;
		}
		//ディレクションライトが使用中か調べる
		const int GetUse() const
		{
			return m_isUse;
		}
		//ライトのビュープロジェクションを登録
		void SetLightVP(const Matrix& vp)
		{
			m_mt = vp;
		}
		//ライトのビュープロジェクションを取得
		const Matrix& GetLightVP() const
		{
			return m_mt;
		}
		/// <summary>
		/// ビュープロジェクションカメラの位置設定
		/// </summary>
		/// <param name="vPCamPos"></param>
		void SetVPCamPosition(const Vector3& vPCamPos)
		{
			m_vPCamPosition = vPCamPos;
		}
		/// <summary>
		/// ビュープロジェクションカメラの位置取得
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
		//座標を設定
		void SetPosition(const Vector3& position)
		{
			this->m_position = position;
		}
		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x,y,z });
		}
		//座標を取得
		const Vector3& GetPosition()
		{
			return this->m_position;
		}
		//カラーを設定
		void SetColor(const Vector3& color)
		{
			this->m_color = color;
		}
		void SetColor(float r, float g, float b)
		{
			SetColor({ r,g,b });
		}
		//カラーを取得
		const Vector3& GetColor() const
		{
			return this->m_color;
		}
		//影響範囲を設定
		void SetRange(float range)
		{
			attn.x = range;
		}
		//影響範囲を取得
		float GetRange() const
		{
			return attn.x;
		}
		//影響率の累乗数
		void SetAffectPowParam(float powParam)
		{
			attn.y = powParam;
		}
		//ポイントライトを使用中にする
		//エンジンで使用するための関数なのでゲーム側から呼び出さないよう注意
		void Use()
		{
			m_isUse = true;
		}
		//ポイントライトを未使用にする
		//エンジンで使用するための関数なのでゲーム側から呼び出さないよう注意
		void UnUse()
		{
			m_isUse = false;
		}
		//ポイントライトが使用中か調べる
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
		//座標を設定
		void SetPosition(const Vector3& position)
		{
			this->m_position = position;
		}
		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x,y,z });
		}
		//座標を取得
		const Vector3& GetPosition()
		{
			return this->m_position;
		}
		//カラーを設定
		void SetColor(const Vector3& color)
		{
			this->m_color = color;
		}
		void SetColor(float r, float g, float b)
		{
			SetColor({ r,g,b });
		}
		//カラーを取得
		const Vector3& GetColor() const
		{
			return this->m_color;
		}
		//射出方向を設定
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
		//射出方向を取得
		const Vector3& GetDirection() const
		{
			return m_direction;
		}
		//射出角度を設定
		void SetAngle(const float angle)
		{
			m_angle = angle;
		}
		//射出角度を取得
		const float GetAngle() const
		{
			return m_angle;
		}
		//影響範囲を設定
		void SetRange(const float range)
		{
			m_range = range;
		}
		//影響範囲を取得
		const float GetRange() const
		{
			return m_range;
		}
		//光の距離による影響率に累乗する値を設定
		void SetRangeAffectPowParam(const float powParam)
		{
			m_pow.x = powParam;
		}
		//光の角度による影響率に累乗する値を設定
		void SetAngleAffectPowParam(const float powParam)
		{
			m_pow.y = powParam;
		}
		//スポットライトを使用中にする
		//エンジンで使用するための関数なのでゲーム側から呼び出さないよう注意
		void Use()
		{
			m_isUse = true;
		}
		//スポットライトを未使用にする
		//エンジンで使用するための関数なのでゲーム側から呼び出さないよう注意
		void UnUse()
		{
			m_isUse = false;
		}
		//スポットライトが使用中か調べる
		const int GetUse() const
		{
			return m_isUse;
		}
	};

	struct Light
	{
		//ディレクションライトの配列
		SDirectionLight m_directionalLight[MAX_DIRECTIONAL_LIGHT];
		//ポイントライトの配列
		SPointLight m_pointLights[MAX_POINT_LIGHT];
		//スポットライトの配列
		SSpotLight m_spotLights[MAX_SPOT_LIGHT];
		//視点の位置
		Vector3 m_eyePos;
		//使用中のポイントライトの数
		int m_numPointLight;
		//環境光
		Vector3 m_ambientLight;
		//使用中のスポットライトの数
		int m_numSpotLight;
		Vector3 pad;
		//使用中のディレクションライトの数
		int m_numDirectionLight;
		//ディレクションライトのビュープロジェクション
	};

	//シーンライトクラス
	class SceneLight : public Noncopyable
	{
	public:
		//コンストラクタ
		SceneLight();
		//デストラクタ
		~SceneLight();

		//初期化
		void Init();

		//シーンライトを取得
		Light& GetSceneLight()
		{
			return m_light;
		}

		//影をキャストするか
		bool IsCastShadow(int ligNo)
		{
			return m_light.m_directionalLight[ligNo].m_castShadow;
		}

		//環境光を設定
		void SetAmbient(Vector3 ambient)
		{
			m_light.m_ambientLight = ambient;
		}

		//更新処理
		void Update();

		//ディレクションライト配列から未使用のライトのポインタを提供
		SDirectionLight* NewDirectionLight();

		//使用中のディレクションライトを削除(アドレス照合)
		void DeleteDirectionLight(SDirectionLight* directionlight);

		//ポイントライト配列から未使用のライトのポインタを提供
		SPointLight* NewPointLight();

		//使用中のポイントライトを削除(アドレス照合)
		void DeletePointLight(SPointLight* pointlight);

		//スポットライト配列から未使用のライトのポインタを提供
		SSpotLight* NewSpotLight();

		//使用中のスポットライトを削除
		void DeleteSpotLight(SSpotLight* spotlight);
		
		//ライトのデータを取得
		Light* GetLightData()
		{
			return &m_light;
		}

		//シーンライト
		Light m_light;
	};
}

