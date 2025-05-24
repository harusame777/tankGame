#pragma once

#include "StateBase.h"

class EnemyTankEntity;
class EnemyTankAttributeBase;
class GamePlayer;
class EnemyAttackPoint;

namespace Const
{
	const float temporarySpeed = 50.0f;
}

class EnemyTankStateAttackMoveUpdate : public StateBase
{
	appState(EnemyTankStateAttackMoveUpdate);
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyTankStateAttackMoveUpdate(
		EnemyTankEntity* hostEnemyTank,
		EnemyTankAttributeBase* attribute
	)
	{
		m_hostEnemyTankEntity = hostEnemyTank;

		m_enemyTankAttribute = attribute;
	}
	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyTankStateAttackMoveUpdate() {};
	/// <summary>
	/// 初期化
	/// </summary>
	void Enter() override;
	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;
	/// <summary>
	/// 終了
	/// </summary>
	void Exit() override;
	/// <summary>
	/// ステート遷移
	/// </summary>
	/// <param name="request"></param>
	/// <returns></returns>
	bool RequestState(uint32_t& request) override;
	/// <summary>
	/// 範囲移動計算
	/// </summary>
	/// <param name="attackPointRadius"></param>
	/// <param name="enemyToAttackPointRadius"></param>
	/// <returns></returns>
	const Vector3& RangeMoveCalc(
		float attackPointRadius,
		float enemyToAttackPointRadius
	);
private:
	/// <summary>
	/// エネミータンクの属性
	/// </summary>
	EnemyTankAttributeBase* m_enemyTankAttribute = nullptr;
	/// <summary>
	/// このステートを保持しているエネミータンク
	/// </summary>
	EnemyTankEntity* m_hostEnemyTankEntity = nullptr;
};

