#pragma once

class EnemyAttackPoint;
class EnemyTankEntity;

class EnemyAttackPointManager
{
private:
	/// <summary>
	/// インスタンス
	/// </summary>
	static EnemyAttackPointManager* m_enemyAttackPointManagerInstance;
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyAttackPointManager() {};
	/// <summary>
	/// コピー禁止
	/// </summary>
	/// <param name=""></param>
	EnemyAttackPointManager(const EnemyAttackPointManager&) = delete;
	/// <summary>
	/// 代入禁止
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	EnemyAttackPointManager& operator = (const EnemyAttackPointManager&) = delete;
public:

	using AttackPointComponent = EnemyAttackPoint;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyAttackPointManager() {};
	/// <summary>
	/// インスタンス作成、または取得	
	/// </summary>
	/// <returns></returns>
	static EnemyAttackPointManager* GetTankShellsManagerInstance()
	{
		if (m_enemyAttackPointManagerInstance == nullptr)
		{
			m_enemyAttackPointManagerInstance = new EnemyAttackPointManager();
		}

		return m_enemyAttackPointManagerInstance;
	}
	/// <summary>
	/// 新しいアタックポイントを生成
	/// </summary>
	/// <param name="followCenterPoint"></param>
	/// <param name="pointTarGetDistance"></param>
	/// <param name="pointNum"></param>
	void CreateEnemyAttackPoints(
		Vector3& followCenterPoint,
		float pointTarGetDistance,
		int pointNum
	);
	/// <summary>
	/// アタックポイント位置更新
	/// </summary>
	void UpdateEnemyAttackPoints();
	/// <summary>
	/// 初期化
	/// </summary>
	void InitEnemyAttackPointManager();
	/// <summary>
	/// 更新
	/// </summary>
	void UpdateEnemyAttackPointManager();
	/// <summary>
	/// 引数のエネミーから一番近いエネミーを探す
	/// </summary>
	/// <param name="searchEnemyTank"></param>
	/// <returns></returns>
	EnemyAttackPoint* GetEnemyNearAttackPoint(EnemyTankEntity* searchEnemyTank);
	/// <summary>
	/// アタックポイントの使用終了を知らせる
	/// </summary>
	/// <param name="enemyTank"></param>
	void EndofUseAttackPoint(EnemyTankEntity* enemyTank);
private:
	struct EnemyAttackPointData
	{
		/// <summary>
		/// アタックポイント
		/// </summary>
		std::shared_ptr<EnemyAttackPoint> m_attackPointPtr;
		/// <summary>
		/// エネミータンク
		/// </summary>
		EnemyTankEntity* m_enemyTankEntityPtr = nullptr;
	};
	/// <summary>
	/// 追従させる中心点位置
	/// </summary>
	Vector3* m_followCenterPoint = nullptr;
	/// <summary>
	/// アタックポイントまでの距離
	/// </summary>
	float m_pointTargetDistance = 0.0f;
	/// <summary>
	/// エネミーアタックポイントリスト
	/// </summary>
	std::vector<EnemyAttackPointData> m_enemyAttackPointList;
};

