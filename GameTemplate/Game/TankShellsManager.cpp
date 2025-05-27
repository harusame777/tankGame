#include "stdafx.h"
#include "TankShellsManager.h"

#include "TankShellsEntity.h"
#include "TankShellsAttributeBase.h"
#include "TankShellsAttributeRegistry.h"

#include "GamePlayer.h"

//インスタンスを初期化
TankShellsManager* TankShellsManager::m_tankShellsManagerInstance = nullptr;

//砲弾を発射する
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
	const Vector3& firingForward,
	EnFireAttribute FirePlayerOrEnemy
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
	//プレイヤーか敵かの属性を設定
	if(FirePlayerOrEnemy == EnFireAttribute::Player)
	{
		newTankShellsPtr->SetCollisionName("");
	}
	else if (FirePlayerOrEnemy == EnFireAttribute::Enemy)
	{
		newTankShellsPtr->SetCollisionName();
	}
	//属性にホストの砲弾のポインタを設定
	calcClass->SetHostPtr(newTankShellsPtr);
	//配列に入れ込み
	m_cannonballList.push_back(newtankShellsData);
}

//砲弾が何かに当たった時の処理
void TankShellsManager::HitTankShells(TankShellsEntity* hitShells)
{
	//for文をvector配列のイテレータを取得して処理
	//イテレータが配列の末尾であれば終了
	for (auto it = m_cannonballList.begin(); it != m_cannonballList.end(); it++)
	{
		//砲弾が引数のポインタと違ったら飛ばす
		if (it->m_tankShellsPtr != hitShells)
		{
			continue;
		}

		if (it->m_deleteFlag == true)
		{
			return;
		}

		it->m_deleteFlag = true;
	}
}

//スタート関数
void TankShellsManager::InitTankShellsManager()
{
	//プレイヤーのインスタンスを取得
	m_player = FindGO<GamePlayer>("gamePlayer");
}

//アップデート関数
void TankShellsManager::UpdateTankShellsManager()
{

	//砲弾の時間削除処理
	DeleteTankShells();

}

//砲弾の時間削除関数
void TankShellsManager::DeleteTankShells()
{
	//for文をvector配列のイテレータを取得して処理
	//イテレータが配列の末尾であれば終了
	for (auto it = m_cannonballList.begin(); it != m_cannonballList.end();)
	{
		//砲弾の残り生存時間を減らす
		it->m_timer -= g_gameTime->GetFrameDeltaTime();

		//現在処理中のイテレータの残り生存時間が0.0f以下だったら削除処理
		if (it->m_timer < 0.0f || it->m_deleteFlag == true)
		{
			//砲弾の削除処理を実行
			it->m_tankShellsPtr->DeleteGOTankShells();
			//配列から削除
			it = m_cannonballList.erase(it);

			continue;
		}
		else
		{
			it++;
		}
	}
}