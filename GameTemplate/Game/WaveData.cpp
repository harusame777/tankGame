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

		EnemyTankSpwanBatch();

		m_waveState = EnWaveState::en_waitTime;

		break;
	case WaveData::EnWaveState::en_waitTime:

		m_waveDatas.m_eventEndTime += g_gameTime->GetFrameDeltaTime();

		UpdateEnemyTankListDelete();

		if (IsWaveEnemyDeadAll())
		{
			m_waveState = EnWaveState::en_end;
		}

		if (IsWaveEnemyAddNum())
		{
			EnemyTankSpwanThreshold();
		}

		break;
	case WaveData::EnWaveState::en_end:

		EventManager::GetEventManagerInstance()->NotifyListeners(m_waveDatas);

		break;
	default:
		break;
	}
}

void WaveData::EnemyTankSpwanThreshold()
{
	std::vector<Vector3> spawnPointList = GetRandomSpawnPoint(WaveDataConstant::spawnAddThreshold);

	std::vector<int> ganerateEnemyNumList = CalcEnemyDistribution(
		WaveDataConstant::spawnAddThreshold,
		m_waveEnemyAttributeList.size()
	);
	
	int num = 0;

	for (auto attributeNo : m_waveEnemyAttributeList)
	{
		//ココから生成、あとで座標も送るよう改造
		EnemyTankBatchGenerate(
			ganerateEnemyNumList[num],
			attributeNo,
			spawnPointList
		);

		num++;
	}
}

void WaveData::EnemyTankSpwanBatch()
{
	//ランダムに選定されたスポーンポイントを取得
	std::vector<Vector3> spawnPointList = GetRandomSpawnPoint(m_waveMaxEnemyNum);

	std::vector<int> ganerateEnemyNumList = CalcEnemyDistribution(
		WaveDataConstant::spawnOnceMaxNum,
		m_waveEnemyAttributeList.size()
	);

	int num = 0;

	for (auto attributeNo :m_waveEnemyAttributeList)
	{
		//ココから生成、あとで座標も送るよう改造
		EnemyTankBatchGenerate(
			ganerateEnemyNumList[num],
			attributeNo,
			spawnPointList
		);

		num++;
	}
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
		//EnemyTankEntity* newTankPtr = nullptr;

		EnemyTankManager::GetEnemyTankManagerInstance()
			->CreateNewEnemyTank(
				attribute,
				spawnPointList[m_waveEnemyNum]
			);

		//m_waveSpawnEnemyList.push_back(newTankPtr);

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

bool WaveData::IsWaveEnemyAddNum()
{
	//現在倒している敵数と現在の敵数の合計がウェーブに出現する敵の最大数を超えるならfalse
	if (m_waveDefeatedEnemyNum + m_waveEnemyNum >= m_waveMaxEnemyNum)
	{
		return false;
	}

	//現在の敵数が(一度に出現できる敵の数-敵の追加しきい値)以上であればtrue
	if (m_waveEnemyNum <= m_waveMaxEnemyNum - WaveDataConstant::spawnAddThreshold)
	{
		return true;
	}

	return false;
}

bool WaveData::IsWaveEnemyDeadAll()
{
	if (m_waveDefeatedEnemyNum >= m_waveMaxEnemyNum)
	{
		return true;
	}

	return false;
}

void WaveData::UpdateEnemyTankListDelete()
{
	//マップの要素分回す
	for (auto itNo = m_waveSpawnEnemyList.begin(); itNo != m_waveSpawnEnemyList.end();)
	{
		EnemyTankEntity* entity = *itNo;

		//このエネミータンクが削除フラグを立てているかどうかを調べる
		if (entity->GetDeleteFlag() == true)
		{
			//配列から削除
			itNo = m_waveSpawnEnemyList.erase(itNo);
			//ウェーブ内のエネミーの数を減らす
			m_waveEnemyNum--;
			//ウェーブ内の倒されたエネミーの数を増やす
			m_waveDefeatedEnemyNum++;
		}
		else
		{
			//次のイテレーターへ
			itNo++;
		}
	}
}