#pragma once

#include "StateBase.h"

class EnemyTankEntity;
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
		GamePlayer* gamePlayerPtr
	)
	{
		m_hostEnemyTankEntity = hostEnemyTank;

		m_player = gamePlayerPtr;
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
	enum class CrossState
	{
		//横切り計算
		en_crossCalc,
		//横切り更新
		en_crossUpdate,
	};
	/// <summary>
	/// 範囲から外れた秒数
	/// </summary>
	float m_rangeOutTime = 0.0f;
	/// <summary>
	/// 移動方向
	/// </summary>
	Vector3 m_moveDir = Vector3::Zero;
	/// <summary>
	/// このステートを保持しているエネミータンク
	/// </summary>
	EnemyTankEntity* m_hostEnemyTankEntity = nullptr;
	/// <summary>
	/// ゲームプレイヤーのインスタンス
	/// </summary>
	GamePlayer* m_player = nullptr;
	/// <summary>
	/// 現在追っているアタックポイント
	/// </summary>
	EnemyAttackPoint* m_attackPoint = nullptr;
	/// <summary>
	/// 横切り計算
	/// </summary>
	CrossState m_crossState = CrossState::en_crossCalc;
};

