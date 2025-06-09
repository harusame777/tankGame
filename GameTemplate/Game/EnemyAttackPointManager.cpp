#include "stdafx.h"
#include "EnemyAttackPointManager.h"

#include "EnemyAttackPoint.h"
#include "EnemyTankManager.h"
#include "EnemyTankEntity.h"

//インスタンス初期化
EnemyAttackPointManager* EnemyAttackPointManager::m_enemyAttackPointManagerInstance = nullptr;

//アタックポイント作成
void EnemyAttackPointManager::CreateEnemyAttackPoints(
	Vector3& followCenterPoint,
	float pointTarGetDistance,
	float pointAttackRadius,
	int pointNum,
	const EnUseAttackPointRange useRange
)
{
	//追従させる中心点を設定
	m_followCenterPoint = &followCenterPoint;
	
	//設置方向
	Vector3 setDirection = g_vec3Front;

	//ポイントを設置する方向を回転させるクオータニオン
	Quaternion directionRot = g_quatIdentity;

	//360度をエネミーアタックポイント配列の要素数で割って等間隔で置くための角度を設定する
	directionRot.SetRotationDegY(360.0f / pointNum);

	//生成する距離のアタックポイントのリストを取得
	std::vector<EnemyAttackPointData>* useList = GetUseAttackPointRangeList(useRange);

	//近距離アタックポイント生成
	for (int num = 0; num < pointNum; num++)
	{
		EnemyAttackPointData newData;

		//アタックポイントを動的に作成
		newData.m_attackPointPtr = std::make_shared<EnemyAttackPoint>();
		//アタックポイントまでの距離
		newData.m_pointTargetDistance = pointTarGetDistance;
		//設置位置を計算
		Vector3 setPosition = *m_followCenterPoint + setDirection * newData.m_pointTargetDistance;
		//設置位置を設定
		newData.m_attackPointPtr->SetPosition(setPosition);
		//設置方向を設定
		newData.m_attackPointPtr->SetDirection(setDirection);
		//攻撃開始範囲を設定
		newData.m_attackPointPtr->SetRadius(pointAttackRadius);
		//リストに設定
		useList->push_back(newData);
		//回転
		directionRot.Apply(setDirection);
	}
}

void EnemyAttackPointManager::UpdateEnemyAttackPoints()
{
	//近距離アタックポイントの位置を更新
	for (auto& attackPoint : m_enemyNearAttackPointList)
	{

		Vector3 updateDirection = attackPoint.m_attackPointPtr->GetDirection();

		Vector3 updatePosition = *m_followCenterPoint + updateDirection * attackPoint.m_pointTargetDistance;

		attackPoint.m_attackPointPtr->SetPosition(updatePosition);
	}

	//中距離アタックポイントの位置を更新
	for (auto& attackPoint : m_enemyMiddleAttackPointList)
	{

		Vector3 updateDirection = attackPoint.m_attackPointPtr->GetDirection();

		Vector3 updatePosition = *m_followCenterPoint + updateDirection * attackPoint.m_pointTargetDistance;

		attackPoint.m_attackPointPtr->SetPosition(updatePosition);
	}
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

