#pragma once

#include "EnemyTankAttributeBase.h"

class EnemyTank_001_Normal : public EnemyTankAttributeBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyTank_001_Normal() {};
	/// <summary>
	/// 属性初期化関数
	/// </summary>
	void InitEnemyTankAttributeData(
		GamePlayer* m_player,
		EnemyTankEntity* hostTank
	) override;
	/// <summary>
	/// 削除処理関数
	/// </summary>
	void DeleteProcessing() override;
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
	/// 範囲
	/// </summary>
	bool IsAttackPointInRadius();
private:
	/// <summary>
	/// 登録実行用
	/// </summary>
	static bool m_attributeRegistered;
	/// <summary>
	/// 移動方向
	/// </summary>
	Vector3 m_moveDirection = Vector3::Zero;
};

