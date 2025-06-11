#include "stdafx.h"
#include "EnemyTankManager.h"

#include "EnemyTankAttributeBase.h"
#include "EnemyTankAttributeRegistry.h"
#include "EnemyTankEntity.h"
#include "GamePlayer.h"
#include "GamePlayerManager.h"

//インスタンス初期化
EnemyTankManager* EnemyTankManager::m_enemyTankManagerInstance = nullptr;

EnemyTankEntity* EnemyTankManager::CreateNewEnemyTank(
	EnEnemyTankAttribute attribute,
	const Vector3& createPos
)
{
	//属性を作成、取得
	std::shared_ptr<EnemyTankAttributeBase> newAttribute
		= EnemyTankAttributeRegistry::CreateEnemyTankAttribute(attribute);
	//ヌルだったら作成しない
	if (newAttribute == nullptr)
	{
		return nullptr;
	}
	//配列登録変数
	EnemyTankData newData;
	//新しいエネミータンク
	EnemyTankEntity* newTankPtr = NewGO<EnemyTankEntity>(0, "enemyTank");
	//位置を設定
	newTankPtr->SetPosition(createPos);
	//プレイヤーのインスタンスを設定
	newTankPtr->SetGamePlayerInstance(m_player);
	//属性を設定
	newTankPtr->SetAttribute(newAttribute);
	//配列登録変数に設定
	newData.m_enemyTankPtr = newTankPtr;
	//配列登録
	m_enemyTankList.push_back(newData);

	return newTankPtr;
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

//エネミータンクのリストの取得
const std::vector<EnemyTankEntity*>& EnemyTankManager::GetEnemyTankList()
{
	//エネミータンクリストを初期化
	m_returnEnemyTankList.clear();

	//リストに現在有効なエネミータンクをまとめる
	for (auto it = m_enemyTankList.begin();it != m_enemyTankList.end();it++)
	{

		if (it->m_deleteFlag == true)
		{
			continue;
		}

		m_returnEnemyTankList.push_back(it->m_enemyTankPtr);
	}

	return m_returnEnemyTankList;
}

//初期化
void EnemyTankManager::InitEnemyTankManager()
{
	m_player = GamePlayerManager::GetGamePlayerManagerInstance()->GetGamePlayerInstance();
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