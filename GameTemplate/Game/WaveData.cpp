#include "stdafx.h"		
#include "WaveData.h"

#include <random>
#include <algorithm>

#include "EnemyTankManager.h"
#include "WaveManager.h"
#include "EventManager.h"

void WaveData::InitWaveData(
	std::vector<EnEnemyTankAttribute> attribute,
	WaveSpawnPointVector spawnPoint
)
{
	//属性リストを登録
	m_waveEnemyAttributeInfo = attribute;
	//出現場所を登録
	m_spawnPointList = spawnPoint;
}

void WaveData::StartWave(
	int spwanMaxNum,
	float enemyAddTime,
	int firstSpawn,
	int nextSpawn
)
{
	//このウェーブで出現する敵の最大数
	m_waveMaxEnemyNum = spwanMaxNum;
	//敵追加までの時間
	m_enemyAddTime = enemyAddTime;
	//最初にウェーブに出現する敵の数
	m_firstSpawnEnemyNum = firstSpawn;
	//追加の際にウェーブに出現する敵の数
	m_nextSpawnEnemyNum = nextSpawn;
	//出現する敵のリストの初期化
	InitAllEnemyInfo();
	//ステートを生成ステートに
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

	//範囲for文で出現属性分繰り返し
	for (const auto& type : m_waveEnemyAttributeInfo)
	{
		//余り分の繰り返し回数を増加
		const int count = countPerType + (loopCount < remainder ? 1 : 0);

		//属性ごとの敵の情報を生成
		for (int i = 0; i < count; i++)
		{
			EnemyInfo newData;

			newData.m_enemyAttribute = type;

			m_waveAllEnemyInfo.push_back(newData);
		}

		//ループ回数増加
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

		//クリアまでにかかった時間計算
		m_waveDatas.m_eventEndTime += g_gameTime->GetFrameDeltaTime();

		//リスト削除処理
		UpdateEnemyTankListDelete();

		//敵の追加処理
		if (m_enemyAddTimer < 0.0f &&
			isAllEnemiesSpawned())
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

		//ウェーブが終了したことをマネージャーに連絡
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
			= m_waveAllEnemyInfo[m_waveSpawnedEnemyCount].m_enemyAttribute;
		//エネミータンクを生成し、IDを格納
		newEnemyInfo.m_enemyId = EnemyTankManager::GetEnemyTankManagerInstance()
			->CreateNewEnemyTank(
				m_waveAllEnemyInfo[m_waveSpawnedEnemyCount].m_enemyAttribute,
				spawnPointList[loopNo]
			);
		//現在アクティブなエネミータンクの数を増やす
		m_waveSpawnedEnemyCount++;

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
			//ウェーブ内の残りエネミー数を格納
			m_eventEnemyDead.m_enemyRemainingNum = m_waveActiveEnemyList.size();
			//イベントを通知
			EventManager::GetEventManagerInstance()->NotifyListeners(m_eventEnemyDead);
		}
		else
		{
			//次のイテレーターへ
			itNo++;
		}
	}
}