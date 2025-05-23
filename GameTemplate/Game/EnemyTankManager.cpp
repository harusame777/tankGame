#include "stdafx.h"
#include "EnemyTankManager.h"

#include "EnemyTankEntity.h"
#include "GamePlayer.h"

//インスタンス初期化
EnemyTankManager* EnemyTankManager::m_enemyTankManagerInstance = nullptr;

void EnemyTankManager::CreateNewEnemyTank(
	const Vector3& createPos
)
{
	EnemyTankData newData;

	EnemyTankEntity* newTankPtr = NewGO<EnemyTankEntity>(0, "enemyTank");

	newTankPtr->SetPosition(createPos);

	newTankPtr->SetGamePlayerInstance(m_player);

	newData.m_enemyTankPtr = newTankPtr;

	m_enemyTankList.push_back(newData);
}

void EnemyTankManager::ActivateDeleteFlag(EnemyTankEntity* subjectEnemyTank)
{
	for (auto& tankPtr : m_enemyTankList)
	{
		if (tankPtr.m_enemyTankPtr == subjectEnemyTank)
		{
			tankPtr.m_deleteFlag = true;
		}
	}
}

//初期化
void EnemyTankManager::InitEnemyTankManager()
{
	m_player = FindGO<GamePlayer>("gamePlayer");
}

//更新
void EnemyTankManager::UpdateEnemyTankManager()
{
	DeleteList();
}

//リスト削除
void EnemyTankManager::DeleteList()
{
	//マップの要素分回す
	for (auto it = m_enemyTankList.begin();
		it != m_enemyTankList.end();)
	{
		bool dataDeleteCondition = IsDataDelteConditions(it._Ptr);

		//要素内のエネミータンクが有効かどうかを調べる
		if (dataDeleteCondition == true &&
			0.0f > it->m_deleteDelayTime)
		{
			//削除処理
			it->m_enemyTankPtr->DeleteGOEnemyTank();
			//リスト削除処理
			it = m_enemyTankList.erase(it);
		}
		else
		{
			//削除条件がtrueだったらディレイを減らす
			if (dataDeleteCondition == true)
			{
				it->m_deleteDelayTime -= g_gameTime->GetFrameDeltaTime();
			}
			//次の要素へ
			it++;
		}
	}
}