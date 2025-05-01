#include "stdafx.h"
#include "CannonballManager.h"

#include "CannonballEntity.h"
#include "CannonballAttributeBase.h"

//砲弾を発射し、発射した砲弾のアドレスを取得する
std::shared_ptr<CannonballEntity> CannonballManager::RequestFiringCannonball(
	const EnCannonballAttribute cannonballAttribute)
{
	//属性に沿った砲弾を作成
	CreateNewCannonball(cannonballAttribute);

	//まずはリストの中に未使用の砲弾があるかどうか調べる
	//if (IsThereSpaceOnList() == true)
	//{

	//}
	//else
	//{
	//	
	//}


	return nullptr;

}

std::shared_ptr<CannonballEntity> CannonballManager::CreateNewCannonball(
	const EnCannonballAttribute cannonballAttribute)
{
	//計算クラスを砲弾属性から取得
	CannonballAttributeBase* calcClass = GetCannonballCalc(cannonballAttribute);
	//ヌルだったら作成しない
	if (calcClass == nullptr)
	{
		return nullptr;
	}
	//データ構造体変数
	CannonballData newCannonballData;
	//砲弾を動的に作成(スマートポインタ使用)
	std::shared_ptr<CannonballEntity> newCannonballPtr = std::make_shared<CannonballEntity>();
	//砲弾のポインタを登録
	newCannonballData.m_cannonballPtr = newCannonballPtr;
	//生存秒数を初期化
	newCannonballData.m_timer = 0.0f;
	//移動計算クラスを設定
	newCannonballPtr->SetCannonballCalc(calcClass);
	//配列に入れ込み
	m_cannonballList.push_back(newCannonballData);
	//戻り値
	return newCannonballPtr;
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