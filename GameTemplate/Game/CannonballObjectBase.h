#pragma once

#include "CannonballCommonState.h"

class CannonballStateBase;

class CannonballObjectBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CannonballObjectBase() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~CannonballObjectBase() {};
	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Init() = 0;
	/// <summary>
	/// ステート更新関数
	/// </summary>
	void UpdateCannonballState();
	/// <summary>
	/// ステートを変更する
	/// </summary>
	/// <param name="changeState"></param>
	void ChangeState(const EnCannonballState changeState)
	{
		m_requestState = changeState;
	}
private:
	/// <summary>
	/// ステート配列
	/// </summary>
	CannonballStateBase* m_cannonballStateList[EnCannonballState::en_stateNum] = { nullptr };
	/// <summary>
	/// 現在のステート
	/// </summary>
	EnCannonballState m_currentState = EnCannonballState::en_init;
	/// <summary>
	/// リクエストされたステート
	/// </summary>
	EnCannonballState m_requestState = EnCannonballState::en_init;
};

