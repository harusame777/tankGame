#pragma once

using WaveSpawnPointVector = std::vector<Vector3>;

class WaveSpawnPointRegistry
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	WaveSpawnPointRegistry() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~WaveSpawnPointRegistry() {};
	/// <summary>
	/// ウェーブスポーンポイントのレジストリを初期化します。
	/// </summary>
	void InitWaveSpawnPointRegistry();
	/// <summary>
	/// ウェーブのスポーンポイントのベクトルを取得します。
	/// </summary>
	/// <returns>Vector3型のstd::vector。各要素はウェーブのスポーンポイントを表します。</returns>
	std::vector<Vector3> GetWaveSpawnPointVector() const
	{
		return m_spawnPointPosList;
	}
private:
	/// <summary>
	/// スポーンポイントの位置を格納するVector3のリストです。
	/// </summary>
	std::vector<Vector3> m_spawnPointPosList;
};

 