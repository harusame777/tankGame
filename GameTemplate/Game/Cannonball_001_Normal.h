#pragma once

#include "CannonballAttributeBase.h"
#include "CannonballAttribute.h"

class CannonballAttributeRegistry;

class Cannonball_001_Normal : public CannonballAttributeBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="cannonball"></param>
	Cannonball_001_Normal() {};
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

