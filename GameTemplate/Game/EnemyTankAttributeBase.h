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
	/// 削除処理関数
	/// </summary>
	virtual void DeleteProcessing() = 0;
	/// <summary>
	/// 使用する砲弾の変数
	/// </summary>
	EnTankShellsAttribute m_shellsUsed = EnTankShellsAttribute::en_normal;
	/// <summary>
	/// 追跡処理初期化
	/// </summary>
	virtual void EnterTracking() = 0;
	/// <summary>
	/// エネミーの追跡処理
	/// </summary>
	virtual const Vector3& UpdateTracking() = 0;
	/// <summary>
	/// エネミーの追跡ステート変更処理
	/// </summary>
	/// <param name="request"></param>
	/// <returns></returns>
	virtual bool RequestStateTracking(uint32_t& request) = 0;
	/// <summary>
	/// 追跡終了
	/// </summary>
	virtual void EndTracking() = 0;
	/// <summary>
	/// 攻撃移動状態に入るための純粋仮想関数です。
	/// </summary>
	virtual void EnterAttackMove() = 0;
	/// <summary>
	/// エネミーの攻撃行動処理
	/// </summary>
	virtual const Vector3& UpdateAttackMove() = 0;
	/// <summary>
	/// エネミーの攻撃行動ステート変更処理
	/// </summary>
	/// <param name="request"></param>
	/// <returns></returns>
	virtual bool RequestStateAttackMove(uint32_t& request) = 0;
	/// <summary>
	/// 攻撃動作終了
	/// </summary>
	virtual void EndAttackMove() = 0;
	/// <summary>
	/// 固有処理初期化
	/// </summary>
	virtual void EnterUnique() = 0;
	/// <summary>
	/// 固有処理更新
	/// </summary>
	/// <returns></returns>
	virtual const Vector3& UpdateUnique() = 0;
	/// <summary>
	/// 固有処理ステート変更処理
	/// </summary>
	/// <param name="request"></param>
	/// <returns></returns>
	virtual bool RequestStateUnique(uint32_t& request) = 0;
	/// <summary>
	/// 固有処理終了
	/// </summary>
	virtual void EndUnique() = 0;
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
