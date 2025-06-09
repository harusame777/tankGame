#include "stdafx.h"
#include "EnemyTank_003_Horming.h"

#include "EnemyTankAttributeRegistry.h"
#include "EnemyAttackPoint.h"
#include "EnemyAttackPointManager.h"

#include "EnemyTankStateTrackingUpdate.h"
#include "EnemyTankStateAttackMoveUpdate.h"

#include "GamePlayer.h"
#include "TankTurretMovingComponent.h"

//初期化関数登録処理
bool EnemyTank_003_Horming::m_attributeRegistered = [] {
	EnemyTankAttributeRegistry::EnemyTankRegisterFactory(EnEnemyTankAttribute::en_tankHorming, []() {
		return std::make_unique<EnemyTank_003_Horming>();
		});
	return true;
}();

//初期化関数
void EnemyTank_003_Horming::InitEnemyTankAttributeData(
	GamePlayer* player,
	EnemyTankEntity* hostTank
)
{
	m_maxTankSpeed = 30.0f;

	m_shellsUsed = EnTankShellsAttribute::en_homing;

	m_attackPointRangeUsed = EnUseAttackPointRange::en_MiddleAttackPoint;

	m_attackPointResetTimer = 3.0f;

	m_player = player;

	m_hostEnemyTankPtr = hostTank;
}

//射撃処理
void EnemyTank_003_Horming::FireProcessing()
{
	
	Vector3 hostEnemyTankPos = m_hostEnemyTankPtr->GetPosition();
	Vector3 playerPos = m_player->GetPosition();

	Vector3 turretMoveDir = playerPos - hostEnemyTankPos;

	m_hostEnemyTankPtr->SetAttackTargetDirection(turretMoveDir);

	//プレイヤーが砲塔正面にいれば射撃処理を行う
	if (m_hostEnemyTankPtr->GetTurretCompornentAddress().
		IsTurretForwardToAPosSameAngle(m_player->GetPosition()) == false)
	{
		return;
	}

	//クールタイムが残っている場合は射撃しない
	if (m_fireCoolTime >= 0.0f)
	{
		m_fireCoolTime -= g_gameTime->GetFrameDeltaTime();

		return;
	}

	//クールタイムをリセット
	m_fireCoolTime = 5.0f;
	//砲弾発射
	TankShellsManager::GetTankShellsManagerInstance()->CreateNewTankShells(
		m_shellsUsed,
		m_hostEnemyTankPtr->GetTurretCompornentAddress().GetCannonFiringPosition(),
		m_hostEnemyTankPtr->GetTurretCompornentAddress().GetTurretForward(),
		"EnemyTankAttack",
		"GamePlayerCollision",
		false
	);
}

//削除処理
bool EnemyTank_003_Horming::DeleteProcessing()
{
	return true;
}

//追跡処理類

//追跡処理初期化
void EnemyTank_003_Horming::EnterTracking()
{
	m_hostEnemyTankPtr->SetFireFlag(false);

	AttackPointReset();
}

//追跡処理更新
const Vector3& EnemyTank_003_Horming::UpdateTracking()
{
	if (m_attackPointResetTimer < 0.0f)
	{
		AttackPointReset();

		m_attackPointResetTimer = 3.0f;
	}
	else
	{
		m_attackPointResetTimer -= g_gameTime->GetFrameDeltaTime();
	}

	m_moveDirection = m_attackPoint->GetPosition() - m_hostEnemyTankPtr->GetPosition();

	m_moveDirection.Normalize();

	return m_moveDirection;
}

//追跡処理終了
void EnemyTank_003_Horming::EndTracking()
{

}

//追跡処理ステート遷移
bool EnemyTank_003_Horming::RequestStateTracking(uint32_t& request)
{
	if (EnemyAttackPointManager::GetEnemyAttackPointManagerInstance()
		->IsUseAttackPointInDistance(
			*m_attackPoint,
			m_hostEnemyTankPtr->GetPosition(),
			10.0f
		) == true)
	{
		request = EnemyTankStateAttackMoveUpdate::ID();

		return true;
	}

	return false;
}

//攻撃動作処理類

//攻撃動作処理初期化
void EnemyTank_003_Horming::EnterAttackMove()
{
	m_hostEnemyTankPtr->SetFireFlag(true);
}

//攻撃動作処理更新
const Vector3& EnemyTank_003_Horming::UpdateAttackMove()
{
	return Vector3::Zero;
}

//攻撃動作処理終了
void EnemyTank_003_Horming::EndAttackMove()
{
	AttackPointReset();
}

//攻撃動作処理ステート遷移
bool EnemyTank_003_Horming::RequestStateAttackMove(uint32_t& request)
{
	if (EnemyAttackPointManager::GetEnemyAttackPointManagerInstance()
		->IsUseAttackPointInRadius(
			*m_attackPoint,
			m_hostEnemyTankPtr->GetPosition()
		) == false)
	{
		request = EnemyTankStateTrackingUpdate::ID();

		return true;
	}

	return false;
}

//固有処理類

//固有処理初期化
void EnemyTank_003_Horming::EnterUnique()
{

}

//固有処理更新
const Vector3& EnemyTank_003_Horming::UpdateUnique()
{
	return Vector3::Zero;
}

//固有処理終了
void EnemyTank_003_Horming::EndUnique()
{

}

//固有処理ステート遷移
bool EnemyTank_003_Horming::RequestStateUnique(uint32_t& request)
{
	return false;
}

//その他類

void EnemyTank_003_Horming::AttackPointReset()
{
	if (m_attackPoint != nullptr)
	{
		EnemyAttackPointManager::
			GetEnemyAttackPointManagerInstance()->EndofUseAttackPoint(
				m_hostEnemyTankPtr,
				m_attackPointRangeUsed
			);
	}

	m_attackPoint = nullptr;

	m_attackPoint = EnemyAttackPointManager::
		GetEnemyAttackPointManagerInstance()->GetEnemyAttackPoint(
			m_hostEnemyTankPtr,
			m_attackPointRangeUsed
		);
}