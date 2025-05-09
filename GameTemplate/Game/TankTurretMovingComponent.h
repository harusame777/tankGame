#pragma once
class TankTurretMovingComponent
{
public:
	/// <summary>
	/// 左右回転ステート
	/// </summary>
	enum EnLeftRightMoveMode
	{
		//回転しない
		en_neutralLR,
		//左回転
		en_trunLeft,
		//右回転
		en_trunRight,
	};
	/// <summary>
	/// コンストラクタ
	/// </summary>
	TankTurretMovingComponent() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~TankTurretMovingComponent() {};
	/// <summary>
	/// データセット
	/// </summary>
	/// <param name="rotDirection"></param>
	/// <param name="followPos"></param>
	/// <param name="followForward"></param>
	/// <param name="turretForward"></param>
	/// <param name="turnSpeed"></param>
	/// <param name="trunModel"></param>
	void InitTankTurretMovingData(
		Vector3& rotDirection,		//移動方向
		Vector3& followPos,			//追従させる位置
		Vector3& followForward,		//追従させるモデルの正面ベクトル
		float& turnSpeed,			//砲塔の回転スピード
		ModelRender& trunModel		//回転させるモデル
	);
	/// <summary>
	/// 計算、モデル更新
	/// </summary>
	/// <returns></returns>
	const Vector3& CalcTurretMovingDataAndModelUpdate();
	/// <summary>
	/// 砲弾発射位置を取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetCannonFiringPosition() const
	{
		return m_cannonFiringPosition;
	}
	/// <summary>
	/// 砲塔の正面ベクトルを取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetTurretForward() const
	{
		return m_forward;
	}
private:
	/// <summary>
	/// 回転方向決定
	/// </summary>
	/// <returns></returns>
	const EnLeftRightMoveMode RotDetermination();
	/// <summary>
	/// 位置計算
	/// </summary>
	/// <returns></returns>
	const Vector3& PositionUpdete();
	/// <summary>
	/// 回転更新
	/// </summary>
	void RotateUpdate();
	/// <summary>
	/// 砲弾発射位置計算
	/// </summary>
	/// <param name="turretPos"></param>
	void CalcCannonFiringPosition(const Vector3& turretForwardVec);
	/// <summary>
	/// 回転ステート
	/// </summary>
	EnLeftRightMoveMode m_moveLRModeState = EnLeftRightMoveMode::en_neutralLR;
	/// <summary>
	/// 現在回転値
	/// </summary>
	Quaternion m_rotaiton = Quaternion::Identity;
	/// <summary>
	/// 砲塔正面ベクトル
	/// </summary>
	Vector3 m_forward = Vector3::AxisZ;
	/// <summary>
	/// 砲弾発射位置
	/// </summary>
	Vector3 m_cannonFiringPosition = Vector3::Zero;
	/// <summary>
	/// 自動回転時間
	/// </summary>
	float m_autoRotTime = 0.0f;
	/// <summary>
	/// 自動回転するか
	/// </summary>
	bool m_isAutoRot = false;
	/// <summary>
	/// 回転方向
	/// </summary>
	Vector3* m_rotDirection = nullptr;
	/// <summary>
	/// 追従座標
	/// </summary>
	Vector3* m_followPosition = nullptr;
	/// <summary>
	/// 追従正面ベクトル
	/// </summary>
	Vector3* m_followForward = nullptr;
	/// <summary>
	/// 砲塔回転スピード
	/// </summary>
	float* m_trunSpeed = nullptr;
	/// <summary>
	/// 回転させるモデル
	/// </summary>
	ModelRender* m_trunModel = nullptr;
};

