#pragma once

#include "StateMachineBase.h"

class EnemyTankEntity;

class EnemyTankStateMachine : public StateMachineBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyTankStateMachine(EnemyTankEntity* hostEnemyTank)
	{
		m_hostEnemyTankEntity = hostEnemyTank;
	}
	/// <summary>
	/// アップデート関数
	/// </summary>
	void Update() override;
private:
	/// <summary>
	/// このステートマシンを保持しているエネミータンク
	/// </summary>
	EnemyTankEntity* m_hostEnemyTankEntity = nullptr;
};

