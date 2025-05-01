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
	Cannonball_001_Normal(CannonballEntity* cannonball) : CannonballAttributeBase(cannonball){}
	/// <summary>
	/// 移動計算
	/// </summary>
	void Calc() override;
	/// <summary>
	/// 衝突時アクション
	/// </summary>
	void HitAction() override;
private:
	/// <summary>
	/// 変数登録実行用
	/// </summary>
	static bool m_attributeRegistered;
	/// <summary>
	/// 初期化関数登録処理
	/// </summary>
	bool m_attributeRegistered = [] {
		CannonballAttributeRegistry::registerFactory(EnCannonballAttribute::en_normal, []() {
			return std::make_unique<Cannonball_001_Normal>();
		});	
		return true;
	}();
};

