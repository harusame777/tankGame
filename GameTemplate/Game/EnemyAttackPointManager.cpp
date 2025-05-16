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
	int pointNum
)
{
	//リスト初期化
	m_enemyAttackPointList.clear();

	//追従させる中心点を設定
	m_followCenterPoint = &followCenterPoint;
	//アタックポイントまでの距離を設定
	m_pointTargetDistance = pointTarGetDistance;
	
	//設置方向
	Vector3 setDirection = g_vec3Front;

	//ポイントを設置する方向を回転させるクオータニオン
	Quaternion directionRot = g_quatIdentity;

	//360度をエネミーアタックポイント配列の要素数で割って等間隔で置くための角度を設定する
	directionRot.SetRotationDegY(360.0f / pointNum);

	//アタックポイント生成
	for (int num = 0; num < pointNum; num++)
	{
		EnemyAttackPointData newData;

		//アタックポイントを動的に作成
		newData.m_attackPointPtr = std::make_shared<EnemyAttackPoint>();
		//設置位置を計算
		Vector3 setPosition = *m_followCenterPoint + setDirection * m_pointTargetDistance;
		//設置位置を設定
		newData.m_attackPointPtr->SetPosition(setPosition);
		//設置方向を設定
		newData.m_attackPointPtr->SetDirection(setDirection);
		//リストに設定
		m_enemyAttackPointList.push_back(newData);
		//回転
		directionRot.Apply(setDirection);
	}
}

void EnemyAttackPointManager::UpdateEnemyAttackPoints()
{
	//リスト全体アタックポイントの位置を更新
	for (auto& attackPoint : m_enemyAttackPointList)
	{

		Vector3 updateDirection = attackPoint.m_attackPointPtr->GetDirection();

		Vector3 updatePosition = *m_followCenterPoint + updateDirection * m_pointTargetDistance;

		attackPoint.m_attackPointPtr->SetPosition(updatePosition);
	}
}

EnemyAttackPoint* EnemyAttackPointManager::GetEnemyNearAttackPoint(EnemyTankEntity* searchEnemyTank)
{
	if (searchEnemyTank == nullptr)
	{
		return nullptr;
	}

	//リストが空だったら
	if (m_enemyAttackPointList.empty() == true)
	{
		//ヌルを返す
		return nullptr;
	}

	//探すエネミーの位置を取得
	Vector3 enemyTankPos = searchEnemyTank->GetPosition();

	//比較用ポインタ
	EnemyAttackPoint* closestAttackPoint = nullptr;
	//比較用距離
	float closestLen = 0.0f;
	
	for (auto& attackPoint : m_enemyAttackPointList)
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
			closestAttackPoint = attackPoint.m_attackPointPtr.get();

			closestLen = EnemyToAttackPointLen;

			continue;
		}
		
		//計算した距離を現在一番近いアタックポイントと距離を比較する
		if (EnemyToAttackPointLen < closestLen)
		{
			//もし真であれば入れ替え処理を行う
			closestAttackPoint = attackPoint.m_attackPointPtr.get();
			closestLen = EnemyToAttackPointLen;
		}
	}

	//もしアタックポイントが現在満員だったら
	if (closestAttackPoint == nullptr)
	{
		//nullを返す
		return nullptr;
	}

	return closestAttackPoint;
}

//アタックポイントの使用終了を知らせる関数
void EnemyAttackPointManager::EndofUseAttackPoint(EnemyTankEntity* enemyTank)
{
	for (auto& attackPoint : m_enemyAttackPointList)
	{
		if (attackPoint.m_enemyTankEntityPtr == enemyTank)
		{
			attackPoint.m_enemyTankEntityPtr = nullptr;
		}
	}
}

void EnemyAttackPointManager::InitEnemyAttackPointManager()
{

}

void EnemyAttackPointManager::UpdateEnemyAttackPointManager()
{

}

