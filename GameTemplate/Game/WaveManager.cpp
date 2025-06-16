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
WaveData* WaveManager::CreateNewWaveData(
	int enemyAppearNum,
	float enemyReapperanceTime
)
{
	//新しいウェーブのデータを作成
	WaveData* newData = new WaveData;
	//初期設定
	newData->InitWaveData(
		GetRandomEnemyAttribute(3),
		m_spawnPointRegistry->GetWaveSpawnPointVector()
	);
	//再出現までの時間を設定
	newData->SetEnemyReappearanceTime(enemyReapperanceTime);
	//出現するエネミーの数を設定
	newData->SetEnemySpawnMaxNum(enemyAppearNum);
	//現在のウェーブに設定
	m_nowWave = newData;
	//敵出現までのタイマー設定
	return m_nowWave;
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