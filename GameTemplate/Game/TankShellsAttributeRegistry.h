#pragma once

#include "TankShellsAttribute.h"

class TankShellsAttributeBase;

class TankShellsAttributeRegistry
{
public:
	/// <summary>
	/// 移動計算関数
	/// </summary>
	using TankShellsAttributeFunc = std::function<std::shared_ptr<TankShellsAttributeBase>()>;
	/// <summary>
	/// 初期化登録
	/// </summary>
	/// <param name="attribute"></param>
	/// <param name="func"></param>
	static void registerFactory(EnTankShellsAttribute attribute, TankShellsAttributeFunc func)
	{
		GetTankShellsAttributeMap()[attribute] = std::move(func);
	}
	/// <summary>
	/// 属性を作成し、その属性のポインタを返す
	/// </summary>
	/// <param name="attribute"></param>
	/// <returns></returns>
	static std::shared_ptr<TankShellsAttributeBase> CreateAttribute(EnTankShellsAttribute attribute)
	{
		//ハッシュマップを取得する
		auto& map = GetTankShellsAttributeMap();
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
	/// 移動計算関数のハッシュマップの作成
	/// </summary>
	/// <returns></returns>
	static std::unordered_map<EnTankShellsAttribute, TankShellsAttributeFunc>& GetTankShellsAttributeMap()
	{
		static std::unordered_map<EnTankShellsAttribute, TankShellsAttributeFunc> map;
		return map;
	}
};

