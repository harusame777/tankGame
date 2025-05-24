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
	/// 固有処理関数
	/// </summary>
	void UniqueProcessing() override;
	/// <summary>
	/// 削除処理関数
	/// </summary>
	void DeleteProcessing() override;
	/// <summary>
	/// エネミーの追跡処理
	/// </summary>
	const Vector3& TrackingAttribute( ) override;
	/// <summary>
	/// エネミーの追跡ステート変更処理
	/// </summary>
	/// <param name="request"></param>
	/// <returns></returns>
	bool RequestStateTrackingAttribute(uint32_t& request) override;
	/// <summary>
	/// エネミーの攻撃行動処理
	/// </summary>
	const Vector3& AttackMoveAttribute() override;
	/// <summary>
	/// エネミーの攻撃行動ステート変更処理
	/// </summary>
	/// <param name="request"></param>
	/// <returns></returns>
	bool RequestStateAttackMoveAttribute(uint32_t& request) override;
	/// <summary>
	/// 範囲
	/// </summary>
	bool IsAttackPointInRadius();
private:
	/// <summary>
	/// 登録実行用
	/// </summary>
	static bool m_attributeRegistered;
};

