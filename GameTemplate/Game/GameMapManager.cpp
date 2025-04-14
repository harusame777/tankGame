#include "stdafx.h"
#include "GameMapManager.h"

//ここからオブジェクトのインクルード
#include "MapObjectFloor.h"

//スタート関数
bool GameMapManager::Start()
{

	//今のところはメンバ変数にする利点が分からないので
	//ローカル変数として作成
	LevelRender MapObjectLevelRender;

	//レベルから位置などを取得してオブジェクトを作成
	MapObjectLevelRender.Init
	("Assets/levelData/testLevel/testLevelV1.tkl",
	[&](LevelObjectData_Render& objData)
	{
		//床生成
		if (objData.ForwardMatchName(L"TestMapV1") == true)
		{
			MapObjectFloor* objectFloor = nullptr;
			//NewGoしてアドレスを取得
			objectFloor = NewGO<MapObjectFloor>(0, "mapObject");
			//位置設定
			objectFloor->SetPosition(objData.m_position);
			//オブジェクトをリストに登録
			SetObjectList(objectFloor);
			return true;
		}
		return true;
	});
}

//アップデート関数
void GameMapManager::Update()
{
	
}

