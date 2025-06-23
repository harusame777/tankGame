#pragma once

#include "TankShellsAttributeBase.h"
#include "TankShellsAttribute.h"

class TankShellsAttributeRegistry;
class EnemyTankEntity;
class GamePlayer;

namespace TankShells_002_Constant
{

	const float SPEED_MAX = 100.0f;

	const float ROTATE_STRENGTH = 0.05f;

	const float HORMING_START_TIME = 1.5f;

	const float HORMING_END_TIME = 1.5f;

	const float POSITION_Y_CORRECTION = 35.0f;
}

class TankShells_002_Homing : public TankShellsAttributeBase
{

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	TankShells_002_Homing() {};
	/// <summary>
	/// 初期化
	/// </summary>
	void InitData(
		CollisionObject* collsion,
		const char* name
	) override;
	/// <summary>
	/// 移動計算
	/// </summary>
	void GunnerIsPlayerMoveCalc() override;
	/// <summary>
	/// 
	/// </summary>
	void GunnerIsEnemyMoveCalc() override;
	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <returns></returns>
	bool HitCheck() override;
	/// <summary>
	/// 衝突時アクション
	/// </summary>
	void HitAction() override;
	/// <summary>
	/// 削除時処理
	/// </summary>
	void DeleteTankShellsAttributeAction() override;
private:
	/// <summary>
	/// ターゲットのエネミータンクを取得
	/// </summary>
	int GetTargetEnemyTankId();
	/// <summary>
	/// 指定された方向に通常の砲弾移動の計算を行う
	/// </summary>
	/// <param name="targetPos"></param>
	/// <returns></returns>
	void CalcNormalMoveVector();
	/// <summary>
	/// 指定されたターゲット位置へのホーミングベクトルを計算します。
	/// </summary>
	/// <param name="targetPos">ターゲットの位置を表すベクトル。</param>
	/// <returns>ターゲット位置へのホーミングベクトルへの参照。</returns>
	void CalcHormingMoveVector(const Vector3& targetPos);
	/// <summary>
	/// 追尾対象エネミー
	/// </summary>
	int m_targetEnemyTankId = -1;
	/// <summary>
	/// プレイヤーのインスタンス
	/// </summary>
	GamePlayer* m_gamePlayer = nullptr;
	/// <summary>
	/// 2つのベクトル間のコサインしきい値を表す変数です。
	/// </summary>
	float m_cosThreshold = 0.0f;
	/// <summary>
	/// ホーミング開始タイマーを表す浮動小数点数型の変数です。
	/// </summary>
	float m_hormingStartTimer = 0.0f;
	/// <summary>
	/// ホーミング終了タイマーを表す浮動小数点数型の変数です。
	/// </summary>
	float m_hormingEndTimer = 0.0f;
	/// <summary>
	/// 速度
	/// </summary>
	Vector3 m_velocity = Vector3::Zero;
	/// <summary>
	/// モデルの向き
	/// </summary>
	Vector3 m_modelForward = Vector3::AxisZ;
	/// <summary>
	/// 更新用ベクトル
	/// </summary>
	Vector3 m_updatePos = Vector3::Zero;
	/// <summary>
	/// 変数登録実行用
	/// </summary>
	static bool m_attributeRegistered;
};

