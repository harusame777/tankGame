#pragma once

#include "StateBase.h"

class EnemyTankEntity;
class EnemyTankAttributeBase;

class EnemyTankStateTrackingUpdate : public StateBase
{
	appState(EnemyTankStateTrackingUpdate);
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyTankStateTrackingUpdate(
		EnemyTankEntity* hostEnemyTank,
		EnemyTankAttributeBase* attribute
	)
	{
		m_hostEnemyTankEntity = hostEnemyTank;

		m_enemyTankAttribute = attribute;
	};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyTankStateTrackingUpdate() {};
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
	/// ホストエネミーを登録
	/// </summary>
	/// <param name="hostEnemyTank"></param>
	void SetHostEnemyTank(EnemyTankEntity* hostEnemyTank)
	{
		m_hostEnemyTankEntity = hostEnemyTank;
	}
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

