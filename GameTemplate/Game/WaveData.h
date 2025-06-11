#pragma once

#include "EnemyTankAttribute.h"

class EnemyTankEntity;

class WaveData
{
public:
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
		int enemyNum
	);
	/// <summary>
	/// 出現する敵のリストを登録
	/// </summary>
	/// <param name="setList"></param>
	void SetWaveAppearEnemyAttribute(std::vector<EnEnemyTankAttribute> setList)
	{
		m_waveEnemyAttributeList = setList;
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
		EnEnemyTankAttribute attribute
	);
	/// <summary>
	/// ウェーブのステート
	/// </summary>
	EnWaveState m_waveState = EnWaveState::en_sandby;
	/// <summary>
	/// このウェーブのエネミータンクの数
	/// </summary>
	int m_waveEnemyNum = 0;
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
	std::vector<EnemyTankEntity> m_waveSpawnEnemyList;

};

