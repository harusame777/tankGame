#include "stdafx.h"
#include "TankShells_002_Homing.h"

#include "TankShellsAttributeRegistry.h"

#include "EnemyTankManager.h"
#include "EnemyTankEntity.h"

#include "GamePlayerManager.h"
#include "GamePlayer.h"

#include "TankTurretMovingComponent.h"


//初期化関数登録処理
bool TankShells_002_Homing::m_attributeRegistered = [] {
	TankShellsAttributeRegistry::registerFactory(EnTankShellsAttribute::en_homing, []() {
		return std::make_unique<TankShells_002_Homing>();
		});
	return true;
}();

//初期化
void TankShells_002_Homing::InitData(
	CollisionObject* collsion,
	const char* name
)
{
	m_hostTankShellsCollision = collsion;

	m_targetCollisionName = name;

	m_updatePos = m_hostTankShellsPtr->GetPosition();

	//プレイヤーのインスタンスを取得
	m_gamePlayer = GamePlayerManager::GetGamePlayerManagerInstance()
		->GetGamePlayerInstance();

	//プレイヤーで初期化されているなら追尾対象を選定
	if (m_calcSwithi == true)
	{
		//追尾半径を設定
		m_cosThreshold = std::cos(30.0f);
		//ターゲット選定
		m_targetEnemyTankPtr = GetTargetEnemyTank();
	}

	//初速設定
	m_velocity = m_hostTankShellsPtr->GetForward() * 
		TankShells_002_Constant::SPEED_MAX;

	//ホーミング開始までのタイマーを設定
	m_hormingStartTimer = TankShells_002_Constant::HORMING_START_TIME;
	//ホーミング終了までのタイマーを設定
	m_hormingEndTimer = TankShells_002_Constant::HORMING_END_TIME;
}

//プレイヤーが砲手の際の処理
void TankShells_002_Homing::GunnerIsPlayerMoveCalc()
{	
	if (m_targetEnemyTankPtr != nullptr && 
		m_hormingStartTimer < 0.0f && 
		m_hormingEndTimer > 0.0f)
	{
		Vector3 targetPos = m_targetEnemyTankPtr->GetPosition();

		CalcHormingMoveVector(targetPos);

		m_hormingEndTimer -= g_gameTime->GetFrameDeltaTime();
	}
	else
	{
		CalcNormalMoveVector();

		m_hormingStartTimer -= g_gameTime->GetFrameDeltaTime();
	}

	m_hostTankShellsPtr->SetForward(m_modelForward);

	m_hostTankShellsPtr->SetPosition(m_updatePos);
}

//エネミーが砲手の際の処理
void TankShells_002_Homing::GunnerIsEnemyMoveCalc()
{
	if (m_gamePlayer != nullptr &&
		m_hormingStartTimer < 0.0f &&
		m_hormingEndTimer > 0.0f)
	{
		Vector3 targetPos = m_gamePlayer->GetPosition();

		CalcHormingMoveVector(targetPos);

		m_hormingEndTimer -= g_gameTime->GetFrameDeltaTime();
	}
	else
	{
		CalcNormalMoveVector();

		m_hormingStartTimer -= g_gameTime->GetFrameDeltaTime();
	}

	m_hostTankShellsPtr->SetForward(m_modelForward);

	m_hostTankShellsPtr->SetPosition(m_updatePos);
}

//衝突判定
bool TankShells_002_Homing::HitCheck()
{
	if (GameCollisionManager::GetCollisionManagerInstance()
		->IsAColisionHitsBColision(m_hostTankShellsCollision, m_targetCollisionName) == true)
	{
		return true;
	}

	return false;
}

//衝突時アクション
void TankShells_002_Homing::HitAction()
{

}

//削除時処理
void TankShells_002_Homing::DeleteTankShellsAttributeAction()
{

}

EnemyTankEntity* TankShells_002_Homing::GetTargetEnemyTank()
{
	//エネミータンクのリストをマネージャーから取得
	const auto& enemyList = EnemyTankManager::GetEnemyTankManagerInstance()
		->GetEnemyTankList();
	//最も近い半径の値(値は負の無限数)
	float bestScore = -std::numeric_limits<float>::infinity();
	//もっとも近いエネミータンクのポインタを定義
	EnemyTankEntity* bestTarget = nullptr;
	//プレイヤーの位置
	Vector3 playerPos = m_gamePlayer->GetPosition();
	//現在のプレイヤーの砲塔の方向
	Vector3 forward = m_gamePlayer->GetTurretForward();

	for (auto listPtr : enemyList)
	{
		//削除フラグがtrueであれば処理を飛ばす
		if (listPtr->GetDeleteFlag() == true)
		{
			continue;
		}

		//プレイヤーからエネミータンクに伸びるベクトル
		Vector3 playerToEnemy = listPtr->GetPosition() - playerPos;
		//正規化
		playerToEnemy.Normalize();
		//内積を測る(1.0fで真正面、-1.0fで真後ろ)
		float cosAngle = forward.Dot(playerToEnemy);

		//半径外であれば処理を飛ばす
		if (cosAngle < m_cosThreshold)
		{
			continue;
		}

		//中心に近いエネミーを選定度：高にする
		if (cosAngle > bestScore)
		{
			bestScore = cosAngle;
			bestTarget = listPtr;
		}

	}

	return bestTarget;
}

void TankShells_002_Homing::CalcNormalMoveVector()
{
	Vector3 modelForward = m_hostTankShellsPtr->GetForward();

	m_modelForward = modelForward;

	Vector3 modelPosition = m_hostTankShellsPtr->GetPosition();

	m_updatePos += modelForward * TankShells_002_Constant::SPEED_MAX * g_gameTime->GetFrameDeltaTime();
}

void TankShells_002_Homing::CalcHormingMoveVector(const Vector3& targetPos)
{
	//砲弾の位置
	Vector3 tankShellsPos = m_hostTankShellsPtr->GetPosition();
	//速度から方向を取得
	Vector3 currentDir = m_velocity;
	currentDir.Normalize();
	//ターゲットの方向を計算
	Vector3 tankShellsToTargetDir = targetPos - tankShellsPos;
	tankShellsToTargetDir.Normalize();
	//線形保管を使用して方向を少しずつ変えるようにする
	Vector3 newDir = Vector3::Zero;
	newDir.Lerp(
		TankShells_002_Constant::ROTATE_STRENGTH,
		currentDir,
		tankShellsToTargetDir
	);
	newDir.Normalize();
	//方向を保存
	m_modelForward = newDir;
	//最終的な速度計算
	m_velocity = newDir * TankShells_002_Constant::SPEED_MAX;

	m_velocity.y = 0.0f;

	//位置更新
	m_updatePos += m_velocity * g_gameTime->GetFrameDeltaTime();
}