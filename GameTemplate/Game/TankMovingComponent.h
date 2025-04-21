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
	/// <param name="正面咆哮"></param>
	/// <param name="移動方向"></param>
	/// <param name="最高速度"></param>
	/// <param name="加速度"></param>
	/// <param name="減速度"></param>
	/// <param name="自然減速度"></param>
	/// <param name="動かしたい対象のキャラクターコントローラー"></param>
	TankMovingComponent(
		Vector3& forward,							//正面方向
		Vector3& moveDirection,						//移動方向
		float& moveSpeed,							//最高速度
		float& acceleration,						//加速度
		float& deceleration,						//減速
		float& friction,							//自然減速
		CharacterController& characterControoler	//キャラコン
	);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~TankMovingComponent() {};
	/// <summary>
	/// 計算値を取得する
	/// </summary>
	/// <returns></returns>
	const Vector3& GetCalcValue();
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
	Vector3* m_forward = nullptr;
	/// <summary>
	/// 移動方向
	/// </summary>
	Vector3* m_moveDirection = nullptr;
	/// <summary>
	/// 最高速度
	/// </summary>
	float* m_moveSpeed = nullptr;
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
};

