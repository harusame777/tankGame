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
	//移動していない状態で一旦初期化
	m_moveFRModeState = EnFrontRearMoveMode::en_neutralFR;
	//回転していない状態で一旦初期化
	m_moveLRModeState = EnLeftRightMoveMode::en_neutralLR;
	
	//移動方向の入力があるかどうかを判定
	if (m_moveDirection->LengthSq() < 0.01f)
	{
		//どちらも入力無しで決定
		return;
	}

	//移動方向のZ値の境界数値
	const float minZThreshold = 0.05f;
	//横方向と前後方向の比率がこの数値以下で前進のみの扱いとする
	const float straightThreshold = 0.1f;
	//横方向と前後方向の比率がこの数値未満でカーブ、以上で旋回とする
	const float curveThreshold = 0.5f;

	//ここから絶対値取得
	//左右入力の強さを計算
	float absX = fabsf(m_moveDirection->x);
	//前後入力の強さを計算
	float absZ = fabsf(m_moveDirection->z);

	//ここから判定
	//まずは回転判定
	
	//absZ < minZThresholdの比較
	//真で前にも後ろにもほとんど動いていない、旋回をすると判断
	//absX / absZ > straightThresholdの計算、比較
	//(横移動の強さ ÷ 前後移動の強さ)がある程度大きい場合であれば横向きに近い入力と判断
	if (absZ < minZThreshold || (absZ / absX) > straightThreshold)
	{
		//m_moveDirection->x > 0.0fであれば右回転、小さければ左回転
		m_moveLRModeState = (m_moveDirection->x > 0.0f) 
			? EnLeftRightMoveMode::en_trunRight : EnLeftRightMoveMode::en_trunLeft;
	}

	//次に前進後退を判定
	//z値が小さくなければ前進するか後退すると判定
	if (absZ >= minZThreshold)
	{
		//m_moveDirection->z > 0.0fであれば前進判定、小さければ後退判定
		m_moveFRModeState = (m_moveDirection->z > 0.0f) 
			? EnFrontRearMoveMode::en_moveForward : EnFrontRearMoveMode::en_moveBackward;
	}
}

//回転計算
void TankMovingComponent::RotateCalc()
{
	//回転値
	float trunCalcValue = 0.0f;
	
	//回転処理
	switch (m_moveLRModeState)
	{
	case TankMovingComponent::en_neutralLR:



		break;
	case TankMovingComponent::en_trunLeft:

		m_rotaiton.AddRotationDegY(*m_trunSpeed);

		break;
	case TankMovingComponent::en_trunRight:

		m_rotaiton.AddRotationDegY(-*m_trunSpeed);

		break;
	default:
		break;
	}

	//モデルの回転更新
	m_rotModel->SetRotation(m_rotaiton);
	//正面値修正
	m_forward = Vector3::AxisZ;
	m_rotaiton.Apply(m_forward);
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

	//最終的な移動座標
	Vector3 finalPosition = Vector3::AxisZ;

	//キャラコン後進
	finalPosition = m_characterController
		->Execute(finalMoveSpeed, g_gameTime->GetFrameDeltaTime());

	//モデル更新
	m_rotModel->SetPosition(finalPosition);
}