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
	//まずは前進させるか回転させるかを判定する
	RotAndMoveDetermination();

	//回転計算
	RotateCalc();

	//移動計算
	MoveCalc();
}

//どう移動させるかどう回転させるかを判定
void TankMovingComponent::RotAndMoveDetermination()
{
	//正面値
	Vector3 forward = m_forward;
	//移動先方向
	Vector3 moveDirection = *m_moveDirection;

	//水平方向で考えるためY値をゼロにする
	forward.y = 0.0f;
	moveDirection.y = 0.0f;

	//移動方向の2乗の数値を計算
	const float distanceSq = moveDirection.LengthSq();

	//正面値と移動方向のベクトルを単位ベクトルにする
	forward.Normalize();
	moveDirection.Normalize();

	//前進回転闘値計算
	Quaternion rotCalc;
	rotCalc.AddRotationDegZ(10.0f);
	const float forwardThreshold = rotCalc.z;

	//後進回転闘値計算
	rotCalc.AddRotationDegZ(20.0f);
	const float backwardThreshold = rotCalc.z;

	//正面値と移動方向の内積を計算し、角度を求める
	const float dot = Dot(forward, moveDirection);

	//外積を使い左に回転するか右に回転するかを判定
	const Vector3 cross = Cross(forward, moveDirection);

	//ここから移動判定
	if (distanceSq < TankMoveConstant::NO_MOVE_DISTANSE)
	{
		//移動していない
		m_moveFRModeState = EnFrontRearMoveMode::en_neutral;
	}
	else if (dot >= cosf(forwardThreshold))
	{
		//正面に移動できる
		m_moveFRModeState = EnFrontRearMoveMode::en_moveForward;
	}
	else if(dot <= -cosf(backwardThreshold))
	{
		//後方に移動できる
		m_moveFRModeState = EnFrontRearMoveMode::en_moveBackward;
	}

	//ここから回転判定
	if (fabsf(cross.y < TankMoveConstant::EQSILON))
	{
		//左右にずれてないので回転しない
		m_moveLRModeState = EnLeftRightMoveMode::en_neutral;
	}
	else if (cross.y > 0.0f)
	{
		//左に回転
		m_moveLRModeState = EnLeftRightMoveMode::en_trunLeft;
	}
	else
	{
		//右に回転
		m_moveLRModeState = EnLeftRightMoveMode::en_trunRight;
	}
}

//回転計算
void TankMovingComponent::RotateCalc()
{
	//回転処理
	switch (m_moveLRModeState)
	{
	case TankMovingComponent::en_neutral:

		return;
		break;
	case TankMovingComponent::en_trunLeft:

		m_rotationY -= *m_trunSpeed * g_gameTime->GetFrameDeltaTime();

		break;
	case TankMovingComponent::en_trunRight:

		m_rotationY += *m_trunSpeed * g_gameTime->GetFrameDeltaTime();

		break;
	default:
		break;
	}

	//回転値
	Quaternion rot;
	rot.SetRotationDegY(m_rotationY);

	//モデルの回転更新
	m_rotModel->SetRotation(rot);
	//正面値修正
	m_forward = Vector3::AxisZ;
	rot.Apply(m_forward);
}

//移動計算
void TankMovingComponent::MoveCalc()
{
	//移動処理
	switch (m_moveFRModeState)
	{
	case TankMovingComponent::en_neutral:

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
		m_moveSpeed += *m_acceleration * g_gameTime->GetFrameDeltaTime();

		break;
	case TankMovingComponent::en_moveBackward:

		//後進処理
		m_moveSpeed -= *m_acceleration * g_gameTime->GetFrameDeltaTime();

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

	//キャラコン後進
	m_characterController->Execute(finalMoveSpeed, g_gameTime->GetFrameDeltaTime());
}