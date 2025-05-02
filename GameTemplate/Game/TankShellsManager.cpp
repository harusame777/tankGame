#include "stdafx.h"
#include "TankShellsManager.h"

#include "TankShellsEntity.h"
#include "TankShellsAttributeBase.h"
#include "TankShellsAttributeRegistry.h"

#include "GamePlayer.h"

//砲弾を発射し、発射した砲弾のアドレスを取得する
void TankShellsManager::RequestFiringTankShells(
	const EnTankShellsAttribute tankShellsAttribute,
	const Vector3& firingPosition,
	const Vector3& firingForward
)
{
	//属性に沿った砲弾を作成
	CreateNewTankShells(tankShellsAttribute,firingPosition,firingForward);
}

void TankShellsManager::CreateNewTankShells(
	const EnTankShellsAttribute tankShellsAttribute,
	const Vector3& firingPosition,
	const Vector3& firingForward
)
{
	//属性を作成、取得
	std::shared_ptr<TankShellsAttributeBase> calcClass = TankShellsAttributeRegistry::CreateAttribute(tankShellsAttribute);
	//ヌルだったら作成しない
	if (calcClass == nullptr)
	{
		return;
	}
	//データ構造体変数
	TankShellsData newtankShellsData;
	//砲弾を作成
	TankShellsEntity* newTankShellsPtr = NewGO<TankShellsEntity>(0, "tankshells");
	//位置設定
	newTankShellsPtr->SetPosition(firingPosition);
	//方向設定
	newTankShellsPtr->SetForward(firingForward);
	//砲弾のポインタを登録
	newtankShellsData.m_tankShellsPtr = newTankShellsPtr;
	//生存秒数を初期化
	newtankShellsData.m_timer = 10.0f;
	//属性を設定
	newTankShellsPtr->SetTankShellsAttribute(calcClass);
	//属性にホストの砲弾のポインタを設定
	calcClass->SetHostPtr(newTankShellsPtr);
	//配列に入れ込み
	m_cannonballList.push_back(newtankShellsData);
}

//スタート関数
bool TankShellsManager::Start()
{
	//プレイヤーのインスタンスを取得
	m_player = FindGO<GamePlayer>("gamePlayer");

	return true;
}

//アップデート関数
void TankShellsManager::Update()
{

	

}