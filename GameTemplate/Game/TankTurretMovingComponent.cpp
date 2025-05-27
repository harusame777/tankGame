#include "stdafx.h"
#include "TankTurretMovingComponent.h"

namespace TankTurretConstant
{
	// 動いてないとみなす距離の闘値
	const float n_noMoveDistance = 0.01f;

	const float n_cannonFiringPositionZ = 55.0;
	const float n_cannonFiringPositionY = 35.0;
}

//アドレス設定
void TankTurretMovingComponent::InitTankTurretMovingData(
	Vector3& rotDirection,		//移動方向
	Vector3& followPos,			//追従させる位置
	Vector3& followForward,		//追従させるモデルの正面ベクトル
	Vector3& crawkerMoveDirection,//履帯の移動方向	
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
	//履帯の移動方向のアドレスを取得
	m_crawlerMoveDirection = &crawkerMoveDirection;
	//砲塔の回転スピードのアドレスを取得
	m_trunSpeed = &turnSpeed;
	//回転させるモデルのアドレスを取得
	m_trunModel = &trunModel;
}

//計算、モデル更新
const Vector3& TankTurretMovingComponent::CalcTurretMovingDataAndModelUpdate()
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
	Vector3 autoRotDir = Vector3::Zero;

	//自動回転タイマー
	if (m_autoRotTime < 0.0f)
	{
		m_isAutoRot = true;

		Vector3 autoRotDirForward = *m_followForward;
		Vector3 autoRotDirBackward = *m_followForward * -1.0f;

		float dotForward = Dot(*m_crawlerMoveDirection, autoRotDirForward);
		float dotBackward = Dot(*m_crawlerMoveDirection, autoRotDirBackward);

		if (dotForward > dotBackward)
		{
				autoRotDir = autoRotDirForward;
		}
		else
		{
			autoRotDir = autoRotDirBackward;
		}
	}
	else
	{
		m_autoRotTime -= g_gameTime->GetFrameDeltaTime();
	}

	//入力方向が定数以下であれば回転しない
	if (m_rotDirection->LengthSq() < TankTurretConstant::n_noMoveDistance)
	{
		//自動回転していないなら回転しない
		if (m_isAutoRot == false)
		{
			return EnLeftRightMoveMode::en_neutralLR;
		}
	}
	else
	{
		//自動回転しないようにする
		m_autoRotTime = 5.0f;
		m_isAutoRot = false;
	}

	//正面ベクトル
	Vector3 normForwardVec = m_forward;
	normForwardVec.Normalize();
	//移動方向ベクトル
	Vector3 normMoveDirection = m_isAutoRot ? *m_followForward : *m_rotDirection;

	if (m_isAutoRot == false)
	{
		normMoveDirection = *m_rotDirection;
	}
	else
	{
		normMoveDirection = autoRotDir;
	}

	normMoveDirection.Normalize();

	normForwardVec.y = 0.0f;
	normMoveDirection.y = 0.0f;

	const float angle = acos(
		btClamped(Dot(normForwardVec, normMoveDirection), -1.0f, 1.0f));

	//一致で停止する
	if (angle < 0.1f)
	{
		m_forward = *m_rotDirection;

		return EnLeftRightMoveMode::en_neutralLR;
	}

	//クロス積を計算してY値角度を出す
	float cross = normForwardVec.x * normMoveDirection.z - normForwardVec.z * normMoveDirection.x;

	if (cross > 0.0f)
	{
		return EnLeftRightMoveMode::en_trunLeft;
	}
	else 
	{
		return EnLeftRightMoveMode::en_trunRight;
	}

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

	if (trunDir != 0.0f)
	{
		angleDelta = trunDir * *m_trunSpeed;

		m_rotaiton.AddRotationDegY(angleDelta);

	}

	//回転角から新しい正面ベクトルを更新
	m_forward = Vector3::AxisZ;
	m_rotaiton.Apply(m_forward);

	//モデルの回転更新
	m_trunModel->SetRotation(m_rotaiton);

	//砲弾発射位置計算
	CalcCannonFiringPosition(m_forward);
}

void TankTurretMovingComponent::CalcCannonFiringPosition(const Vector3& turretForwardVec)
{
	//まずは砲塔の正面ベクトルを取得
	Vector3 firingVec = turretForwardVec;
	//一応正規化
	firingVec.Normalize();
	//そこから砲塔の弾丸発射Z値と計算し正確な発射位置を計算
	const Vector3 firingPos = firingVec * TankTurretConstant::n_cannonFiringPositionZ;
	//それを現在の追従位置と計算して発射位置とする
	m_cannonFiringPosition = firingPos + *m_followPosition;
	//Y値を修正
	m_cannonFiringPosition.y += TankTurretConstant::n_cannonFiringPositionY;
}

bool TankTurretMovingComponent::IsTurretForwardToAPosSameAngle(const Vector3& aPos)
{
	//引数の位置と追従位置のベクトルを計算
	Vector3 turretToAPosVec = aPos - *m_followPosition;
	//砲塔の正面ベクトルを取得
	Vector3 turretForwardVec = m_forward;
	turretForwardVec.Normalize();
	//引数のベクトルを正規化
	Vector3 aVecNorm = turretToAPosVec;
	aVecNorm.Normalize();
	//角度を計算
	const float angle = acos(
		btClamped(Dot(turretForwardVec, aVecNorm), -1.0f, 1.0f));
	//角度が一定以下ならtrue
	return angle < 0.1f;
}