#include "stdafx.h"		int enemyNum

#include "WaveData.h"

#include "EnemyTankManager.h"
#include "EnemyTankEntity.h"

void WaveData::InitWaveData(
	int enemyNum
)
{
	
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
		break;
	default:
		break;
	}
}

void WaveData::UpdateEnemyGenerateState()
{
	for (auto attributeNo :m_waveEnemyAttributeList)
	{
		//ココから生成、あとで座標も送るよう改造
		EnemyTankBatchGenerate(
			3,
			attributeNo
		);
	}
}

void WaveData::EnemyTankBatchGenerate(
	int generateNum,
	EnEnemyTankAttribute attribute
)
{
	for (int No = 0; No > generateNum; ++No)
	{
		//ココには座標指定のプログラムを入れる

		EnemyTankManager::GetEnemyTankManagerInstance()
			->CreateNewEnemyTank(
				attribute,

			);

	}
}