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
	virtual ~TankShellsAttributeBase() {};
	/// <summary>
	/// この属性を持っている砲弾のポインタを設定
	/// </summary>
	/// <param name="hostTankShells"></param>
	void SetHostPtr(TankShellsEntity* hostTankShells)
	{
		m_hostTankShellsPtr = hostTankShells;
	}
	/// <summary>
	/// プレイヤーかエネミーどちらの移動計算を使用するかを設定
	/// trueがプレイヤー、falseがエネミー
	/// </summary>
	/// <param name="swithi"></param>
	void SetCalcSwithi(const bool swithi)
	{
		m_calcSwithi = swithi;
	}
	/// <summary>
	/// データ設定
	/// </summary>
	/// <param name="hostData"></param>
	virtual void InitData(
		CollisionObject* collsion,
		const char* name
	) = 0;
	/// <summary>
	/// 移動更新
	/// </summary>
	void UpdateMove()
	{
		if (m_calcSwithi)
		{
			GunnerIsPlayerMoveCalc();
		}
		else
		{
			GunnerIsEnemyMoveCalc();
		}
	}
	/// <summary>
	/// プレイヤーが砲手の際の移動計算処理
	/// </summary>
	virtual void GunnerIsPlayerMoveCalc() = 0;
	/// <summary>
	/// エネミーが砲手の際の移動計算処理
	/// </summary>
	virtual void GunnerIsEnemyMoveCalc() = 0;
	/// <summary>
	/// 接触条件
	/// </summary>
	/// <returns></returns>
	virtual bool HitCheck() = 0;
	/// <summary>
	/// 接触時のふるまい
	/// </summary>
	virtual void HitAction() = 0;
	/// <summary>
	/// 削除時処理
	/// </summary>
	virtual void DeleteTankShellsAttributeAction() = 0;
protected:
	/// <summary>
	/// この属性を持っている砲弾本体
	/// </summary>
	TankShellsEntity* m_hostTankShellsPtr = nullptr;
	/// <summary>
	/// プレイヤーかエネミーどちらの移動計算を使用するかのbool
	/// trueがプレイヤー、falseがエネミー
	/// </summary>
	bool m_calcSwithi = true;
	/// <summary>
	/// 衝突対象の名前を格納する文字列へのポインタです。
	/// </summary>
	const char* m_targetCollisionName;
	/// <summary>
	/// ホスト戦車の砲弾の衝突オブジェクトを指すポインタです。
	/// </summary>
	CollisionObject* m_hostTankShellsCollision = nullptr;
};

