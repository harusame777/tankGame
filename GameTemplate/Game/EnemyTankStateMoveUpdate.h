#pragma once

#include "StateBase.h"

class EnemyTankEntity;

class EnemyTankStateMoveUpdate : public StateBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyTankStateMoveUpdate(EnemyTankEntity* hostEnemyTank);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyTankStateMoveUpdate() {};
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
private:
	/// <summary>
	/// このステートを保持しているエネミータンク
	/// </summary>
	EnemyTankEntity* m_hostEnemyTankEntity;
};

