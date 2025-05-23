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
	void InitEnemyTankAttributeData() override;
	/// <summary>
	/// 固有処理関数
	/// </summary>
	void EnemyTankUniqueProcessing() override;
	/// <summary>
	/// 削除処理関数
	/// </summary>
	void EnemyTankDeleteProcessing() override;
private:
	/// <summary>
	/// 登録実行用
	/// </summary>
	static bool m_attributeRegistered;
};

