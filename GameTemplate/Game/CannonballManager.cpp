#include "stdafx.h"
#include "CannonballManager.h"

#include "CannonballEntity.h"
#include "CannonballObjectBase.h"


//砲弾を発射し、発射した砲弾のアドレスを取得する
const std::unique_ptr<CannonballEntity>& CannonballManager::FiringCannonball()
{

	//まずはリストの中に未使用の砲弾があるかどうか調べる
	if (IsThereSpaceOnList() == true)
	{

	}
	else
	{
		
	}

}

bool CannonballManager::IsThereSpaceOnList()
{
	bool isThereSpaceOnList = false;

	for (auto& listPtr : m_cannonballList)
	{
		if (listPtr.IsDataUse());
		{
			isThereSpaceOnList = true;
		}
	}

	return isThereSpaceOnList;
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