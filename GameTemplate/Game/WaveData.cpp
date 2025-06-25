#include "stdafx.h"		
#include "WaveData.h"

#include <random>
#include <algorithm>

#include "EnemyTankManager.h"
#include "WaveManager.h"

void WaveData::InitWaveData(
	std::vector<EnEnemyTankAttribute> attribute,
	WaveSpawnPointVector spawnPoint
)
{
	m_waveEnemyAttributeInfo = attribute;

	m_spawnPointList = spawnPoint;

}

void WaveData::StartWave(
	int spwanMaxNum,
	float enemyAddTime,
	int firstSpawn,
	int nextSpawn
)
{
	m_waveMaxEnemyNum = spwanMaxNum;

	m_enemyAddTime = enemyAddTime;

	m_firstSpawnEnemyNum = firstSpawn;

	m_nextSpawnEnemyNum = nextSpawn;

	InitAllEnemyInfo();

	m_waveState = EnWaveState::en_enemyGenerate;
}

//すべてのエネミーの情報を初期化する
void WaveData::InitAllEnemyInfo()
{
	//各種類の敵を均等に生成する
	const int countPerType 
		= m_waveMaxEnemyNum / m_waveEnemyAttributeInfo.size();
	//余り分
	const int remainder
		= m_waveMaxEnemyNum % m_waveEnemyAttributeInfo.size();
	//ループした数
	int loopCount = 0;

	for (const auto& type : m_waveEnemyAttributeInfo)
	{
		const int count = countPerType + (loopCount < remainder ? 1 : 0);

		for (int i = 0; i < count; i++)
		{
			EnemyInfo newData;

			newData.m_enemyAttribute = type;

			m_waveAllEnemyInfo.push_back(newData);
		}

		loopCount++;
	}

	//乱数初期化
	std::random_device randomDevice;
	std::mt19937 gen(randomDevice());

	//順番をシャッフルする
	std::shuffle(
		m_waveAllEnemyInfo.begin(),
		m_waveAllEnemyInfo.end(), 
		gen
	);
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

		//ウェーブ開始まで待機

		break;
	case WaveData::EnWaveState::en_enemyGenerate:

		//最初の敵群を生成
		EnemyTankSpwan(m_firstSpawnEnemyNum);

		//生成までの時間を初期化
		m_enemyAddTimer = m_enemyAddTime;

		//ステートを変更
		m_waveState = EnWaveState::en_waitTime;

		break;
	case WaveData::EnWaveState::en_waitTime:

		m_waveDatas.m_eventEndTime += g_gameTime->GetFrameDeltaTime();

		UpdateEnemyTankListDelete();

		//敵の追加処理
		if (m_enemyAddTimer < 0.0f &&
			IsRestActiveEnemy() == true)
		{
			//追加分の敵を生成
			EnemyTankSpwan(m_nextSpawnEnemyNum);

			//生成までの時間を初期化
			m_enemyAddTimer = m_enemyAddTime;
		}
		else
		{
			//生成までの時間を減少
			m_enemyAddTimer -= g_gameTime->GetFrameDeltaTime();
		}

		//敵がすべて倒されたらウェーブ終了処理へ
		if (IsEnemyAllDefeated() == true)
		{
			m_waveState = EnWaveState::en_end;
		}

		break;
	case WaveData::EnWaveState::en_end:

		WaveManager::GetWaveManagerInstance()->NotifyWaveCompleted(m_waveDatas);

		break;
	default:
		break;
	}
}

void WaveData::EnemyTankSpwan(int spwanNum)
{
	//生成数を調整
	int spwanMaxNum = GetSpwanMaxCount(spwanNum);

	//ランダムに選定されたスポーンポイントを取得
	std::vector<Vector3> spawnPointList = GetRandomSpawnPoint(spwanMaxNum);

	for (int loopNo = 0; loopNo < spwanMaxNum; loopNo++)
	{
		//初期化
		EnemyInfo newEnemyInfo;
		//属性を格納
		newEnemyInfo.m_enemyAttribute 
			= m_waveAllEnemyInfo[m_waveAliveEnemyCount].m_enemyAttribute;
		//エネミータンクを生成し、IDを格納
		newEnemyInfo.m_enemyId = EnemyTankManager::GetEnemyTankManagerInstance()
			->CreateNewEnemyTank(
				m_waveAllEnemyInfo[m_waveAliveEnemyCount].m_enemyAttribute,
				spawnPointList[loopNo]
			);
		//現在アクティブなエネミータンクの数を増やす
		m_waveAliveEnemyCount++;

		//配列に格納
		m_waveActiveEnemyList.push_back(newEnemyInfo);
	}
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

void WaveData::UpdateEnemyTankListDelete()
{
	//マップの要素分回す
	for (auto itNo = m_waveActiveEnemyList.begin(); itNo != m_waveActiveEnemyList.end();)
	{
		int enemyId = itNo->m_enemyId;

		//このエネミータンクが削除フラグを立てているかどうかを調べる
		if (EnemyTankManager::GetEnemyTankManagerInstance()
			->GetIdEnemyTankDeleteFlag(enemyId) == true)
		{
			//配列から削除
			itNo = m_waveActiveEnemyList.erase(itNo);
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