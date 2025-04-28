#pragma once

#include "CannonballCommonState.h"

class CannonballObjectBase;

class CannonballStateBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CannonballStateBase(CannonballObjectBase* cannonball) : m_connectCannonball(cannonball) {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual~CannonballStateBase() {};
	/// <summary>
	/// 純粋仮想関数、ステート初期化
	/// </summary>
	virtual void InitState() = 0;
	/// <summary>
	/// 純粋仮想関数、ステート更新
	/// </summary>
	virtual void UpdateState() = 0;
	/// <summary>
	/// 純粋仮想関数、ステート終了
	/// </summary>
	virtual void EndState() = 0;
private:
	/// <summary>
	/// このステートを保持している砲弾のステートを変更する
	/// </summary>
	/// <param name="changeState"></param>
	void ChangeConnectCannonballState(const EnCannonballState changeState);
	/// <summary>
	/// このステートを持っている砲弾クラス
	/// </summary>
	CannonballObjectBase* m_connectCannonball = nullptr;
};

