#pragma once
#include "CRC32.h"

class StateBase;

#define appState(name)  \
public:\
	static constexpr uint32_t ID(){ return Hash32(#name); }

class StateMachineBase
{
	/// <summary>
	/// 名前定義、ステートマップ
	/// </summary>
	using StateMap = std::unordered_map<uint32_t, StateBase*>;
	/// <summary>
	/// 名前定義。ステートペア
	/// </summary>
	using StatePair = std::pair<uint32_t, StateBase*>;
protected:
	/// <summary>
	/// ステートマップ
	/// </summary>
	StateMap m_stateMap;
	/// <summary>
	/// 現在のステートポインタ
	/// </summary>
	StateBase* m_currentState = nullptr;
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	StateMachineBase() 
		: m_currentState(nullptr) 
	{
		m_stateMap.clear();
	}
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~StateMachineBase()
	{
		for (auto it : m_stateMap)
		{
			delete it.second;
			it.second = nullptr;
		}
		m_stateMap.clear();
	}
	/// <summary>
	/// 純粋仮想関数、更新関数
	/// </summary>
	virtual void Update() = 0;
public:
	/// <summary>
	/// ステートマップに登録
	/// </summary>
	template<typename T, typename... Args>
	inline void RegisterState(Args&&... args)
	{
		m_stateMap.insert(StatePair(T::ID(), new T(std::forward<Args>(args)...)));
	}
	/// <summary>
	/// ステート初期化
	/// </summary>
	template<typename T>
	inline void InitilizeState()
	{
		m_currentState = FindState(T::ID());
	}
protected:
	/// <summary>
	/// ステートを探す
	/// </summary>
	/// <param name="id"></param>
	/// <returns></returns>
	inline StateBase* FindState(uint32_t id)
	{
		const auto& it = m_stateMap.find(id);
		if (it == m_stateMap.end())
		{
			//念のため
			return nullptr;
		}
		return it->second;
	}
};

