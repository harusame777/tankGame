#include "stdafx.h"
#include "EnemyTankManager.h"

#include "EnemyTankAttributeBase.h"
#include "EnemyTankAttributeRegistry.h"
#include "EnemyTankEntity.h"
#include "GamePlayer.h"
#include "GamePlayerManager.h"

//インスタンス初期化
EnemyTankManager* EnemyTankManager::m_enemyTankManagerInstance = nullptr;

int EnemyTankManager::CreateNewEnemyTank(
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
		return -1;
	}
	//IDを決定
	int id = m_nextId++;
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
	//IDを設定
	newTankPtr->SetEnemyTankId(id);
	//配列登録変数に設定
	newData.m_enemyTankPtr = newTankPtr;
	//idとともに配列へ
	m_enemyTankListMap[id] = newData;
	//戻り値はid
	return id;
}

void EnemyTankManager::ActivateDeleteFlag(int enemyTankId)
{
	for (auto& tankPtr : m_enemyTankListMap)
	{
		if (tankPtr.first == enemyTankId)
		{
			tankPtr.second.m_deleteFlag = true;
		}
	}
}

//エネミータンクのリストの取得
std::vector<int> EnemyTankManager::GetEnemyTankList()
{
	//エネミータンクリストを初期化
	std::vector<int> returnList;

	//リストに現在有効なエネミータンクをまとめる
	for (auto& mapPtr : m_enemyTankListMap)
	{

		if (mapPtr.second.m_deleteFlag == true)
		{
			continue;
		}

		returnList.push_back(mapPtr.first);
	}

	return returnList;
}

bool EnemyTankManager::GetIdEnemyTankDeleteFlag(int enemyTankId)
{
	//IDのエネミータンクを探す
	auto it = m_enemyTankListMap.find(enemyTankId);

	if (it == m_enemyTankListMap.end())
	{
		return true;
	}

	return it->second.m_deleteFlag;
}

const Vector3& EnemyTankManager::GetIdEnemyTankPosition(int enemyTankId)
{
	//IDのエネミータンクを探す
	auto it = m_enemyTankListMap.find(enemyTankId);

	if (it == m_enemyTankListMap.end())
	{
		return Vector3::Zero;
	}

	return it->second.m_enemyTankPtr->GetPosition();
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
	for (auto it = m_enemyTankListMap.begin();it != m_enemyTankListMap.end();)
	{
		bool dataDeleteCondition = IsDataDelteConditions(&it->second);

		//要素内のエネミータンクが有効かどうかを調べる
		if (dataDeleteCondition == true &&
			0.0f > it->second.m_deleteDelayTime)
		{
			//削除処理
			it->second.m_enemyTankPtr->DeleteGOEnemyTank();
			//リスト削除処理
			it = m_enemyTankListMap.erase(it);
			//id使いまわしのリストに登録
		}
		else
		{
			//削除条件がtrueだったらディレイを減らす
			if (dataDeleteCondition == true)
			{
				it->second.m_deleteDelayTime -= g_gameTime->GetFrameDeltaTime();
			}
			//次の要素へ
			it++;
		}
	}
}