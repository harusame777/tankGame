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
	m_maxTankSpeed = 50.0f;

	m_shellsUsed = EnTankShellsAttribute::en_normal;

	m_attackPointRangeUsed = EnUseAttackPointRange::en_NearAttackPoint;

	m_player = player;

	m_hostEnemyTankPtr = hostTank;
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
		GetEnemyAttackPointManagerInstance()->EndofUseAttackPoint(
			m_hostEnemyTankPtr,
			m_attackPointRangeUsed
		);

	return true;
}

//ココから追跡処理

//追跡処理初期化
void EnemyTank_001_Normal::EnterTracking()
{
	m_hostEnemyTankPtr->SetFireFlag(false);

	if (m_attackPoint == nullptr)
	{
		m_attackPoint = EnemyAttackPointManager::
			GetEnemyAttackPointManagerInstance()->GetEnemyAttackPoint(
				m_hostEnemyTankPtr,m_attackPointRangeUsed);
	}
}

//追跡処理
const Vector3& EnemyTank_001_Normal::UpdateTracking()
{
	m_moveDirection = m_attackPoint->GetPosition() - m_hostEnemyTankPtr->GetPosition();

	m_moveDirection.Normalize();

	return m_moveDirection;
}

//追跡ステート遷移
bool EnemyTank_001_Normal::RequestStateTracking(uint32_t& request) 
{
	if (IsAttackPointInRadius() == true)
	{
		request = EnemyTankStateAttackMoveUpdate::ID();

		return true;
	}

	return false;
}

void EnemyTank_001_Normal::EndTracking()
{
	m_attackPoint = nullptr;
}

//ココから攻撃動作処理

//攻撃動作初期化
void EnemyTank_001_Normal::EnterAttackMove()
{
	m_hostEnemyTankPtr->SetFireFlag(true);

	//攻撃ポイントを取得
	m_attackPoint = EnemyAttackPointManager::
		GetEnemyAttackPointManagerInstance()->GetSameEnemyAddressAttackPoint(
			m_hostEnemyTankPtr, m_attackPointRangeUsed);

}

//攻撃動作
const Vector3& EnemyTank_001_Normal::UpdateAttackMove()
{
	return Vector3::Zero;
}

bool EnemyTank_001_Normal::RequestStateAttackMove(uint32_t& request)
{
	if (IsAttackPointInRadius(m_attackPoint->GetRadiusSq()) == false)
	{
		request = EnemyTankStateTrackingUpdate::ID();

		return true;
	}

	return false;
}

void EnemyTank_001_Normal::EndAttackMove()
{
	EnemyAttackPointManager::
		GetEnemyAttackPointManagerInstance()->EndofUseAttackPoint(
			m_hostEnemyTankPtr,
			m_attackPointRangeUsed
		);

	m_attackPoint = nullptr;
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

//射撃処理

//その他関数など

//アタックポイント内にホストタンクが入っているかどうか
bool EnemyTank_001_Normal::IsAttackPointInRadius(float radius)
{

	//ホストタンクのポジション
	const Vector3 hostEnemyTankPos = m_hostEnemyTankPtr->GetPosition();
	//プレイヤーのポジション
	const Vector3 attackPointPos = m_attackPoint->GetPosition();
	//ホストタンクからプレイヤーへ向かうベクトル(2Dベクトルとして考える)
	const float distX = attackPointPos.x - hostEnemyTankPos.x;
	const float distY = attackPointPos.y - hostEnemyTankPos.y;
	//ホストタンクとプレイヤーの半径
	const float hostEnemyTankToAttackPointRangeSq = distX * distX + distY * distY;

	if (radius >= hostEnemyTankToAttackPointRangeSq)
	{
		return true;
	}

	return false;
}
