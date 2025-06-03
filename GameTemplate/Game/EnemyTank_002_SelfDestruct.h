#pragma once

#include "EnemyTankAttributeBase.h"
#include "TankShellsManager.h"

class EnemyTank_002_SelfDestruct : public EnemyTankAttributeBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyTank_002_SelfDestruct() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyTank_002_SelfDestruct() {};
	/// <summary>
	/// 属性初期化関数
	/// </summary>
	void InitEnemyTankAttributeData(
		GamePlayer* m_player,
		EnemyTankEntity* hostTank
	) override;
	/// <summary>
	/// 射撃処理
	/// </summary>
	void FireProcessing() override;
	/// <summary>
	/// 削除処理関数
	/// </summary>
	bool DeleteProcessing() override;
	/// <summary>
	/// 追跡処理初期化
	/// </summary>
	void EnterTracking() override;
	/// <summary>
	/// エネミーの追跡処理
	/// </summary>
	const Vector3& UpdateTracking() override;
	/// <summary>
	/// エネミーの追跡ステート変更処理
	/// </summary>
	/// <param name="request"></param>
	/// <returns></returns>
	bool RequestStateTracking(uint32_t& request) override;
	/// <summary>
	/// 追跡終了
	/// </summary>
	void EndTracking() override;
	/// <summary>
	/// 攻撃移動モードに入ります。
	/// </summary>
	void EnterAttackMove() override;
	/// <summary>
	/// エネミーの攻撃行動処理
	/// </summary>
	const Vector3& UpdateAttackMove() override;
	/// <summary>
	/// エネミーの攻撃行動ステート変更処理
	/// </summary>
	/// <param name="request"></param>
	/// <returns></returns>
	bool RequestStateAttackMove(uint32_t& request) override;
	/// <summary>
	/// 攻撃動作終了
	/// </summary>
	void EndAttackMove() override;
	/// <summary>
	/// 固有処理初期化
	/// </summary>
	void EnterUnique() override;
	/// <summary>
	/// 固有処理更新
	/// </summary>
	/// <returns></returns>
	const Vector3& UpdateUnique() override;
	/// <summary>
	/// 固有処理ステート遷移
	/// </summary>
	/// <param name="request"></param>
	/// <returns></returns>
	bool RequestStateUnique(uint32_t& request) override;
	/// <summary>
	/// 固有処理終了
	/// </summary>
	void EndUnique() override;
	/// <summary>
	/// 自爆可能な距離にいるかどうかを返します。
	/// </summary>
	/// <returns></returns>
	bool IsHostTankInSelfDestructRange();
	/// <summary>
	/// 自爆処理更新
	/// </summary>
	void UpdateSelfDestruct();
private:
	/// <summary>
	/// 登録実行用
	/// </summary>
	static bool m_attributeRegistered;
	/// <summary>
	/// 移動方向
	/// </summary>
	Vector3 m_moveDirection = Vector3::Zero;
	/// <summary>
	/// 自爆までのタイマー
	/// </summary>
	float m_selfDestructTimer = 0.0f; 
	/// <summary>
	/// 自爆中かどうか
	/// </summary>
	bool m_isSelfDestruct = false; 
	/// <summary>
	/// 自爆当たり判定
	/// </summary>
	std::shared_ptr<CollisionObject> m_selfDestructCollision = nullptr;
	/// <summary>
	/// 自爆終了までのタイマー
	/// </summary>
	float m_selfDestructEndTimer = 0.0f;
	/// <summary>
	/// 自爆遅延タイマー
	/// </summary>
	float m_selfDestructDelayTimer = 0.0f; 
};

