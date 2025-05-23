#pragma once

#include "TankShellsAttribute.h"
#include "EnemyTankEntity.h"

class EnemyTankAttributeBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyTankAttributeBase() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~EnemyTankAttributeBase() {};
	/// <summary>
	/// この属性を持っている砲弾のポインタを設定
	/// </summary>
	/// <param name="hostTankShells"></param>
	void SetHostPtr(EnemyTankEntity* hostEnemyTankPtr)
	{
		m_hostEnemyTankPtr = hostEnemyTankPtr;
	}
	/// <summary>
	/// 属性データ初期化
	/// </summary>
	virtual void InitEnemyTankAttributeData() = 0;
	/// <summary>
	/// 固有処理関数
	/// </summary>
	virtual void EnemyTankUniqueProcessing() = 0;
	/// <summary>
	/// 削除処理関数
	/// </summary>
	virtual void EnemyTankDeleteProcessing() = 0;
	/// <summary>
	/// 使用する砲弾の変数
	/// </summary>
	EnTankShellsAttribute m_shellsUsed = EnTankShellsAttribute::en_normal;
	/// <summary>
	/// タンクの最大速度
	/// </summary>
	float m_maxTankSpeed = 0.0f;
protected:
	/// <summary>
	/// この属性を持っている砲弾本体
	/// </summary>
	EnemyTankEntity* m_hostEnemyTankPtr = nullptr;
};