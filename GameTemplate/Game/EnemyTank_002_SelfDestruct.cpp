#include "stdafx.h"
#include "EnemyTank_002_SelfDestruct.h"

#include "EnemyTankAttributeRegistry.h"
#include "GamePlayer.h"
#include "GameCollisionManager.h"
#include "EnemyTankManager.h"

#include "EnemyTankStateTrackingUpdate.h"
#include "EnemyTankStateAttackMoveUpdate.h"
#include "EnemyTankStateUniqueUpdate.h"

//初期化関数登録処理
bool EnemyTank_002_SelfDestruct::m_attributeRegistered = [] {
EnemyTankAttributeRegistry::EnemyTankRegisterFactory(EnEnemyTankAttribute::en_tankSelfDestruct, []() {
	return std::make_unique<EnemyTank_002_SelfDestruct>();
	});
return true;
}();

//初期化関数
void EnemyTank_002_SelfDestruct::InitEnemyTankAttributeData(
	GamePlayer* player,
	EnemyTankEntity* hostTank
)
{
	m_maxTankSpeed = 20.0f;

	m_shellsUsed = EnTankShellsAttribute::en_normal;

	m_player = player;

	m_hostEnemyTankPtr = hostTank;
}

//射撃処理
void EnemyTank_002_SelfDestruct::FireProcessing()
{
	//特になし
}

//削除処理
bool EnemyTank_002_SelfDestruct::DeleteProcessing()
{

	//自爆当たり判定が未生成の場合は生成する
	if (m_selfDestructCollision == nullptr)
	{
		m_selfDestructCollision = GameCollisionManager::GetCollisionManagerInstance()->CreateSphereCollision(
			m_hostEnemyTankPtr->GetPosition(),
			Quaternion::Identity,
			150.0f, // 自爆範囲の半径
			"GamePlayerAttack"
		);

		//自爆中はホストの敵戦車を描画しない
		m_hostEnemyTankPtr->SetDrawFlag(false);

		//自爆終了までのタイマーを設定
		m_selfDestructEndTimer = 3.0f;
	}

	//自爆終了までのタイマーが0以下になったら自爆終了
	if (m_selfDestructEndTimer <= 0.0f)
	{
		//削除フラグを立てる
		EnemyTankManager::GetEnemyTankManagerInstance()->ActivateDeleteFlag(m_hostEnemyTankPtr);

		return true; // 処理が終了したので削除
	}
	else
	{
		m_selfDestructEndTimer -= g_gameTime->GetFrameDeltaTime();
	}

	//自爆当たり判定の位置をホストの敵戦車の位置に更新
	Vector3 colPos = m_hostEnemyTankPtr->GetPosition();
	colPos.y += 35.0f;
	m_selfDestructCollision->SetPosition(colPos);
	m_selfDestructCollision->Update();

	//処理が終わってない場合は削除しない
	return false;
}

//追跡処理類

//追跡処理初期化
void EnemyTank_002_SelfDestruct::EnterTracking()
{
	//特になし
}

//追跡処理更新
const Vector3& EnemyTank_002_SelfDestruct::UpdateTracking()
{
	//プレイヤーの位置を取得
	Vector3 playerPos = m_player->GetPosition();
	//ホストの敵戦車の位置を取得
	Vector3 hostPos = m_hostEnemyTankPtr->GetPosition();
	//ホストの敵戦車の位置からプレイヤーの位置を引く
	m_moveDirection = playerPos - hostPos;

	return m_moveDirection;
}

//追跡処理終了
void EnemyTank_002_SelfDestruct::EndTracking()
{
	//自爆までの遅延タイマーを設定
	m_selfDestructDelayTimer = 2.0f;
	//自身の当たり判定を無効化
	m_hostEnemyTankPtr->SetCollisionEnable(false);
}

//追跡処理ステート遷移
bool EnemyTank_002_SelfDestruct::RequestStateTracking(uint32_t& request)
{
	//追跡処理から固有処理に遷移する場合の条件をチェック
	if (IsHostTankInSelfDestructRange() == true)
	{
		request = EnemyTankStateUniqueUpdate::ID();

		return true;
	}

	return false;
}

//攻撃動作処理類

//攻撃動作処理初期化
void EnemyTank_002_SelfDestruct::EnterAttackMove()
{
	//特になし
}

//攻撃動作処理更新
const Vector3& EnemyTank_002_SelfDestruct::UpdateAttackMove()
{
	return Vector3::Zero;
}

//攻撃動作処理終了
void EnemyTank_002_SelfDestruct::EndAttackMove()
{
	//特になし
}

//攻撃動作処理ステート遷移
bool EnemyTank_002_SelfDestruct::RequestStateAttackMove(uint32_t& request)
{
	return false;
}

//固有処理類

//固有処理初期化
void EnemyTank_002_SelfDestruct::EnterUnique()
{
	//自爆までの時間を設定
	m_selfDestructTimer = 1.0f; 
}

//固有処理更新
const Vector3& EnemyTank_002_SelfDestruct::UpdateUnique()
{
	//自爆タイマーが0以下の場合自爆、それ以外はタイマーを減らす
	if (m_selfDestructTimer <= 0.0f && m_isSelfDestruct == false)
	{
		m_isSelfDestruct = true;
	}
	else
	{
		m_selfDestructTimer -= g_gameTime->GetFrameDeltaTime();
	}

	//自爆フラグがtrueなら、自爆処理を行う
	if (m_isSelfDestruct == true)
	{
		UpdateSelfDestruct();
	}

	return Vector3::Zero;
}

//固有処理終了
void EnemyTank_002_SelfDestruct::EndUnique()
{
	//特になし	
}

//固有処理ステート遷移
bool EnemyTank_002_SelfDestruct::RequestStateUnique(uint32_t& request)
{
	//特になし
	return false;
}

//その他処理類

//ホストの敵戦車が自爆可能な距離にいるか判定
bool EnemyTank_002_SelfDestruct::IsHostTankInSelfDestructRange()
{
	//プレイヤーの位置を取得
	Vector3 playerPos = m_player->GetPosition();
	//ホストの敵戦車の位置を取得
	Vector3 hostPos = m_hostEnemyTankPtr->GetPosition();
	//ホストの敵戦車の位置からプレイヤーの位置を引く
	Vector3 hostTankToPlayerVec = playerPos - hostPos;
	//ホストの敵戦車とプレイヤーの距離を計算
	float hostTankToPlayerRange = hostTankToPlayerVec.Length();

	//距離が自爆可能距離以内かチェック
	if (hostTankToPlayerRange < 100.0f)
	{
		return true;
	}

	return false;
}

void EnemyTank_002_SelfDestruct::UpdateSelfDestruct()
{
	//自爆遅延処理
    if (m_selfDestructDelayTimer > 0.0f)
	{
		m_selfDestructDelayTimer -= g_gameTime->GetFrameDeltaTime();
		return; // 遅延中は処理を抜ける
	}

	//自爆当たり判定が未生成の場合は生成する
	if (m_selfDestructCollision == nullptr)
	{
		m_selfDestructCollision = GameCollisionManager::GetCollisionManagerInstance()->CreateSphereCollision(
			m_hostEnemyTankPtr->GetPosition(), 
			Quaternion::Identity,
			150.0f, // 自爆範囲の半径
			"EnemyTankAttack"
		);

		//自爆中はホストの敵戦車を描画しない
		m_hostEnemyTankPtr->SetDrawFlag(false);

		//自爆終了までのタイマーを設定
		m_selfDestructEndTimer = 3.0f;
	}

	//自爆終了までのタイマーが0以下になったら自爆終了
	if (m_selfDestructEndTimer <= 0.0f)
	{
		//削除フラグを立てる
		EnemyTankManager::GetEnemyTankManagerInstance()->ActivateDeleteFlag(m_hostEnemyTankPtr);
	}
	else
	{
		m_selfDestructEndTimer -= g_gameTime->GetFrameDeltaTime();
	}

	//自爆当たり判定の位置をホストの敵戦車の位置に更新
	Vector3 colPos = m_hostEnemyTankPtr->GetPosition();
	colPos.y += 35.0f;
	m_selfDestructCollision->SetPosition(colPos);
	m_selfDestructCollision->Update();
}