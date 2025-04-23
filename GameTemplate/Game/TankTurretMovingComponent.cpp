#include "stdafx.h"
#include "TankTurretMovingComponent.h"

namespace TankTurretConstant
{
	//誤差込み数値、小さい値の比較は誤差を考慮して「闘値以下」で判断
	static const float EQSILON = 0.001f;
	// 動いてないとみなす距離の闘値
	const float NO_MOVE_DISTANSE = 0.01f;
}

//アドレス設定
void TankTurretMovingComponent::InitTankTurretMovingData(
	Vector3& rotDirection,		//移動方向
	Vector3& followPos,			//追従させる位置
	Vector3& followForward,		//追従させるモデルの正面ベクトル
	Vector3& turretForward,		//砲塔の正面ベクトル
	float& turnSpeed,			//砲塔の回転スピード
	ModelRender& trunModel		//回転させるモデル
)
{
	//回転方向のアドレスを取得
	m_rotDirection = &rotDirection,
	//追従させる位置のアドレスを取得
	m_followPosition = &followPos;
	//追従させるモデルの正面ベクトルのアドレスを取得
	m_followForward = &followForward;
	//砲塔の正面ベクトルのアドレスを取得
	m_turretForward = &turretForward;
	//砲塔の回転スピードのアドレスを取得
	m_trunSpeed = &turnSpeed;
	//回転させるモデルのアドレスを取得
	m_trunModel = &trunModel;
}

//計算、モデル更新
const Vector3& TankTurretMovingComponent::CalcValueAndModelUpdate()
{
	//最終的な位置
	Vector3 finalPosition = Vector3::Zero;

	//回転方向を決定する
	m_moveLRModeState = RotDetermination();

	finalPosition = PositionUpdete();

	//回転更新
	RotateUpdate();

	return finalPosition;
}

//回転方向決定関数
const TankTurretMovingComponent::EnLeftRightMoveMode TankTurretMovingComponent::RotDetermination()
{
	//入力方向が定数以下であれば回転しない
	if (m_rotDirection->LengthSq() < TankTurretConstant::NO_MOVE_DISTANSE)
	{
		return EnLeftRightMoveMode::en_neutralLR;
	}

	//正面ベクトル
	Vector3 normForwardVec = *m_followForward;
	normForwardVec.Normalize();
	//移動方向ベクトル
	Vector3 normMoveDirection = *m_rotDirection;
	normMoveDirection.Normalize();

	//クロス積を計算してY値角度を出す
	float cross = normForwardVec.x * normMoveDirection.z - normForwardVec.z * normMoveDirection.x;

	if (cross > 0.1f)
	{
		return EnLeftRightMoveMode::en_trunLeft;
	}
	else if(cross < -0.1f)
	{
		return EnLeftRightMoveMode::en_trunRight;
	}

	return EnLeftRightMoveMode::en_neutralLR;
}

const Vector3& TankTurretMovingComponent::PositionUpdete()
{
	//位置更新
	m_trunModel->SetPosition(*m_followPosition);

	return *m_followPosition;
}

void TankTurretMovingComponent::RotateUpdate()
{
	//回転方向
	float trunDir = 0.0f;
	//角度
	float angleDelta = 0.0f;

	switch (m_moveLRModeState)
	{
	case TankTurretMovingComponent::en_neutralLR:
		break;
	case TankTurretMovingComponent::en_trunLeft:

		trunDir = -1.0f;

		break;
	case TankTurretMovingComponent::en_trunRight:

		trunDir = 1.0f;

		break;
	default:
		break;
	}

	Quaternion rotCalcQua;
	rotCalcQua.AddRotationY(180.0f);
	const float rotationCalcY = rotCalcQua.y;

	if (trunDir != 0.0f)
	{
		angleDelta = trunDir * rotationCalcY * *m_trunSpeed;

		m_rotaiton.AddRotationDegY(angleDelta);

		//回転角から新しい正面ベクトルを更新
		m_forward = Vector3::AxisZ;
		m_rotaiton.Apply(m_forward);
	}

	//モデルの回転更新
	m_trunModel->SetRotation(m_rotaiton);
}