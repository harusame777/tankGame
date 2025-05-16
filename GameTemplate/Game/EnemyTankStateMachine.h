#pragma once

#include "StateMachineBase.h"

class EnemyTankEntity;

class EnemyTankStateMachine : public StateMachineBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyTankStateMachine(){}
	/// <summary>
	/// アップデート関数
	/// </summary>
	void Update() override;
	/// <summary>
	/// ホストエネミーを登録
	/// </summary>
	/// <param name="hostEnemyTank"></param>
	void SetHostEnemyTank(EnemyTankEntity* hostEnemyTank)
	{
		m_hostEnemyTankEntity = hostEnemyTank;
	}
private:
	/// <summary>
	/// このステートマシンを保持しているエネミータンク
	/// </summary>
	EnemyTankEntity* m_hostEnemyTankEntity = nullptr;
};

