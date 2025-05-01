#include "stdafx.h"
#include "CannonballManager.h"

#include "CannonballEntity.h"
#include "CannonballAttributeBase.h"
#include "CannonballAttributeRegistry.h"

//砲弾を発射し、発射した砲弾のアドレスを取得する
void CannonballManager::RequestFiringCannonball(
	const EnCannonballAttribute cannonballAttribute)
{
	//属性に沿った砲弾を作成
	CreateNewCannonball(cannonballAttribute);
}

void CannonballManager::CreateNewCannonball(
	const EnCannonballAttribute cannonballAttribute)
{
	//属性を作成、取得
	std::shared_ptr<CannonballAttributeBase> calcClass = CannonballAttributeRegistry::CreateAttribute(cannonballAttribute);
	//ヌルだったら作成しない
	if (calcClass == nullptr)
	{
		return;
	}
	//データ構造体変数
	CannonballData newCannonballData;
	//砲弾を作成
	CannonballEntity* newCannonballPtr = NewGO<CannonballEntity>(0, "cannonball");
	//砲弾のポインタを登録
	newCannonballData.m_cannonballPtr = newCannonballPtr;
	//生存秒数を初期化
	newCannonballData.m_timer = 10.0f;
	//属性を設定
	newCannonballPtr->SetCannonballAttribute(calcClass);
	//属性にホストの砲弾のポインタを設定
	calcClass->SetHostPtr(newCannonballPtr);
	//配列に入れ込み
	m_cannonballList.push_back(newCannonballData);
}

CannonballAttributeBase* CannonballManager::GetCannonballCalc(
	const EnCannonballAttribute cannonballAttribute)
{

	
	
	return nullptr;
}

//スタート関数
bool CannonballManager::Start()
{

	

	return true;
}

//アップデート関数
void CannonballManager::Update()
{

	

}