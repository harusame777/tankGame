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
TankMovingComponent::TankMovingComponent(
	Vector3& forward,							//正面方向
	Vector3& moveDirection,						//移動方向
	float& moveSpeed,							//最高速度
	float& acceleration,						//加速度
	float& deceleration,						//減速
	float& friction,							//自然減速
	CharacterController& characterControoler	//キャラコン
)
{
	//正面方向のアドレスを取得
	m_forward = &forward;
	//移動方向のアドレスを取得
	m_moveDirection = &moveDirection;
	//移動速度のアドレスを取得
	m_moveSpeed = &moveSpeed;
	//加速度のアドレスを取得
	m_acceleration = &acceleration;
	//減速のアドレスを取得
	m_deceleration = &deceleration;
	//自然減速のアドレスを取得
	m_friction = &friction;
	//キャラクターコントローラーのアドレスを取得
	m_characterController = &characterControoler;
}

//計算値を取得する
const Vector3& TankMovingComponent::GetCalcValue()
{
	
	//まずは前進させるか回転させるかを判定する
	RotAndMoveDetermination();

	//移動計算
	MoveCalc();

}

//どう移動させるかどう回転させるかを判定
void TankMovingComponent::RotAndMoveDetermination()
{
	//正面値
	Vector3 forward = *m_forward;
	//移動先方向
	Vector3 moveDirection = *m_moveDirection;

	//水平方向で考えるためY値をゼロにする
	forward.y = 0.0f;
	moveDirection.y = 0.0f;

	//移動方向の2乗の数値を計算
	float distanceSq = moveDirection.LengthSq();

	//正面値と移動方向のベクトルを単位ベクトルにする
	forward.Normalize();
	moveDirection.Normalize();

	//角度関係
	float dot = 0.0f;
	Vector3 cross;

	//前進回転闘値計算
	Quaternion rotCalc;
	rotCalc.AddRotationDegZ(10.0f);
	float forwardThreshold = rotCalc.z;

	//後進回転闘値計算
	rotCalc.AddRotationDegZ(20.0f);
	float backwardThreshold = rotCalc.z;

	//正面値と移動方向の内積を計算し、角度を求める
	dot = Dot(forward, moveDirection);

	//外積を使い左に回転するか右に回転するかを判定
	cross = Cross(forward, moveDirection);

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

//移動計算
void TankMovingComponent::MoveCalc()
{

}