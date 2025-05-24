#include "stdafx.h"
#include "EnemyTank_001_Normal.h"

#include "EnemyTankAttributeRegistry.h"
#include "EnemyAttackPointManager.h"
#include "EnemyAttackPoint.h"

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

//固有処理
void EnemyTank_001_Normal::UniqueProcessing()
{

}

//削除処理
void EnemyTank_001_Normal::DeleteProcessing()
{

}

//追跡処理
const Vector3& EnemyTank_001_Normal::TrackingAttribute()
{
	Vector3 moveDir = m_attackPoint->GetPosition() - m_hostEnemyTankPtr->GetPosition();

	moveDir.Normalize();

	return moveDir;
}

//追跡ステート遷移
bool EnemyTank_001_Normal::RequestStateTrackingAttribute(uint32_t& request) 
{
	//現在このエネミータンクが見ているアタックポイントを取得
	if (m_attackPoint == nullptr)
	{
		m_attackPoint = EnemyAttackPointManager::
			GetEnemyAttackPointManagerInstance()->GetEnemyNearAttackPoint(m_hostEnemyTankPtr);
	}

	if (IsAttackPointInRadius() == true)
	{
		request = EnemyTankStateAttackMoveUpdate::ID();

		return true;
	}

	return false;
}

//攻撃動作
const Vector3& EnemyTank_001_Normal::AttackMoveAttribute()
{
	return Vector3::Zero;
}

bool EnemyTank_001_Normal::RequestStateAttackMoveAttribute(uint32_t& request)
{
	return false;
}

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
