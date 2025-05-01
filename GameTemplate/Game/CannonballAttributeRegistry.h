#pragma once

#include "CannonballAttribute.h"

class CannonballAttributeBase;

class CannonballAttributeRegistry
{
public:
	/// <summary>
	/// 移動計算関数
	/// </summary>
	using CannonballMoveCalcFunc = std::function<std::shared_ptr<CannonballAttributeBase>()>;
	/// <summary>
	/// 初期化登録
	/// </summary>
	/// <param name="attribute"></param>
	/// <param name="func"></param>
	static void registerFactory(EnCannonballAttribute attribute, CannonballMoveCalcFunc func)
	{
		GetAttributeMap()[attribute] = std::move(func);
	}
	/// <summary>
	/// 属性を作成し、その属性のポインタを返す
	/// </summary>
	/// <param name="attribute"></param>
	/// <returns></returns>
	static std::shared_ptr<CannonballAttributeBase> CreateAttribute(EnCannonballAttribute attribute)
	{
		//ハッシュマップを取得する
		auto& map = GetAttributeMap();
		//ハッシュマップから属性のポインタを取得
		auto it = map.find(attribute);
		//it内に正しく属性のポインタが登録されていれば
		if (it != map.end())
		{
			//属性のポインタを返す
			return it->second();
		}
		//登録されていなければ
		return nullptr;
	}
private:
	/// <summary>
	/// 移動計算関数のハッシュマップの作成
	/// </summary>
	/// <returns></returns>
	static std::unordered_map<EnCannonballAttribute, CannonballMoveCalcFunc>& GetAttributeMap()
	{
		static std::unordered_map<EnCannonballAttribute, CannonballMoveCalcFunc> map;
		return map;
	}
};

