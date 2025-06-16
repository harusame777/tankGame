#include "stdafx.h"		
#include "WaveData.h"

#include <random>
#include <algorithm>

#include "EnemyTankManager.h"

void WaveData::InitWaveData(
	std::vector<EnEnemyTankAttribute> attribute,
	WaveSpawnPointVector spawnPoint
)
{
	m_waveEnemyAttributeList = attribute;

	m_spawnPointList = spawnPoint;
}

void WaveData::UpdateWaveData()
{
	//ウェーブステートの更新
	UpdateWaveState();
}

void WaveData::UpdateWaveState()
{
	switch (m_waveState)
	{
	case WaveData::EnWaveState::en_sandby:

		//待機

		break;
	case WaveData::EnWaveState::en_enemyGenerate:

		UpdateEnemyGenerateState();

		break;
	case WaveData::EnWaveState::en_waitTime:

		if (IsWaveEnemyDeadAll())
		{

		}

		break;
	default:
		break;
	}
}

void WaveData::UpdateEnemyGenerateState()
{
	//ランダムに選定されたスポーンポイントを取得
	std::vector<Vector3> spawnPoint = GetRandomSpawnPoint(m_waveMaxEnemyNum);

	std::vector<int> ganerateEnemyNumList = CalcEnemyDistribution(m_waveMaxEnemyNum, m_waveEnemyAttributeList.size());

	int num = 0;

	for (auto attributeNo :m_waveEnemyAttributeList)
	{
		//ココから生成、あとで座標も送るよう改造
		EnemyTankBatchGenerate(
			ganerateEnemyNumList[num],
			attributeNo,
			spawnPoint
		);

		num++;
	}

	m_waveState = EnWaveState::en_waitTime;
}

void WaveData::EnemyTankBatchGenerate(
	int generateNum,
	EnEnemyTankAttribute attribute,
	const std::vector<Vector3>& spawnPointList
)
{
	int batchGenerateNum = m_waveEnemyNum + generateNum;

	bool ganerateEnd = true;

	do
	{
		EnemyTankEntity* newTankPtr = nullptr;

		newTankPtr = EnemyTankManager::GetEnemyTankManagerInstance()
			->CreateNewEnemyTank(
				attribute,
				spawnPointList[m_waveEnemyNum]
			);

		m_waveSpawnEnemyList.push_back(newTankPtr);

		m_waveEnemyNum++;

		if (m_waveEnemyNum >= batchGenerateNum)
		{
			ganerateEnd = false;
		}

	} while (ganerateEnd);
}

std::vector<Vector3> WaveData::GetRandomSpawnPoint(int generateNum)
{
	//シャッフルして先頭から座標を取り出す
	std::random_device randomDevice;
	std::mt19937 gen(randomDevice());
	std::shuffle(m_spawnPointList.begin(), m_spawnPointList.end(), gen);

	//戻り値
	return std::vector<Vector3>(
		m_spawnPointList.begin(),
		m_spawnPointList.begin() + generateNum
	);
}

std::vector<int> WaveData::CalcEnemyDistribution(
	int totalEnemyNum,
	int enemyAttributeCount
)
{
	std::vector<int> count(enemyAttributeCount, 0);

	if (enemyAttributeCount <= 0 || totalEnemyNum <= 0)
	{
		return count;
	}

	int baseCount = totalEnemyNum / enemyAttributeCount;
	int remainder = totalEnemyNum % enemyAttributeCount;

	for (int listNo = 0; listNo < enemyAttributeCount; listNo++)
	{
		count[listNo] = baseCount + (listNo < remainder ? 1 : 0);
	}

	return count;
}

bool WaveData::IsWaveEnemyDeadAll()
{
	//マップの要素分回す
	for (auto itNo = m_waveSpawnEnemyList.begin();itNo != m_waveSpawnEnemyList.end();)
	{
		EnemyTankEntity* entity = *itNo;

		if (entity->GetDeleteFlag() == true)
		{
			itNo = m_waveSpawnEnemyList.erase(itNo);
		}
		else
		{
			itNo++;
		}
	}

	if (0 >= m_waveSpawnEnemyList.size())
	{
		return true;
	}

	return false;
}