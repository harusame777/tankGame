#pragma once

class EnemyTankEntity;

class EnemyTankManager
{
private:
	/// <summary>
	/// インスタンス
	/// </summary>
	static EnemyTankManager* m_enemyTankManagerInstance;
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyTankManager() {};
	/// <summary>
	/// コピー禁止
	/// </summary>
	/// <param name=""></param>
	EnemyTankManager(const EnemyTankManager&) = delete;
	/// <summary>
	/// 代入禁止
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	EnemyTankManager& operator = (const EnemyTankManager&) = delete;
public:
	struct EnemyTankData
	{
		/// <summary>
		/// 敵タンクポインタ
		/// </summary>
		EnemyTankEntity* m_enemyTankPtr = nullptr;
		/// <summary>
		/// デリートフラグ
		/// </summary>
		bool m_deleteFlag = false;
	};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyTankManager() {};
	/// <summary>
	/// インスタンス作成、または取得	
	/// </summary>
	/// <returns></returns>
	static EnemyTankManager* GetTankShellsManagerInstance()
	{
		if (m_enemyTankManagerInstance == nullptr)
		{
			m_enemyTankManagerInstance = new EnemyTankManager();
		}

		return m_enemyTankManagerInstance;
	}
	/// <summary>
	/// 敵タンクマネージャー初期化
	/// </summary>
	void InitEnemyTankManager();
	/// <summary>
	/// 敵タンクマネージャークラス更新
	/// </summary>
	void UpdateEnemyTankManager();

	void CreateNewEnemyTank();
	/// <summary>
	/// 敵タンクリスト
	/// </summary>
	std::vector<EnemyTankData> m_enemyTankList;
};

