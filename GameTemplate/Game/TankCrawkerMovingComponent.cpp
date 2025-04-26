#include "stdafx.h"
#include "TankCrawkerMovingComponent.h"

namespace TankTurretConstant
{
	//誤差込み数値、小さい値の比較は誤差を考慮して「闘値以下」で判断
	static const float EQSILON = 0.001f;
	// 動いてないとみなす距離の闘値
	const float NO_MOVE_DISTANSE = 0.01f;
}

//コンストラクタ
void TankCrawkerMovingComponent::InitTankCrawkerMoveingData(
	Vector3& moveDirection,						//移動方向
	Vector3& forward,							//正面方向
	float& maxMoveSpeed,						//最大速度
	CharacterController& characterControoler,	//キャラコン
	float& trunSpeed,							//回転速度
	ModelRender& rotModel						//回転させるモデル
)
{
	//移動方向のアドレスを取得
	m_moveDirection = &moveDirection;
	//正面方向のアドレスを取得
	m_forward = &forward;
	//最大速度のアドレスを取得
	m_maxMoveSpeed = &maxMoveSpeed;
	//キャラクターコントローラーのアドレスを取得
	m_characterController = &characterControoler;
	//回転速度のアドレスを取得
	m_trunSpeed = &trunSpeed;
	//回転させるモデルのアドレスを取得
	m_rotModel = &rotModel;
}

//計算値を取得する
const Vector3& TankCrawkerMovingComponent::CalcCrawkerMovingDataAndModelUpdate()
{
	//最終的な位置座標
	Vector3 finalPosition = Vector3::Zero; 

	//回転方向を判定する
	m_moveLRModeState = RotDetermination();

	//まずは前進させるか後退させるかを判定する
	m_moveFRModeState = MoveDetermination();

	//回転計算
	RotateCalc();

	//移動計算
	MoveCalc();

	return m_modelPosition;
}

//前進させるか後退させるかを判定
const TankCrawkerMovingComponent::EnFrontRearMoveMode TankCrawkerMovingComponent::MoveDetermination()
{
	//入力方向が定数以下であれば移動しない
	if (m_moveDirection->LengthSq() < TankTurretConstant::NO_MOVE_DISTANSE)
	{
		return EnFrontRearMoveMode::en_neutralFR;
	}

	//正面ベクトル
	Vector3 normForwardVec = *m_forward;
	normForwardVec.Normalize();
	//移動方向ベクトル
	Vector3 normMoveDirection = *m_moveDirection;
	normMoveDirection.Normalize();

	//内積を計算(クランプする)
	const float dot = btClamped(Dot(normForwardVec, normMoveDirection), -1.0f, 1.0f);

	const float forwardThershold = cosf(DirectX::XMConvertToRadians(65.0f));

	//正面角度以下であれば前進する
	if (dot > forwardThershold)
	{
		return EnFrontRearMoveMode::en_moveForward;
	}
	//背面角度以上であれば後進する
	else if(dot < -forwardThershold)
	{
		return EnFrontRearMoveMode::en_moveBackward;
	}

	//いちおうここでも設定
	return EnFrontRearMoveMode::en_neutralFR;
}

//回転方向を判定
const TankCrawkerMovingComponent::EnLeftRightMoveMode TankCrawkerMovingComponent::RotDetermination()
{
	//入力方向が定数以下であれば回転しない
	if (m_moveDirection->LengthSq() < TankTurretConstant::NO_MOVE_DISTANSE)
	{
		return EnLeftRightMoveMode::en_neutralLR;
	}

	//正面ベクトル
	Vector3 normForwardVec = *m_forward;
	normForwardVec.Normalize();
	//移動方向ベクトル
	Vector3 normMoveDirection = *m_moveDirection;
	normMoveDirection.Normalize();

	//正面差分角度を出す
	const float angleToForward = acos(
		btClamped(Dot(normForwardVec, normMoveDirection), -1.0f, 1.0f));
	//背面差分角度を出す
	const float angleToBackward = acos(
		btClamped(Dot((normForwardVec * -1.0f), normMoveDirection), -1.0f, 1.0f));

	//正面方向に回転させるか背面方向に回転させるかを判定
	bool aimToForward = angleToForward < angleToBackward;

	if (aimToForward == true)
	{
		if (angleToForward < 0.1f)
		{
			return EnLeftRightMoveMode::en_neutralLR;
		}
	}
	else
	{
		if (angleToBackward < 0.1f)
		{
			return EnLeftRightMoveMode::en_neutralLR;
		}
	}

	//正面方向回転か、背面方向回転かでクロス積の計算方法を変更する
	Vector3 dirCalcVec = aimToForward ? normForwardVec : (normForwardVec * -1.0f);

	//クロス積を計算してY値角度を出す
	float cross = dirCalcVec.x * normMoveDirection.z - dirCalcVec.z * normMoveDirection.x;

	//出した角度を使用し判定
	if (cross > 0.0f)
	{
		//左にズレがある
		return aimToForward ?
			EnLeftRightMoveMode::en_trunLeftForward : EnLeftRightMoveMode::en_trunLeftBackward;
	}
	else
	{
		//左にズレがある
		return aimToForward ?
			EnLeftRightMoveMode::en_trunRightForward : EnLeftRightMoveMode::en_trunRightBackward;
	}
}

//回転計算
void TankCrawkerMovingComponent::RotateCalc()
{
	//回転方向
	float trunDir = 0.0f;
	//角度
	float angleDelta = 0.0f;

	switch (m_moveLRModeState)
	{
	case TankCrawkerMovingComponent::en_neutralLR:
		break;
	case TankCrawkerMovingComponent::en_trunLeftForward:
	case TankCrawkerMovingComponent::en_trunLeftBackward:

		trunDir = -1.0f;

		break;
	case TankCrawkerMovingComponent::en_trunRightForward:
	case TankCrawkerMovingComponent::en_trunRightBackward:

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
	*m_forward = Vector3::AxisZ;
	m_rotaiton.Apply(*m_forward);

	//モデルの回転更新
	m_rotModel->SetRotation(m_rotaiton);
}

//移動計算
void TankCrawkerMovingComponent::MoveCalc()
{
	//移動方向
	Vector3 moveDirection = Vector3::Zero;
	//最終的な速度
	Vector3 finalMoveSpeed;
	
	//移動処理
	switch (m_moveFRModeState)
	{
	case TankCrawkerMovingComponent::en_neutralFR:
		break;
	case TankCrawkerMovingComponent::en_moveForward:

		moveDirection = *m_forward;

		moveDirection.Normalize();

		finalMoveSpeed += moveDirection * *m_maxMoveSpeed;

		break;
	case TankCrawkerMovingComponent::en_moveBackward:

		moveDirection = (*m_forward * 1.0f);

		moveDirection.Normalize();

		finalMoveSpeed += moveDirection * -*m_maxMoveSpeed;

		break;
	default:
		break;
	}

	//キャラコン後進
	m_modelPosition = m_characterController
		->Execute(finalMoveSpeed, g_gameTime->GetFrameDeltaTime());

	//モデル更新
	m_rotModel->SetPosition(m_modelPosition);
}