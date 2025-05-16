#pragma once
#include "CRC32.h"

#define appState(name)	\
public:\
	static constexpr uint32_t ID() { return Hash32(#name); }

class StateBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	StateBase() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~StateBase() {};
	/// <summary>
	/// 純粋仮想関数、ステートに入る関数
	/// </summary>
	virtual void Enter() = 0;
	/// <summary>
	/// 純粋仮想関数、ステートを更新する関数
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// 純粋仮想関数、ステートから出る関数
	/// </summary>
	virtual void Exit() = 0;
	/// <summary>
	/// 純粋仮想関数、ステートリクエスト
	/// </summary>
	/// <param name="request"></param>
	/// <returns></returns>
	virtual bool RequestState(uint32_t& request) = 0;
};

