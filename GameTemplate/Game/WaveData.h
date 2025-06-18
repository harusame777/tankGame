#pragma once

#include "EnemyTankAttribute.h"
#include "WaveSpawnPointRegistry.h"

#include"EnemyTankEntity.h"

class WaveData
{
public:
	/// <summary>
	/// ウェーブ終了イベントを表す構造体です。
	/// </summary>
	struct WaveEndEvent
	{
		/// <summary>
		/// ウェーブ終了までの時間
		/// </summary>
		float m_eventEndTime = 0.0f;
	};
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
	void StartWave()
	{
		m_waveState = EnWaveState::en_enemyGenerate;
	}
	/// <summary>
	/// このウェーブの最大スポーン数を設定
	/// </summary>
	/// <param name="num"></param>
	void SetEnemySpawnMaxNum(int num)
	{
		m_waveMaxEnemyNum = num;
	}
	/// <summary>
	/// 敵再出現までの時間を設定
	/// </summary>
	/// <param name="time"></param>
	void SetEnemyReappearanceTime(float time)
	{
		m_enemyReapperanceTimer = time;
	}
	/// <summary>
	/// ウェーブデータ更新
	/// </summary>
	void UpdateWaveData();
private: 
	/// <summary>
	/// ウェーブステートの更新
	/// </summary>
	void UpdateWaveState();
	/// <summary>
	/// エネミータンクの生成関数
	/// </summary>
	void UpdateEnemyGenerateState();
	/// <summary>
	/// エネミーを属性を参考に作成する
	/// </summary>
	/// <param name="attribute"></param>
	/// <returns></returns>
	void EnemyTankBatchGenerate(
		int generateNum,
		EnEnemyTankAttribute attribute,
		const std::vector<Vector3>& spawnPointList
	);
	/// <summary>
	/// ランダムなスポーン地点の座標を取得します。
	/// </summary>
	/// <returns>ランダムに選ばれたスポーン地点を表す Vector3 型の座標。</returns>
	std::vector<Vector3> GetRandomSpawnPoint(int generateNum);
	/// <summary>
	/// 指定された敵の総数と属性数に基づいて、各属性ごとの敵の分布を計算します。
	/// </summary>
	/// <param name="totalEnemyNum">分配する敵の総数。</param>
	/// <param name="enemyAttributeCount">敵属性の種類数。</param>
	/// <returns>各属性ごとの敵の数を格納した std::vector<int>。</returns>
	std::vector<int> CalcEnemyDistribution(
		int totalEnemyNum,
		int enemyAttributeCount
	);
	/// <summary>
	/// すべてのウェーブの敵が倒されたかどうかを判定します。
	/// </summary>
	/// <returns>すべてのウェーブの敵が倒されていれば true、そうでなければ false を返します。</returns>
	bool IsWaveEnemyDeadAll();
	/// <summary>
	/// ウェーブのステート
	/// </summary>
	EnWaveState m_waveState = EnWaveState::en_sandby;
	/// <summary>
	/// このウェーブのエネミータンクの数
	/// </summary>
	int m_waveEnemyNum = 0;
	/// <summary>
	/// このウェーブの最大のエネミータンクの数
	/// </summary>
	int m_waveMaxEnemyNum = 0;
	/// <summary>
	/// 敵再出現までの時間
	/// </summary>
	float m_enemyReapperanceTimer = 0.0f;
	/// <summary>
	/// このウェーブに出現する敵種類のリスト
	/// </summary>
	std::vector<EnEnemyTankAttribute> m_waveEnemyAttributeList;
	/// <summary>
	/// 敵戦車エンティティのリストを格納するベクターです。
	/// </summary>
	std::vector<EnemyTankEntity*> m_waveSpawnEnemyList;
	/// <summary>
	/// ウェーブのスポーンポイントのリストを格納する変数です。
	/// </summary>
	WaveSpawnPointVector m_spawnPointList;
};

