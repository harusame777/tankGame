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
		attackPointPos,
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
		Vector3 direction = followPosition - useEntityPos;
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

EnemyAttackPoint* EnemyAttackPointManager::GetEnemyAttackPoint(
	EnemyTankEntity* searchEnemyTank,
	const EnUseAttackPointRange useRange
)
{
	if (searchEnemyTank == nullptr)
	{
		return nullptr;
	}

	//取得する距離のアタックポイントリストを取得
	std::vector<EnemyAttackPointData>* useList = GetUseAttackPointRangeList(useRange);

	//リストが空だったら
	if (useList->empty() == true)
	{
		//ヌルを返す
		return nullptr;
	}

	//探すエネミーの位置を取得
	Vector3 enemyTankPos = searchEnemyTank->GetPosition();

	//比較用ポインタ
	EnemyAttackPointData* closestAttackPoint = nullptr;
	//比較用距離
	float closestLen = 0.0f;
	
	for (auto& attackPoint : *useList)
	{
		//アタックポイントの位置を取得
		Vector3 attackPointPos = attackPoint.m_attackPointPtr->GetPosition();
		//エネミーからアタックポイントまでの距離を計算
		Vector3 EnemyToAttackPointDis = attackPointPos - enemyTankPos;
		//計算したベクトルから長さを取得
		float EnemyToAttackPointLen = EnemyToAttackPointDis.Length();

		//ココから判定

		//アタックポイントが使用中かどうか判定
		if (nullptr != attackPoint.m_enemyTankEntityPtr)
		{
			//もし使用中だったらこの一回を飛ばす
			continue;
		}

		//比較用のポインタがNULLだったら代入する
		if (closestAttackPoint == nullptr)
		{
			closestAttackPoint = &attackPoint;

			closestLen = EnemyToAttackPointLen;

			continue;
		}
		
		//計算した距離を現在一番近いアタックポイントと距離を比較する
		if (EnemyToAttackPointLen < closestLen)
		{
			//もし真であれば入れ替え処理を行う
			closestAttackPoint = &attackPoint;
			closestLen = EnemyToAttackPointLen;
		}
	}

	//もしアタックポイントが現在満員だったら
	if (closestAttackPoint == nullptr)
	{
		//nullを返す
		return nullptr;
	}

	//選択されたアタックポイントに使用中のエネミーを設定
	closestAttackPoint->m_enemyTankEntityPtr = searchEnemyTank;

	return closestAttackPoint->m_attackPointPtr.get();
}

//同じエネミータンクのアドレスを持っているアタックポイントを取得する
EnemyAttackPoint* EnemyAttackPointManager::GetSameEnemyAddressAttackPoint(
	EnemyTankEntity* searchEnemyTank,
	const EnUseAttackPointRange useRange
)
{
	if (searchEnemyTank == nullptr)
	{
		return nullptr;
	}

	//取得する距離のアタックポイントリストを取得
	std::vector<EnemyAttackPointData>* useList = GetUseAttackPointRangeList(useRange);

	EnemyAttackPoint* attackPoint = nullptr;

	for (auto& listPtr : *useList)
	{
		if (listPtr.m_enemyTankEntityPtr == searchEnemyTank)
		{
			attackPoint = listPtr.m_attackPointPtr.get();
		}
	}

	if (attackPoint == nullptr)
	{
		return nullptr;
	}

	return attackPoint;
}

//アタックポイントの使用終了を知らせる関数
void EnemyAttackPointManager::EndofUseAttackPoint(
	EnemyTankEntity* enemyTank,
	const EnUseAttackPointRange useRange
)
{
	if (enemyTank == nullptr)
	{
		return;
	}

	//仕様解除する距離のアタックポイントリストを取得
	std::vector<EnemyAttackPointData>* useList = GetUseAttackPointRangeList(useRange);

	for (auto& attackPoint : *useList)
	{
		if (attackPoint.m_enemyTankEntityPtr == enemyTank)
		{
			attackPoint.m_enemyTankEntityPtr = nullptr;
		}
	}
}

std::vector<EnemyAttackPointManager::EnemyAttackPointData>* EnemyAttackPointManager::GetUseAttackPointRangeList(const EnUseAttackPointRange useRange)
{

	switch (useRange)
	{
	case EnUseAttackPointRange::en_NearAttackPoint:

		return &m_enemyNearAttackPointList;

		break;
	case EnUseAttackPointRange::en_MiddleAttackPoint:

		return &m_enemyMiddleAttackPointList;

		break;
	default:
		break;
	}

}

bool EnemyAttackPointManager::IsUseAttackPointInDistance(
	const EnemyAttackPoint& useAttackPoint,
	const Vector3& useEntityPos,
	float triggerDistanceThreshold
)
{
	//アタックポイントのポジション
	const Vector3 attackPointPos = useAttackPoint.GetPosition();
	//2点間のベクトルを作成
	const Vector3 positionToAttackPointVec = attackPointPos - useEntityPos;
	//距離を計算
	const float distance = positionToAttackPointVec.Length();
	//距離がtriggerDistanceThreshold以下になったらtrueを返す
	if (distance < triggerDistanceThreshold)
	{
		return true;
	}

	return false;
}

bool EnemyAttackPointManager::IsUseAttackPointInRadius(
	const EnemyAttackPoint& useAttackPoint,
	const Vector3& useEntityPos
)
{
	//アタックポイントのポジション
	const Vector3 attackPointPos = useAttackPoint.GetPosition();
	//ポジションからアタックポイントに向かうベクトル(2Dベクトルとして考える)
	const float distX = attackPointPos.x - useEntityPos.x;
	const float distZ = attackPointPos.z - useEntityPos.z;
	//半径計算
	const float hostEnemyTankToAttackPointRangeSq = distX * distX + distZ * distZ;

	if (useAttackPoint.GetRadiusSq() >= hostEnemyTankToAttackPointRangeSq)
	{
		return true;
	}

	return false;
}

void EnemyAttackPointManager::InitEnemyAttackPointManager()
{

}

void EnemyAttackPointManager::UpdateEnemyAttackPointManager()
{

}

