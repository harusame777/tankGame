#include "stdafx.h"
#include "TankShells_001_Normal.h"

#include "TankShellsAttributeRegistry.h"

//初期化関数登録処理
bool TankShells_001_Normal::m_attributeRegistered = [] {
	TankShellsAttributeRegistry::registerFactory(EnTankShellsAttribute::en_normal, []() {
		return std::make_unique<TankShells_001_Normal>();
		});
	return true;
}();

//初期化
void TankShells_001_Normal::InitData(
	CollisionObject* collsion,
	const char* name
) 
{
	m_hostTankShellsCollision = collsion;

	m_targetCollisionName = name;
}

//プレイヤーが砲手の際の処理
void TankShells_001_Normal::GunnerIsPlayerMoveCalc()
{
	Vector3 newPosition = Vector3::Zero;

	const Vector3 modelForward = m_hostTankShellsPtr->GetForward();

	const Vector3 modelPosition = m_hostTankShellsPtr->GetPosition();

	newPosition = modelPosition + modelForward * TankShells_001_Constant::speed * g_gameTime->GetFrameDeltaTime();

	m_hostTankShellsPtr->SetPosition(newPosition);
}

void TankShells_001_Normal::GunnerIsEnemyMoveCalc()
{
	Vector3 newPosition = Vector3::Zero;

	const Vector3 modelForward = m_hostTankShellsPtr->GetForward();

	const Vector3 modelPosition = m_hostTankShellsPtr->GetPosition();

	newPosition = modelPosition + modelForward * TankShells_001_Constant::speed * g_gameTime->GetFrameDeltaTime();

	m_hostTankShellsPtr->SetPosition(newPosition);
}

//衝突判定
bool TankShells_001_Normal::HitCheck()
{
	if (GameCollisionManager::GetCollisionManagerInstance()
		->IsAColisionHitsBColision(m_hostTankShellsCollision, m_targetCollisionName) == true)
	{
		return true;
	}

	return false;
}

//衝突時アクション
void TankShells_001_Normal::HitAction()
{

}

//削除時処理
void TankShells_001_Normal::DeleteTankShellsAttributeAction()
{

}