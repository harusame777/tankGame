#pragma once

#include "TankShellsAttributeBase.h"
#include "TankShellsAttribute.h"

class TankShellsAttributeRegistry;

namespace TankShells_001_Constant
{
	
	const float speed = 100.0f;

}

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
	void InitData(
		CollisionObject* collsion,
		const char* name
	) override;
	/// <summary>
	/// 移動計算
	/// </summary>
	void GunnerIsPlayerMoveCalc() override;
	/// <summary>
	/// 
	/// </summary>
	void GunnerIsEnemyMoveCalc() override;
	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <returns></returns>
	bool HitCheck() override;
	/// <summary>
	/// 衝突時アクション
	/// </summary>
	void HitAction() override;
	/// <summary>
	/// 削除時処理
	/// </summary>
	void DeleteTankShellsAttributeAction() override;
private:
	/// <summary>
	/// 変数登録実行用
	/// </summary>
	static bool m_attributeRegistered;
};

