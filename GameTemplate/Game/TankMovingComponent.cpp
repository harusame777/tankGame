#include "stdafx.h"
#include "TankMovingComponent.h"

namespace TankMoveConstant
{
	//誤差込み数値、小さい値の比較は誤差を考慮して「闘値以下」で判断
	static const float EQSILON = 0.001f;
	// 動いてないとみなす距離の闘値
	const float NO_MOVE_DISTANSE = 0.01f;
}

//コンストラクタ
void TankMovingComponent::InitTankMoveingData(
	Vector3& moveDirection,						//移動方向
	Vector3& forward,							//正面方向
	float& maxMoveSpeed,						//最大速度
	float& acceleration,						//加速度
	float& deceleration,						//減速
	float& friction,							//自然減速
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
	//加速度のアドレスを取得
	m_acceleration = &acceleration;
	//減速のアドレスを取得
	m_deceleration = &deceleration;
	//自然減速のアドレスを取得
	m_friction = &friction;
	//キャラクターコントローラーのアドレスを取得
	m_characterController = &characterControoler;
	//回転速度のアドレスを取得
	m_trunSpeed = &trunSpeed;
	//回転させるモデルのアドレスを取得
	m_rotModel = &rotModel;
}

//計算値を取得する
void TankMovingComponent::CalcValueAndModelUpdate()
{
	//まずは前進させるか後退させるかを判定する
	MoveDetermination();

	//回転計算
	RotateCalc();

	//移動計算
	MoveCalc();
}

//前進させるか後退させるかを判定
void TankMovingComponent::MoveDetermination()
{
	//入力方向が定数以下であれば移動しない
	if (m_moveDirection->LengthSq() < TankMoveConstant::NO_MOVE_DISTANSE)
	{
		m_moveFRModeState = EnFrontRearMoveMode::en_neutralFR;

		return;
	}

	//正面ベクトル
	Vector3 normForwardVec = *m_forward;
	normForwardVec.Normalize();
	//移動方向ベクトル
	Vector3 normMoveDirection = *m_moveDirection;
	normMoveDirection.Normalize();

	//内積を計算(クランプする)
	const float dot = btClamped(Dot(normForwardVec, normMoveDirection), -1.0f, 1.0f);
	//角度出す
	const float angle = acos(dot);

	//正面旋回境界角度
	const float forwardThreshold = DirectX::XMConvertToRadians(2.0f);
	//背面旋回境界角度
	const float backwardThreshold = DirectX::XMConvertToRadians(178.0f);

	//正面角度以下であれば前進する
	if (angle < forwardThreshold)
	{
		m_moveFRModeState = EnFrontRearMoveMode::en_moveForward;

		return;
	}
	//背面角度以上であれば後進する
	else if(angle > backwardThreshold)
	{
		m_moveFRModeState = EnFrontRearMoveMode::en_moveBackward;

		return;
	}

	//いちおうここでも設定
	m_moveFRModeState = EnFrontRearMoveMode::en_neutralFR;

	return;
}

//回転方向を判定
void TankMovingComponent::RotDetermination()
{
	//入力方向が定数以下であれば回転しない
	if (m_moveDirection->LengthSq() < TankMoveConstant::NO_MOVE_DISTANSE)
	{
		m_moveLRModeState = EnLeftRightMoveMode::en_neutralLR;

		return;
	}

	//正面ベクトル
	Vector3 normForwardVec = *m_forward;
	normForwardVec.Normalize();
	//移動方向ベクトル
	Vector3 normMoveDirection = *m_moveDirection;
	normMoveDirection.Normalize();

	//内積を計算(クランプする)
	const float dot = btClamped(Dot(normForwardVec, normMoveDirection), -1.0f, 1.0f);
	//正面差分角度を出す
	const float angleToForward = acos(dot);
	//背面差分角度を出す
	const float angleToBackward = acos(-dot);

	//正面方向に回転させるか背面方向に回転させるかを判定
	bool aimToForward = angleToForward < angleToBackward;

	//クロス積を計算してY値角度を出す
	float cross = normForwardVec.x * normMoveDirection.z - normForwardVec.z * normMoveDirection.x;

	//出した角度を使用し判定
	if (cross > 0)
	{
		//正面方向に回転するか、背面方向に回転させるかを決定
		m_moveLRModeState = aimToForward ? 
			EnLeftRightMoveMode::en_trunLeftForward : EnLeftRightMoveMode::en_trunLeftBackward;
	}
	else
	{
		//正面方向に回転するか、背面方向に回転させるかを決定
		m_moveLRModeState = aimToForward ?
			EnLeftRightMoveMode::en_trunRightForward : EnLeftRightMoveMode::en_trunRightBackward;
	}
}

//回転計算
void TankMovingComponent::RotateCalc()
{
	//回転値
	float trunCalcValue = 0.0f;
	
	//回転処理
	//switch (m_moveLRModeState)
	//{
	//case TankMovingComponent::en_neutralLR:



	//	break;
	//case TankMovingComponent::en_trunLeft:

	//	m_rotaiton.AddRotationDegY(*m_trunSpeed);

	//	break;
	//case TankMovingComponent::en_trunRight:

	//	m_rotaiton.AddRotationDegY(-*m_trunSpeed);

	//	break;
	//default:
	//	break;
	//}

	//モデルの回転更新
	m_rotModel->SetRotation(m_rotaiton);
	//正面値修正
	*m_forward = Vector3::AxisZ;
	m_rotaiton.Apply(*m_forward);
}

//移動計算
void TankMovingComponent::MoveCalc()
{
	//移動処理
	switch (m_moveFRModeState)
	{
	case TankMovingComponent::en_neutralFR:

		//自然減速処理
		if (m_moveSpeed > 0.0f)
		{
			m_moveSpeed -= *m_friction * g_gameTime->GetFrameDeltaTime();

			if (m_moveSpeed < 0.0f)
			{
				m_moveSpeed = 0.0f;
			}
		}
		else if(m_moveSpeed < 0.0f)
 		{
			m_moveSpeed += *m_friction * g_gameTime->GetFrameDeltaTime();
		}

		break;
	case TankMovingComponent::en_moveForward:

		//前進処理
		m_moveSpeed -= *m_acceleration * g_gameTime->GetFrameDeltaTime();

		break;
	case TankMovingComponent::en_moveBackward:

		//後進処理
		m_moveSpeed += *m_acceleration * g_gameTime->GetFrameDeltaTime();

		break;
	default:
		break;
	}

	//速度のクランプ
	if (m_moveSpeed > *m_maxMoveSpeed)
	{
		m_moveSpeed = *m_maxMoveSpeed;
	}
	if (m_moveSpeed < -*m_maxMoveSpeed * 0.5)
	{
		//後進は遅めに設定
		m_moveSpeed = -*m_maxMoveSpeed * 0.5;
	}

	//移動方向
	Vector3 moveDirection = *m_moveDirection;
	moveDirection.Normalize();

	//最終的な速度
	Vector3 finalMoveSpeed;
	finalMoveSpeed += moveDirection * m_moveSpeed;

	//最終的な移動座標
	Vector3 finalPosition = Vector3::AxisZ;

	//キャラコン後進
	finalPosition = m_characterController
		->Execute(finalMoveSpeed, g_gameTime->GetFrameDeltaTime());

	//モデル更新
	m_rotModel->SetPosition(finalPosition);
}