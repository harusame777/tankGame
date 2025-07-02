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
	//遠距離
	en_FarAttackPoint,
	//種類数
	en_UseAttackPointRangeCount
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
	/// 攻撃ポイントの半径と終了半径、および使用範囲を初期化します。
	/// </summary>
	/// <param name="attackPointRadius">攻撃ポイントの初期半径。</param>
	/// <param name="attackEndRadius">攻撃ポイントの終了時の半径。</param>
	/// <param name="useRange">攻撃ポイント範囲の使用方法を指定する列挙型。</param>
	void InitAttackPointRadius(
		float attackPointRadius,
		float attackEndRadius,
		EnUseAttackPointRange useRange
	);
	/// <summary>
	/// 敵戦車の攻撃ポイントを作成します。
	/// </summary>
	/// <param name="enemyTankId">攻撃ポイントを作成する対象の敵戦車のID。</param>
	/// <param name="useRange">使用する攻撃ポイントの範囲を指定するEnUseAttackPointRange型の値。</param>
	void CreateEnemyAttackPoint(
		int enemyTankId,
		const Vector3& enemyPos,
		EnUseAttackPointRange useRange 
	);
	/// <summary>
	/// 攻撃ポイントの半径を更新します。
	/// </summary>
	/// <param name="followPosition">追従する位置を表す3次元ベクトル。</param>
	/// <param name="useRange">使用する攻撃ポイントの範囲を指定する列挙型。</param>
	void UpdateAttackPointRadius(
		const Vector3& followPosition,
		EnUseAttackPointRange useRange
	);
	/// <summary>
	/// 敵戦車の攻撃ポイントを更新します。
	/// </summary>
	/// <param name="enemyTankId">攻撃ポイントを更新する対象の敵戦車のID。</param>
	/// <param name="useEnemyPos">新しい攻撃ポイントとして使用する敵戦車の位置ベクトル。</param>
	void UpdateAttackPoint(
		int enemyTankId,
		const Vector3& useEnemyPos,
		EnUseAttackPointRange useRange
	);
	/// <summary>
	/// 初期化
	/// </summary>
	void InitEnemyAttackPointManager();
	/// <summary>
	/// 更新
	/// </summary>
	void UpdateEnemyAttackPointManager();
	/// <summary>
	/// 指定された敵戦車IDと使用範囲に基づいて、攻撃ポイントの位置を取得します。
	/// </summary>
	/// <param name="enemyTankId">攻撃ポイントの位置を取得する対象の敵戦車のID。</param>
	/// <param name="useRange">攻撃ポイントの検索に使用する範囲を指定する列挙型。</param>
	/// <returns>攻撃ポイントの位置を表すVector3型の定数参照。</returns>
	const Vector3& GetEnemyIdAttackPointPosition(
		int enemyTankId,
		EnUseAttackPointRange useRange
	);
	/// <summary>
	/// 指定した敵タンクIDが攻撃ポイントにいるかどうかを判定します。
	/// </summary>
	/// <param name="enemyTankId">判定対象の敵タンクのID。</param>
	/// <param name="enemyPos">敵タンクの現在位置（3次元ベクトル）。</param>
	/// <param name="useRange">使用する攻撃ポイントの範囲。</param>
	/// <returns>敵タンクが攻撃ポイントにいる場合はtrue、そうでない場合はfalseを返します。</returns>
	bool IsIdEnemyAtAttackPoint(
		int enemyTankId,
		const Vector3& enemyPos,
		EnUseAttackPointRange useRange
	);
	/// <summary>
	/// 指定した敵IDが攻撃ポイントの半径内にいるかどうかを判定します。
	/// </summary>
	/// <param name="enemyTankId">判定対象となる敵戦車のID。</param>
	/// <param name="enemyPos">敵戦車の現在位置（3次元ベクトル）。</param>
	/// <param name="useRange">使用する攻撃ポイントの範囲。</param>
	/// <returns>敵IDが攻撃ポイントの半径内にいる場合はtrue、そうでない場合はfalseを返します。</returns>
	bool IsIdEnemyInAttackPointRadius(
		int enemyTankId,
		const Vector3& enemyPos,
		EnUseAttackPointRange useRange
	);
	/// <summary>
	/// 指定した敵IDが攻撃終了半径内にいるかどうかを判定します。
	/// </summary>
	/// <param name="enemyTankId">判定対象となる敵戦車のID。</param>
	/// <param name="enemyPos">敵戦車の現在位置（3次元ベクトル）。</param>
	/// <param name="useRange">使用する攻撃ポイントの範囲。</param>
	/// <returns>敵IDが攻撃終了半径内にいる場合はtrue、そうでない場合はfalse。</returns>
	bool IsIdEnemyInAttackEndRadius(
		int enemyTankId,
		const Vector3& enemyPos,
		EnUseAttackPointRange useRange
	);
	/// <summary>
	/// アタックポイントの使用終了を知らせる
	/// </summary>
	/// <param name="enemyTank"></param>
	void EndUseAttackPoint(
		int enemyTankId,
		EnUseAttackPointRange useRange
	);
private:
	/// <summary>
	/// 敵の攻撃ポイント情報を管理する構造体です。
	/// </summary>
	struct AttackPointListInfo
	{
		/// <summary>
		/// 敵の攻撃ポイントを管理するためのマップです。
		/// </summary>
		std::unordered_map<int,std::shared_ptr<EnemyAttackPoint>> m_attackPointMap;
		/// <summary>
		/// 攻撃ポイントの半径を表す浮動小数点型の変数です。
		/// </summary>
		float m_attackPointRadius = 0.0f;
		/// <summary>
		/// 攻撃の終了半径を表す浮動小数点型の変数です。
		/// </summary>
		float m_attackEndRadius = 0.0f;	
		/// <summary>
		/// 追従位置
		/// </summary>
		Vector3 m_followPosition = Vector3::Zero;
	};

	const Vector3& CalcAttackPointPosition(
		const Vector3& followPosition,
		const Vector3& attackPointPos,
		const Vector3& useEntityPos,
		float attackPointRadius,
		float attackEndRadius
	);
	/// <summary>
	/// aPositionがbPositionからbRadius以内にあるかどうかを判定します。
	/// </summary>
	/// <param name="aPosition">判定対象となる位置ベクトル。</param>
	/// <param name="bPosition">中心となる位置ベクトル。</param>
	/// <param name="bRadius">bPositionを中心とした半径。</param>
	/// <returns>aPositionがbPositionからbRadius以内であればtrue、そうでなければfalseを返します。</returns>
	bool IsAPositionInBRadius(
		const Vector3& aPosition, 
		const Vector3& bPosition, 
		float bRadius
	);
	/// <summary>
	/// 攻撃ポイント情報を格納するための連想配列です。
	/// </summary>
	std::unordered_map<EnUseAttackPointRange, AttackPointListInfo> m_attackPointInfoMap;

};

