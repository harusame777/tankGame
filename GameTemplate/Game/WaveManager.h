#pragma once
#include "EnemyTankAttribute.h"

class WaveData;
class WaveSpawnPointRegistry;

class WaveManager
{
private:
	/// <summary>
	/// インスタンス
	/// </summary>
	static WaveManager* m_waveManagerInstance;
	/// <summary>
	/// コンストラクタ
	/// </summary>
	WaveManager() {};
	/// <summary>
	/// コピー禁止
	/// </summary>
	/// <param name=""></param>
	WaveManager(const WaveManager&) = delete;
	/// <summary>
	/// 代入禁止
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	WaveManager& operator = (const WaveManager&) = delete;
public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	~WaveManager() {};
	/// <summary>
	/// インスタンス作成、または取得	
	/// </summary>
	/// <returns></returns>
	static WaveManager* GetWaveManagerInstance()
	{
		if (m_waveManagerInstance == nullptr)
		{
			m_waveManagerInstance = new WaveManager();
		}

		return m_waveManagerInstance;
	}
	/// <summary>
	/// 初期化関数
	/// </summary>
	void InitWaveManager();
	/// <summary>
	/// 更新関数
	/// </summary>
	void UpdateWaveManager();
	/// <summary>
	/// 新しいウェーブデータを作成
	/// </summary>
	WaveData* CreateNewWaveData(
		int enemyAppearNum,
		float enemyReapperanceTime
	);
private:
	/// <summary>
	/// WaveSpawnPointRegistry 型のポインタ m_spawnPointRegistry を初期化します。
	/// </summary>
	WaveSpawnPointRegistry* m_spawnPointRegistry = nullptr;
	/// <summary>
	/// 指定された数のランダムな敵戦車属性を取得します。
	/// </summary>
	/// <param name="attributeCount">取得する敵戦車属性の数。</param>
	/// <returns>ランダムに選ばれた EnEnemyTankAttribute の std::vector。</returns>
	std::vector<EnEnemyTankAttribute> GetRandomEnemyAttribute(int attributeCount);
	/// <summary>
	/// ウェーブクリア数を保持する整数型の変数です。
	/// </summary>
	int m_waveClearNum = 0;
	/// <summary>
	/// このウェーブで出現するエネミーの最大数
	/// </summary>
	int m_waveMaxEnemyNum = 0;
	/// <summary>
	/// 現在のウェーブデータを指すポインタです。
	/// </summary>
	WaveData* m_nowWave = nullptr;
};

