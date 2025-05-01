#pragma once

class CannonballEntity;

class CannonballAttributeBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CannonballAttributeBase(CannonballEntity* cannonball) : m_connectCannonball(cannonball) {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual~CannonballAttributeBase() {};
	/// <summary>
	/// 計算を行う
	/// </summary>
	virtual void Calc() = 0;
	/// <summary>
	/// 接触時のふるまい
	/// </summary>
	virtual void HitAction() = 0;
private:
	/// <summary>
	/// このステートを持っている砲弾クラス
	/// </summary>
	CannonballEntity* m_connectCannonball = nullptr;
};

