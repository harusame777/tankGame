#pragma once

#include "TankShellsAttributeBase.h"
#include "TankShellsAttribute.h"

class TankShellsAttributeRegistry;

class TankShells_001_Normal : public TankShellsAttributeBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="cannonball"></param>
	TankShells_001_Normal() {};
	/// <summary>
	/// 初期化
	/// </summary>
	void InitData() override;
	/// <summary>
	/// 移動計算
	/// </summary>
	void MoveCalc() override;
	/// <summary>
	/// 衝突時アクション
	/// </summary>
	void HitAction() override;
private:
	/// <summary>
	/// 変数登録実行用
	/// </summary>
	static bool m_attributeRegistered;
};

