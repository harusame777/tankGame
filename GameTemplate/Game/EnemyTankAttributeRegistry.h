#pragma once

#include "EnemyTankAttribute.h"

class EnemyTankAttributeBase;

class EnemyTankAttributeRegistry
{
public:
	/// <summary>
	/// 登録に使用する命名定義
	/// </summary>
	using EnemyTankAttributeFunc = std::function<std::shared_ptr<EnemyTankAttributeBase>()>;
	/// <summary>
	/// 初期化登録関数
	/// </summary>
	/// <param name="attribute"></param>
	/// <param name="func"></param>
	static void EnemyTankRegisterFactory(EnEnemyTankAttribute attribute, EnemyTankAttributeFunc func)
	{
		GetEnemyTankAttributeMap()[attribute] = std::move(func);
	}
	/// <summary>
	/// 属性を作成し、その属性のポインタを返す
	/// </summary>
	/// <param name="attribute"></param>
	/// <returns></returns>
	static std::shared_ptr<EnemyTankAttributeBase> CreateEnemyTankAttribute(EnEnemyTankAttribute attribute)
	{
		//ハッシュマップを取得する
		auto& map = GetEnemyTankAttributeMap();
		//ハッシュマップから属性のポインタを取得
		auto it = map.find(attribute);
		//it内に正しく属性のポインタが登録されていれば
		if (it != map.end())
		{
			//属性のポインタを返す
			return it->second();
		}
		//登録されていなければ
		K2_ASSERT(false, "想定外");
		return nullptr;
	}
private:
	/// <summary>
	/// ハッシュマップ作製関数
	/// </summary>
	/// <returns></returns>
	static std::unordered_map<EnEnemyTankAttribute, EnemyTankAttributeFunc>& GetEnemyTankAttributeMap()
	{
		static std::unordered_map<EnEnemyTankAttribute, EnemyTankAttributeFunc> map;
		return map;
	}
};

