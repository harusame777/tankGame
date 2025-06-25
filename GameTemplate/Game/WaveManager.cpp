#include "stdafx.h"
#include "WaveManager.h"

#include <random>
#include <algorithm>

#include "WaveData.h"
#include "EnemyTankEntity.h"
#include "EnemyTankManager.h"
#include "WaveSpawnPointRegistry.h"

//インスタンス初期化
WaveManager* WaveManager::m_waveManagerInstance = nullptr;

//初期化関数
void WaveManager::InitWaveManager()
{
	//スポーンポイントのレジストリを生成
	m_spawnPointRegistry = new WaveSpawnPointRegistry;
	//初期化
	m_spawnPointRegistry->InitWaveSpawnPointRegistry();
}

//更新関数
void WaveManager::UpdateWaveManager()
{
	m_nowWave->UpdateWaveData();
}

//新しいウェーブデータを作成
void WaveManager::CreateAndStartWaveData(
	int spwanMaxNum,
	float enemyAddTime,
	int firstSpawn,
	int nextSpawn,
	int spwanEnemyAttribute
)
{
	//もうすでにウェーブが生成されている場合は戻す
	if (m_nowWave != nullptr)
	{
		return;
	}

	//新しいウェーブのデータを作成
	WaveData* newData = new WaveData;
	//初期設定
	newData->InitWaveData(
		GetRandomEnemyAttribute(spwanEnemyAttribute),
		m_spawnPointRegistry->GetWaveSpawnPointVector()
	);
	//現在のウェーブに設定
	m_nowWave = newData;
	//ウェーブ開始
	m_nowWave->StartWave(
		spwanMaxNum,
		enemyAddTime,
		firstSpawn,
		nextSpawn
	);
}

std::vector<EnEnemyTankAttribute> WaveManager::GetRandomEnemyAttribute(int attributeCount)
{
	//全属性のリストを作成
	std::vector<EnEnemyTankAttribute> allAttributeList;
	for (int i = 0;i < static_cast<int>(EnEnemyTankAttribute::en_count);++i)
	{
		allAttributeList.push_back(static_cast<EnEnemyTankAttribute>(i));
	}

	//シャッフルして先頭からattributeCount数取り出す
	std::random_device randomDevice;
	std::mt19937 gen(randomDevice());
	std::shuffle(allAttributeList.begin(), allAttributeList.end(), gen);

	//指定属性数がリストよりも多ければ、リストの最大数を代入
	if (attributeCount > static_cast<int>(allAttributeList.size()))
	{
		attributeCount = static_cast<int>(allAttributeList.size());
	}

	//戻り値
	return std::vector<EnEnemyTankAttribute>(
		allAttributeList.begin(),
		allAttributeList.begin() + attributeCount
	);
}

void WaveManager::NotifyWaveCompleted(WaveEndEvent endEventData)
{
	//イベントを発行
	EventManager::GetEventManagerInstance()->NotifyListeners(m_waveEndEventData);
	//削除
	delete m_nowWave;
}