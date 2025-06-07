#pragma once

class EnemyAttackPoint;
class EnemyTankEntity;

/// <summary>
/// 攻撃ポイントの範囲を表す列挙型です。
/// </summary>
enum EnUseAttackPointRange
{
	//近距離
	en_NearAttackPoint,
	//中距離
	en_MiddleAttackPoint,
};

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
	static EnemyAttackPointManager* GetEnemyAttackPointManagerInstance()
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
		float pointAttackRadius,
		int pointNum,
		const EnUseAttackPointRange useRange
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
	EnemyAttackPoint* GetEnemyAttackPoint(
		EnemyTankEntity* searchEnemyTank,
		const EnUseAttackPointRange useRange
	);
	/// <summary>
	/// 同じエネミータンクのアドレスを持っている近距離のアタックポイントを取得する
	/// </summary>
	/// <param name="searchEnemyTank"></param>
	/// <returns></returns>
	EnemyAttackPoint* GetSameEnemyAddressAttackPoint(
		EnemyTankEntity* searchEnemyTank,
		const EnUseAttackPointRange useRange
	);
	/// <summary>
	/// アタックポイントの使用終了を知らせる
	/// </summary>
	/// <param name="enemyTank"></param>
	void EndofUseAttackPoint(
		EnemyTankEntity* enemyTank,
		const EnUseAttackPointRange useRange
	);
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
		/// <summary>
		/// アタックポイントまでの距離
		/// </summary>
		float m_pointTargetDistance = 0.0f;
	};
	/// <summary>
	/// 使用する距離のアタックポイントリストを取得
	/// </summary>
	std::vector<EnemyAttackPointData>* GetUseAttackPointRangeList(const EnUseAttackPointRange useRange);
	/// <summary>
	/// 追従させる中心点位置
	/// </summary>
	Vector3* m_followCenterPoint = nullptr;
	/// <summary>
	/// エネミーの近距離アタックポイントリスト
	/// </summary>
	std::vector<EnemyAttackPointData> m_enemyNearAttackPointList;
	/// <summary>
	/// エネミーの中距離アタックポイントリスト
	/// </summary>
	std::vector<EnemyAttackPointData> m_enemyMiddleAttackPointList;
};

