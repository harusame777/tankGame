#pragma once

#include "TankShellsEntity.h"

class TankShellsAttributeBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	TankShellsAttributeBase(){};
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual~TankShellsAttributeBase() {};
	/// <summary>
	/// この属性を持っている砲弾のポインタを設定
	/// </summary>
	/// <param name="hostTankShells"></param>
	void SetHostPtr(TankShellsEntity* hostTankShells)
	{
		m_hostTankShellsPtr = hostTankShells;
	}
	/// <summary>
	/// データ設定
	/// </summary>
	/// <param name="hostData"></param>
	virtual void InitData() = 0;
	/// <summary>
	/// 移動計算を行う、ポインタで送るので引数の内容は更新される
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="rot"></param>
	/// <param name="forward"></param>
	virtual void MoveCalc() = 0;
	/// <summary>
	/// 接触時のふるまい
	/// </summary>
	virtual void HitAction() = 0;
protected:
	/// <summary>
	/// この属性を持っている砲弾本体
	/// </summary>
	TankShellsEntity* m_hostTankShellsPtr = nullptr;
};

