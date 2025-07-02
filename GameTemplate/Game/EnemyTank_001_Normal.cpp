#include "stdafx.h"
#include "EnemyTank_001_Normal.h"

#include "EnemyTankAttributeRegistry.h"
#include "EnemyAttackPoint.h"

#include "EnemyTankStateTrackingUpdate.h"
#include "EnemyTankStateAttackMoveUpdate.h"

#include "TankShellsManager.h"
#include "TankTurretMovingComponent.h"
#include "GamePlayer.h"

//初期化関数登録処理
bool EnemyTank_001_Normal::m_attributeRegistered = [] {
	EnemyTankAttributeRegistry::EnemyTankRegisterFactory(EnEnemyTankAttribute::en_tankNormal, []() {
		return std::make_unique<EnemyTank_001_Normal>();
		});
	return true;
}();

//属性初期化関数
void EnemyTank_001_Normal::InitEnemyTankAttributeData(
	GamePlayer* player,
	EnemyTankEntity* hostTank
)
{
	//プレイヤーのインスタンス
	m_player = player;

	m_hostEnemyTankPtr = hostTank;
	//速度設定
	m_maxTankSpeed = 50.0f;
	//使用砲弾設定
	m_shellsUsed = EnTankShellsAttribute::en_normal;
	//攻撃距離設定
	m_attackPointRangeUsed = EnUseAttackPointRange::en_NearAttackPoint;
	//攻撃ポイント初期化
	EnemyAttackPointManager::GetEnemyAttackPointManagerInstance()
		->CreateEnemyAttackPoint(
			m_hostEnemyTankPtr->GetEnemyTankId(),
			m_hostEnemyTankPtr->GetPosition(),
			m_attackPointRangeUsed
		);
}

//射撃処理
void EnemyTank_001_Normal::FireProcessing()
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
bool EnemyTank_001_Normal::DeleteProcessing()
{
	//アタックポイントの使用を終了
	EnemyAttackPointManager::
		GetEnemyAttackPointManagerInstance()->EndUseAttackPoint(
			m_hostEnemyTankPtr->GetEnemyTankId(),
			m_attackPointRangeUsed
		);

	return true;
}

//ココから追跡処理

//追跡処理初期化
void EnemyTank_001_Normal::EnterTracking()
{

}

//追跡処理
const Vector3& EnemyTank_001_Normal::UpdateTracking()
{

	Vector3 attackPointPosition = EnemyAttackPointManager::GetEnemyAttackPointManagerInstance()
		->GetEnemyIdAttackPointPosition(
			m_hostEnemyTankPtr->GetEnemyTankId(),
			m_attackPointRangeUsed
		);

	m_moveDirection = attackPointPosition - m_hostEnemyTankPtr->GetPosition();

	m_moveDirection.Normalize();

	EnemyAttackPointManager::GetEnemyAttackPointManagerInstance()
		->UpdateAttackPoint(
			m_hostEnemyTankPtr->GetEnemyTankId(),
			m_hostEnemyTankPtr->GetPosition(),
			m_attackPointRangeUsed
		);

	return m_moveDirection;
}

//追跡ステート遷移
bool EnemyTank_001_Normal::RequestStateTracking(uint32_t& request) 
{
	if (EnemyAttackPointManager::GetEnemyAttackPointManagerInstance()
		->IsIdEnemyAtAttackPoint(
			m_hostEnemyTankPtr->GetEnemyTankId(),
			m_hostEnemyTankPtr->GetPosition(),
			m_attackPointRangeUsed
		) == true)
	{
		request = EnemyTankStateAttackMoveUpdate::ID();

		return true;
	}

	return false;
}

void EnemyTank_001_Normal::EndTracking()
{

}

//ココから攻撃動作処理

//攻撃動作初期化
void EnemyTank_001_Normal::EnterAttackMove()
{
	m_hostEnemyTankPtr->SetFireFlag(true);
}

//攻撃動作
const Vector3& EnemyTank_001_Normal::UpdateAttackMove()
{
	return Vector3::Zero;
}

bool EnemyTank_001_Normal::RequestStateAttackMove(uint32_t& request)
{
	if (EnemyAttackPointManager::GetEnemyAttackPointManagerInstance()
		->IsIdEnemyInAttackEndRadius(
			m_hostEnemyTankPtr->GetEnemyTankId(),
			m_hostEnemyTankPtr->GetPosition(),
			m_attackPointRangeUsed
		) == false)
	{
		request = EnemyTankStateTrackingUpdate::ID();

		return true;
	}

	return false;
}

void EnemyTank_001_Normal::EndAttackMove()
{
	m_hostEnemyTankPtr->SetFireFlag(false);
}

//ココから固有処理

void EnemyTank_001_Normal::EnterUnique()
{
	//特に無し
}

const Vector3& EnemyTank_001_Normal::UpdateUnique()
{
	//特に無し
	return Vector3::Zero;
}

bool EnemyTank_001_Normal::RequestStateUnique(uint32_t& request)
{
	//特に無し
	return false;
}

void EnemyTank_001_Normal::EndUnique()
{
	//特に無し
}
