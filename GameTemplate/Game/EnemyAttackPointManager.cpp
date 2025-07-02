#include "stdafx.h"
#include "EnemyAttackPointManager.h"

#include "EnemyAttackPoint.h"
#include "EnemyTankManager.h"
#include "EnemyTankEntity.h"

//インスタンス初期化
EnemyAttackPointManager* EnemyAttackPointManager::m_enemyAttackPointManagerInstance = nullptr;

//アタックポイントの範囲の初期化
void EnemyAttackPointManager::InitAttackPointRadius(
	float attackPointRadius,
	float attackEndRadius,
	EnUseAttackPointRange useRange
)
{

	AttackPointListInfo newAttackPointInfo;

	//アタックポイントの半径を設定
	newAttackPointInfo.m_attackPointRadius = attackPointRadius;
	
	//アタックポイントの使用範囲を設定
	newAttackPointInfo.m_attackEndRadius = attackEndRadius;

	//アタックポイントのリストを初期化
	m_attackPointInfoMap[useRange] = newAttackPointInfo;
}

void EnemyAttackPointManager::CreateEnemyAttackPoint(
	int enemyTankId,
	const Vector3& enemyPos,
	EnUseAttackPointRange useRange
)
{
	auto useAttackPointList = m_attackPointInfoMap.find(useRange);

	//指定しようとした箇所のアタックポイント情報が存在しない場合は戻す
	if (useAttackPointList == m_attackPointInfoMap.end())
	{
		return;
	}

	//登録しようとしたエネミータンクのIDがすでに存在している場合は戻す
	if (useAttackPointList->second.m_attackPointMap.count(enemyTankId) > 0)
	{
		return;
	}

	auto newAttackPoint = std::make_unique<EnemyAttackPoint>();

	useAttackPointList->second.m_attackPointMap[enemyTankId] = std::move(newAttackPoint);

	//該当するエネミータンクIDのアタックポイントを取得
	auto useAttackPoint = useAttackPointList->second.m_attackPointMap.find(enemyTankId);

	//該当のエネミータンクIDのアタックポイントが存在しない場合は戻す
	if (useAttackPoint == useAttackPointList->second.m_attackPointMap.end())
	{
		return;
	}

	//アタックポイントの位置を更新するための位置を計算
	Vector3 updatePos = CalcAttackPointPosition(
		useAttackPointList->second.m_followPosition,
		useAttackPoint->second->GetPosition(),
		enemyPos,
		useAttackPointList->second.m_attackPointRadius,
		useAttackPointList->second.m_attackEndRadius
	);
}

void EnemyAttackPointManager::UpdateAttackPointRadius(
	const Vector3& followPosition,
	EnUseAttackPointRange useRange
)
{
	auto useAttackPointList = m_attackPointInfoMap.find(useRange);

	//指定しようとした箇所のアタックポイント情報が存在しない場合は戻す
	if (useAttackPointList == m_attackPointInfoMap.end())
	{
		return;
	}

	//追従位置を更新
	useAttackPointList->second.m_followPosition = followPosition;
}

void EnemyAttackPointManager::UpdateAttackPoint(
	int enemyTankId,
	const Vector3& useEnemyPos,
	EnUseAttackPointRange useRange
)
{
	//該当する距離の情報を取得
	auto useAttackPointList = m_attackPointInfoMap.find(useRange);

	//指定しようとした箇所のアタックポイント情報が存在しない場合は戻す
	if (useAttackPointList == m_attackPointInfoMap.end())
	{
		return;
	}

	//該当するエネミータンクIDのアタックポイントを取得
	auto useAttackPoint = useAttackPointList->second.m_attackPointMap.find(enemyTankId);

	//該当のエネミータンクIDのアタックポイントが存在しない場合は戻す
	if (useAttackPoint == useAttackPointList->second.m_attackPointMap.end())
	{
		return;
	}

	//アタックポイントの位置を更新するための位置を計算
	Vector3 updatePos = CalcAttackPointPosition(
		useAttackPointList->second.m_followPosition,
		useAttackPoint->second->GetPosition(),
		useEnemyPos,
		useAttackPointList->second.m_attackPointRadius,
		useAttackPointList->second.m_attackEndRadius
	);
	
	//位置更新
	useAttackPoint->second->SetPosition(updatePos);
}

const Vector3& EnemyAttackPointManager::CalcAttackPointPosition(
	const Vector3& followPosition,
	const Vector3& attackPointPos,
	const Vector3& useEntityPos,
	float attackPointRadius,
	float attackEndRadius
)
{
	//戻り値
	Vector3 returnPos = Vector3::Zero;

	//まずはアタックポイントが半径内に存在するかどうかを判定
	if (IsAPositionInBRadius(
		useEntityPos,
		followPosition,
		attackEndRadius
	))
	{
		//もし半径内に存在していたらそのままアタックポイントの位置を返す
		returnPos = attackPointPos;
	}
	//範囲外なら半径の外周に位置するように計算
	else
	{
		//使用エネミータンク位置から追従位置へ伸びるベクトル
		Vector3 direction = useEntityPos - followPosition;
		direction.Normalize();

		//Y値は不要なので0にする
		direction.y = 0.0f;

		//更新位置を計算
		returnPos = followPosition + direction * attackPointRadius;
	}

	return returnPos;
}

bool EnemyAttackPointManager::IsAPositionInBRadius(
	const Vector3& aPosition,
	const Vector3& bPosition,
	float bRadius
)
{
	float distX = aPosition.x - bPosition.x;
	float distY = aPosition.y - bPosition.y;
	float distZ = aPosition.z - bPosition.z;
	float distSq = distX * distX + distY * distY + distZ * distZ;
	float radiusSq = bRadius * bRadius;
	return distSq <= radiusSq;
}

const Vector3& EnemyAttackPointManager::GetEnemyIdAttackPointPosition(
	int enemyTankId,
	EnUseAttackPointRange useRange
)
{
	//該当する距離の情報を取得
	auto useAttackPointList = m_attackPointInfoMap.find(useRange);

	//指定しようとした箇所のアタックポイント情報が存在しない場合は戻す
	if (useAttackPointList == m_attackPointInfoMap.end())
	{
		return Vector3::Zero;
	}

	//該当するエネミータンクIDのアタックポイントを取得
	auto useAttackPoint = useAttackPointList->second.m_attackPointMap.find(enemyTankId);

	//該当のエネミータンクIDのアタックポイントが存在しない場合は戻す
	if (useAttackPoint == useAttackPointList->second.m_attackPointMap.end())
	{
		return Vector3::Zero;
	}

	return useAttackPoint->second->GetPosition();
}

bool EnemyAttackPointManager::IsIdEnemyAtAttackPoint(
	int enemyTankId,
	const Vector3& enemyPos,
	EnUseAttackPointRange useRange
)
{
	//該当する距離の情報を取得
	auto useAttackPointList = m_attackPointInfoMap.find(useRange);

	//指定しようとした箇所のアタックポイント情報が存在しない場合は戻す
	if (useAttackPointList == m_attackPointInfoMap.end())
	{
		return false;
	}

	//該当するエネミータンクIDのアタックポイントを取得
	auto useAttackPoint = useAttackPointList->second.m_attackPointMap.find(enemyTankId);

	//該当のエネミータンクIDのアタックポイントが存在しない場合は戻す
	if (useAttackPoint == useAttackPointList->second.m_attackPointMap.end())
	{
		return false;
	}

	
	Vector3 attackPointPos = useAttackPoint->second->GetPosition();

	Vector3 enemyToAttackPVec = attackPointPos - enemyPos;

	float length = enemyToAttackPVec.Length();

	if (length < 1.0f)
	{
		return true;
	}

	return false;
}

bool EnemyAttackPointManager::IsIdEnemyInAttackPointRadius(
	int enemyTankId,
	const Vector3& enemyPos,
	EnUseAttackPointRange useRange
)
{
	//該当する距離の情報を取得
	auto useAttackPointList = m_attackPointInfoMap.find(useRange);

	//指定しようとした箇所のアタックポイント情報が存在しない場合は戻す
	if (useAttackPointList == m_attackPointInfoMap.end())
	{
		return false;
	}

	//該当するエネミータンクIDのアタックポイントを取得
	auto useAttackPoint = useAttackPointList->second.m_attackPointMap.find(enemyTankId);

	//該当のエネミータンクIDのアタックポイントが存在しない場合は戻す
	if (useAttackPoint == useAttackPointList->second.m_attackPointMap.end())
	{
		return false;
	}

	bool isInRadius = false;

	//アタックポイントの位置とエネミーの位置を比較して半径内に存在するかどうかを判定
	isInRadius = IsAPositionInBRadius(
		useAttackPoint->second->GetPosition(),
		enemyPos,
		useAttackPointList->second.m_attackPointRadius
	);

	return isInRadius;
}

bool EnemyAttackPointManager::IsIdEnemyInAttackEndRadius(
	int enemyTankId,
	const Vector3& enemyPos,
	EnUseAttackPointRange useRange
)
{
	//該当する距離の情報を取得
	auto useAttackPointList = m_attackPointInfoMap.find(useRange);

	//指定しようとした箇所のアタックポイント情報が存在しない場合は戻す
	if (useAttackPointList == m_attackPointInfoMap.end())
	{
		return false;
	}

	//該当するエネミータンクIDのアタックポイントを取得
	auto useAttackPoint = useAttackPointList->second.m_attackPointMap.find(enemyTankId);

	//該当のエネミータンクIDのアタックポイントが存在しない場合は戻す
	if (useAttackPoint == useAttackPointList->second.m_attackPointMap.end())
	{
		return false;
	}

	bool isInRadius = false;

	//アタックポイントの位置とエネミーの位置を比較して半径内に存在するかどうかを判定
	isInRadius = IsAPositionInBRadius(
		useAttackPointList->second.m_followPosition,
		enemyPos,
		useAttackPointList->second.m_attackEndRadius
	);

	return isInRadius;
}

void EnemyAttackPointManager::EndUseAttackPoint(
	int enemyTankId,
	EnUseAttackPointRange useRange
)
{

	//該当する距離の情報を取得
	auto useAttackPointList = m_attackPointInfoMap.find(useRange);

	//指定しようとした箇所のアタックポイント情報が存在しない場合は戻す
	if (useAttackPointList == m_attackPointInfoMap.end())
	{
		return;
	}

	//該当するエネミータンクIDのアタックポイントを取得
	auto useAttackPoint = useAttackPointList->second.m_attackPointMap.find(enemyTankId);

	//該当のエネミータンクIDのアタックポイントが存在しない場合は戻す
	if (useAttackPoint == useAttackPointList->second.m_attackPointMap.end())
	{
		return;
	}

	useAttackPointList->second.m_attackPointMap.erase(useAttackPoint);
}

void EnemyAttackPointManager::InitEnemyAttackPointManager()
{

}

void EnemyAttackPointManager::UpdateEnemyAttackPointManager()
{

}

