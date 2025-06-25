#pragma once

#include "EnemyTankAttribute.h"
#include "WaveSpawnPointRegistry.h"
#include "EventManager.h"

#include"EnemyTankEntity.h"

/// <summary>
/// WaveDataConstant 定数を格納するための名前空間です。
/// </summary>
namespace WaveDataConstant
{
	/// <summary>
	/// 一度に生成できる最大数を表す変数です。
	/// </summary>
	const int spawnOnceMaxNum = 10;
	/// <summary>
	/// 追加のスポーンを許可するしきい値を表す定数です。
	/// </summary>
	const int spawnAddThreshold = 3;
	/// <summary>
	/// 敵を追加するための定数時間（秒単位）です。
	/// </summary>
	const float enemyAddTimeConstant = 15.0f;
};

/// <summary>
/// ウェーブ終了イベントを表す構造体です。
/// </summary>
struct WaveEndEvent : public EventManager::StructEventBase
{
	/// <summary>
	/// ウェーブ終了までの時間
	/// </summary>
	float m_eventEndTime = 0.0f;
};

class WaveData
{
public:
	/// <summary>
	/// 敵の出現や待機など、ウェーブの状態を表す列挙型です。
	/// </summary>
	enum class EnWaveState
	{
		//待機
		en_sandby,
		//敵生成
		en_enemyGenerate,
		//再出現待機
		en_waitTime,
		//終了
		en_end
	};
	/// <summary>
	/// コンストラクタ
	/// </summary>
	WaveData() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~WaveData() {};
	/// <summary>
	/// ウェーブデータの初期化関数
	/// </summary>
	void InitWaveData(
		std::vector<EnEnemyTankAttribute> attribute, 
		WaveSpawnPointVector spawnPoint
	);
	/// <summary>
	/// ウェーブを開始し、ウェーブ状態を敵生成に設定します。
	/// </summary>
	void StartWave(
		int spwanMaxNum,
		float enemyAddTime
	);
	/// <summary>
	/// このウェーブの最大スポーン数を設定
	/// </summary>
	/// <param name="num"></param>
	void SetEnemySpawnMaxNum(int num)
	{
		m_waveMaxEnemyNum = num;
	}
	/// <summary>
	/// ウェーブデータ更新
	/// </summary>
	void UpdateWaveData();
private: 
	/// <summary>
	/// 敵の情報を格納する構造体です。
	/// </summary>
	struct EnemyInfo
	{
		/// <summary>
		/// 敵のIDを格納する整数型のメンバー変数です。
		/// </summary>
		int m_enemyId = -1;
		/// <summary>
		/// 敵戦車の属性を表す変数を初期化します。
		/// </summary>
		EnEnemyTankAttribute m_enemyAttribute = EnEnemyTankAttribute::en_tankNormal;
	};
	/// <summary>
	/// すべての敵情報を初期化します。
	/// </summary>
	void InitAllEnemyInfo();
	/// <summary>
	/// ウェーブステートの更新
	/// </summary>
	void UpdateWaveState();
	/// <summary>
	/// エネミータンクの生成関数
	/// </summary>
	void EnemyTankSpwan(int spwanNum);
	/// <summary>
	/// すべての敵が倒されたかどうかを判定します。
	/// </summary>
	/// <returns>すべての敵が倒されていれば true、そうでなければ false を返します。</returns>
	bool IsEnemyAllDefeated()
	{
		int allEnemys = GetAllEnemyCount();

		if (m_waveDefeatedEnemyNum >= allEnemys)
		{
			return true;
		}

		return false;
	}
	/// <summary>
	/// アクティブな敵が残っているかどうかを判定します。
	/// </summary>
	/// <returns>アクティブな敵が残っていれば true、そうでなければ false を返します。</returns>
	bool IsRestActiveEnemy()
	{
		if (m_waveMaxEnemyNum <= m_waveAliveEnemyCount)
		{
			return false;
		}
		
		return true;
	}
	/// <summary>
	/// すべての敵の数を取得します。
	/// </summary>
	/// <returns>すべての敵の合計数を表す整数値。</returns>
	int GetAllEnemyCount() const
	{
		return m_waveAllEnemyInfo.size();
	}
	/// <summary>
	/// アクティブな敵の数を取得します。
	/// </summary>
	/// <returns>現在アクティブな敵の数。</returns>
	int GetActiveEnemyCount() const
	{
		return m_waveActiveEnemyList.size();
	}
	/// <summary>
	/// 指定されたスポーン数と残りの敵数に基づいて、1回のスポーンで最大何体の敵を出現させるかを計算します。
	/// </summary>
	/// <param name="SpwanNum">出現させたい敵の数。</param>
	/// <returns>1回のスポーンで出現可能な最大の敵数。</returns>
	int GetSpwanMaxCount(int SpwanNum) const
	{
		int allEnemys = GetAllEnemyCount();
		int activeEnemys = GetActiveEnemyCount();
		
		int restEnemys = allEnemys - activeEnemys;

		if (restEnemys <= SpwanNum)
		{
			if (WaveDataConstant::spawnOnceMaxNum < restEnemys)
			{
				return WaveDataConstant::spawnOnceMaxNum;
			}

			return restEnemys;
		}

		return SpwanNum;
	}
	/// <summary>
	/// ランダムなスポーン地点の座標を取得します。
	/// </summary>
	/// <returns>ランダムに選ばれたスポーン地点を表す Vector3 型の座標。</returns>
	std::vector<Vector3> GetRandomSpawnPoint(int generateNum);
	/// <summary>
	/// 敵戦車リストの削除処理を実行します。
	/// </summary>
	void UpdateEnemyTankListDelete();
	/// <summary>
	/// ウェーブのステート
	/// </summary>
	EnWaveState m_waveState = EnWaveState::en_sandby;
	/// <summary>
	/// このウェーブの最大のエネミータンクの数
	/// </summary>
	int m_waveMaxEnemyNum = 0;
	/// <summary>
	/// ウェーブ内で生存している敵の数を表す変数です。
	/// </summary>
	int m_waveAliveEnemyCount = 0;
	/// <summary>
	/// このウェーブの倒されたエネミータンクの数
	/// </summary>
	int m_waveDefeatedEnemyNum = 0;
	/// <summary>
	/// 敵の追加タイマーを表す浮動小数点型の変数です。
	/// </summary>
	float m_enemyAddTimer = 0.0f;
	/// <summary>
	/// 敵の追加時間を表す浮動小数点数型の変数です。
	/// </summary>
	float m_enemyAddTime = 0.0f;
	/// <summary>
	/// すべての敵の情報を格納するベクターです。
	/// </summary>
	std::vector<EnemyInfo> m_waveAllEnemyInfo;
	/// <summary>
	/// 敵戦車の属性情報を格納するベクターです。
	/// </summary>
	std::vector<EnEnemyTankAttribute> m_waveEnemyAttributeInfo;
	/// <summary>
	/// アクティブな敵の情報を格納するベクターです。
	/// </summary>
	std::vector<EnemyInfo> m_waveActiveEnemyList;
	/// <summary>
	/// ウェーブのスポーンポイントのリストを格納する変数です。
	/// </summary>
	WaveSpawnPointVector m_spawnPointList;
	/// <summary>
	/// WaveEndEvent 型の変数 m_waveDatas です。
	/// </summary>
	WaveEndEvent m_waveDatas;
};

