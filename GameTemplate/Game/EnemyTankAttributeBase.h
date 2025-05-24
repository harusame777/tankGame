#pragma once

#include "TankShellsAttribute.h"
#include "EnemyTankEntity.h"

class GamePlayer;
class EnemyAttackPoint;

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
	virtual void InitEnemyTankAttributeData(
		GamePlayer* player,
		EnemyTankEntity* hostTank
	) = 0;
	/// <summary>
	/// 固有処理関数
	/// </summary>
	virtual void UniqueProcessing() = 0;
	/// <summary>
	/// 削除処理関数
	/// </summary>
	virtual void DeleteProcessing() = 0;
	/// <summary>
	/// 使用する砲弾の変数
	/// </summary>
	EnTankShellsAttribute m_shellsUsed = EnTankShellsAttribute::en_normal;
	/// <summary>
	/// エネミーの追跡処理
	/// </summary>
	virtual const Vector3& TrackingAttribute() = 0;
	/// <summary>
	/// エネミーの追跡ステート変更処理
	/// </summary>
	/// <param name="request"></param>
	/// <returns></returns>
	virtual bool RequestStateTrackingAttribute(uint32_t& request) = 0;
	/// <summary>
	/// エネミーの攻撃行動処理
	/// </summary>
	virtual const Vector3& AttackMoveAttribute() = 0;
	/// <summary>
	/// エネミーの攻撃行動ステート変更処理
	/// </summary>
	/// <param name="request"></param>
	/// <returns></returns>
	virtual bool RequestStateAttackMoveAttribute(uint32_t& request) = 0;
	/// <summary>
	/// タンクの最大速度
	/// </summary>
	float m_maxTankSpeed = 0.0f;
protected:
	/// <summary>
	/// アタックポイント
	/// </summary>
	EnemyAttackPoint* m_attackPoint = nullptr;
	/// <summary>
	/// この属性を持っている砲弾本体
	/// </summary>
	EnemyTankEntity* m_hostEnemyTankPtr = nullptr;
	/// <summary>
	/// ゲームプレイヤーのインスタンス
	/// </summary>
	GamePlayer* m_player = nullptr;
};
