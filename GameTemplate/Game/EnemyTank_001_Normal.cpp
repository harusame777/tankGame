#include "stdafx.h"
#include "EnemyTank_001_Normal.h"

#include "EnemyTankAttributeRegistry.h"
#include "EnemyAttackPointManager.h"
#include "EnemyAttackPoint.h"

#include "EnemyTankStateTrackingUpdate.h"
#include "EnemyTankStateAttackMoveUpdate.h"

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

	m_player = player;

	m_hostEnemyTankPtr = hostTank;
}

//削除処理
void EnemyTank_001_Normal::DeleteProcessing()
{

}

//ココから追跡処理

//追跡処理初期化
void EnemyTank_001_Normal::EnterTracking()
{
	if (m_attackPoint == nullptr)
	{
		m_attackPoint = EnemyAttackPointManager::
			GetEnemyAttackPointManagerInstance()->GetEnemyNearAttackPoint(m_hostEnemyTankPtr);
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
	//攻撃ポイントを取得
	if (m_attackPoint == nullptr)
	{
		m_attackPoint = EnemyAttackPointManager::
			GetEnemyAttackPointManagerInstance()->GetEnemyNearAttackPoint(m_hostEnemyTankPtr);
	}
}

//攻撃動作
const Vector3& EnemyTank_001_Normal::UpdateAttackMove()
{
	return Vector3::Zero;
}

bool EnemyTank_001_Normal::RequestStateAttackMove(uint32_t& request)
{
	if (IsAttackPointInRadius() == false)
	{
		request = EnemyTankStateTrackingUpdate::ID();

		return true;
	}

	return false;
}

void EnemyTank_001_Normal::EndAttackMove()
{
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
bool EnemyTank_001_Normal::IsAttackPointInRadius()
{
	const float attackPointRadiusSq = m_attackPoint->GetRadiusSq();

	//ホストタンクのポジション
	const Vector3 hostEnemyTankPos = m_hostEnemyTankPtr->GetPosition();
	//プレイヤーのポジション
	const Vector3 attackPointPos = m_attackPoint->GetPosition();
	//ホストタンクからプレイヤーへ向かうベクトル(2Dベクトルとして考える)
	const float distX = attackPointPos.x - hostEnemyTankPos.x;
	const float distY = attackPointPos.y - hostEnemyTankPos.y;
	//ホストタンクとプレイヤーの半径
	const float hostEnemyTankToAttackPointRangeSq = distX * distX + distY * distY;

	if (attackPointRadiusSq >= hostEnemyTankToAttackPointRangeSq)
	{
		return true;
	}

	return false;
}
