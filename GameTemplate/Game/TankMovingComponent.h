#pragma once
class TankMovingComponent
{
public:
	/// <summary>
	/// 正面、後方移動ステート
	/// </summary>
	enum EnFrontRearMoveMode
	{
		//移動しない
		en_neutral,
		//正面に移動
		en_moveForward,
		//後方に移動
		en_moveBackward,
	};
	/// <summary>
	/// 左右回転ステート
	/// </summary>
	enum EnLeftRightMoveMode
	{
		//移動しない
		en_neutral,
		//左に回転
		en_trunLeft,
		//右に回転
		en_trunRight
	};
	/// <summary>
	/// コンストラクタ
	/// </summary>
	TankMovingComponent() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~TankMovingComponent() {};
	/// <summary>
	/// 戦車移動初期化
	/// </summary>
	/// <param name="moveDirection"></param>
	/// <param name="acceleration"></param>
	/// <param name="deceleration"></param>
	/// <param name="friction"></param>
	/// <param name="characterControoler"></param>
	/// <param name="trunSpeed"></param>
	/// <param name="rotModel"></param>
	void InitTankMoveingData(
		Vector3& moveDirection,						//移動方向
		float& maxMoveSpeed,						//最大速度
		float& acceleration,						//加速度
		float& deceleration,						//減速
		float& friction,							//自然減速
		CharacterController& characterControoler,	//キャラコン
		float& trunSpeed,							//回転速度
		ModelRender& rotModel						//回転させるモデル
	);
	/// <summary>
	/// 計算とモデル更新を行う
	/// </summary>
	/// <returns></returns>
	void CalcValueAndModelUpdate();
	/// <summary>
	/// 現在速度を返す
	/// </summary>
	/// <returns></returns>
	const float GetMoveSpeed()const
	{
		return m_moveSpeed;
	}
	/// <summary>
	/// 現在回転角度(Y)を返す
	/// </summary>
	/// <returns></returns>
	const float GetRotationY()const
	{
		return m_rotationY;
	}
	/// <summary>
	/// 現在正面方向を返す
	/// </summary>
	/// <returns></returns>
	const Vector3& GetForward()const
	{
		return m_forward;
	}
private:
	/// <summary>
	/// どう回転するか、どう移動するかの判定
	/// </summary>
	void RotAndMoveDetermination();
	/// <summary>
	/// 移動計算
	/// </summary>
	void MoveCalc();
	/// <summary>
	/// 回転計算
	/// </summary>
	void RotateCalc();
	/// <summary>
	/// 正面、後方移動ステート
	/// </summary>
	EnFrontRearMoveMode m_moveFRModeState = EnFrontRearMoveMode::en_neutral;
	/// <summary>
	/// 左右回転ステート
	/// </summary>
	EnLeftRightMoveMode m_moveLRModeState = EnLeftRightMoveMode::en_neutral;
	/// <summary>
	/// 正面方向
	/// </summary>
	Vector3 m_forward = Vector3::AxisZ;
	/// <summary>
	/// 現在速度
	/// </summary>
	float m_moveSpeed = 0.0f;
	/// <summary>
	/// 現在回転角度
	/// </summary>
	float m_rotationY = 0.0f;
	/// <summary>
	/// 移動方向
	/// </summary>
	Vector3* m_moveDirection = nullptr;
	/// <summary>
	/// 最大速度
	/// </summary>
	float* m_maxMoveSpeed = nullptr;
	/// <summary>
	/// 加速度
	/// </summary>
	float* m_acceleration = nullptr;
	/// <summary>
	/// 減速度
	/// </summary>
	float* m_deceleration = nullptr;
	/// <summary>
	/// 自然減速
	/// </summary>
	float* m_friction = nullptr;
	/// <summary>
	/// キャラクターコントローラー
	/// </summary>
	CharacterController* m_characterController = nullptr;
	/// <summary>
	/// 回転速度
	/// </summary>
	float* m_trunSpeed = nullptr;
	/// <summary>
	/// 回転させるモデル
	/// </summary>
	ModelRender* m_rotModel = nullptr;
};

