#include "stdafx.h"
#include "GameCollisionManager.h"

//インスタンスを初期化
GameCollisionManager* GameCollisionManager::m_collisionManagerInstance = nullptr;

//球状コリジョン作成
std::shared_ptr<CollisionObject> GameCollisionManager::CreateSphereCollision(
	const Vector3& initPosition,
	const Quaternion& initRotation,
	float initSize,
	const char* str
)
{
	//データローカル変数
	GameCollisionListData newCollisionData;
	//コリジョンを動的に作成
	std::shared_ptr<CollisionObject> newCollision = std::make_shared<CollisionObject>();
	//新規コリジョンを作成
	newCollision->CreateSphere(initPosition, initRotation, initSize);
	//コリジョンのポインタをデータに登録
	newCollisionData.m_collisionPtr = newCollision;
	//ハッシュ値を計算
	uint32_t hashNum = GetHashNum(str);
	//配列に代入
	m_collisionMap.insert({ hashNum,newCollisionData });
	
	return newCollision;
}

//ハッシュ値取得
constexpr uint32_t GameCollisionManager::GetHashNum(const char* str)
{
	//32bit変数の初期化
	uint32_t hash = 2166136261u;
	//文字数分繰り返す
	while (*str)
	{
		//文字を変換して代入
		hash ^= static_cast<uint8_t>(*str++);
		//拡散させるために掛ける
		hash *= 16777619u;
	}
	return hash;
}

const bool GameCollisionManager::IsAColisionHitsBColision(
	CollisionObject* AColisionAddress,
	const char* BCollisionName
)
{
	//名前が一致するコリジョンを探す
	const auto& findCollisionList = FindListCollisionObjects(BCollisionName);

	for (auto listPtr : findCollisionList)
	{
		//コリジョンが接触していたらtrue
		if (listPtr->IsHit(AColisionAddress))
		{
			return true;
		}
	}
	//していないならfalse
	return false;
}

const bool GameCollisionManager::IsACharaconHitsBColision(
	CharacterController* ACharaconAddress,
	const char* BCollisionName
)
{
	//名前が一致するコリジョンを探す
	const auto& findCollisionList = FindListCollisionObjects(BCollisionName);

	for (auto listPtr : findCollisionList)
	{
		//キャラコンが接触していたらtrue
		if (listPtr->IsHit(*ACharaconAddress))
		{
			return true;
		}
	}
	//していないならfalse
	return false;
}

//Addressのコリジョンがリストに存在していて、なおかつ有効かどうか
CollisionObject* GameCollisionManager::Is_Address_PresentList(CollisionObject* Address)
{
	//マップの要素分回す
	for (auto it = m_collisionMap.begin(); it != m_collisionMap.end();it++)
	{
		auto shared = it->second.m_collisionPtr.lock();

		//その要素のコリジョンが有効かどうかを調べる
		if (nullptr == shared)
		{
			continue;
		}

		//要素のコリジョンがアドレスと同じか調べる
		if (Address == shared.get())
		{
			return shared.get();
		}
		else
		{
			continue;
		}
	}

	return nullptr;
}

//nameのコリジョンを複数探す
const std::vector<CollisionObject*>& GameCollisionManager::FindListCollisionObjects(const char* name)
{
	//入力された文字列をハッシュ値変換
	uint32_t hash = GetHashNum(name);
	//初期化する
	m_findCollisionObjcts.clear();
	//マップの要素分回す
	for (auto it = m_collisionMap.begin(); it != m_collisionMap.end(); it++)
	{
		//コリジョンが有効かどうか
		if (it->second.m_isValid == false)
		{
			continue;
		}

		//ハッシュ値が一致しているかどうか調べる
		if (hash == it->first)
		{
			//使用できるように変換
			auto shared = it->second.m_collisionPtr.lock();
			//一致していたら見つけたコリジョンリストにコリジョンのポインタを代入
			m_findCollisionObjcts.push_back(shared.get());
		}
	}

	return m_findCollisionObjcts;
}

//Nameのコリジョンがリストに存在しているかどうか
CollisionObject* GameCollisionManager::Is_Name_PresentList(const char* Name, CollisionObject* Address)
{
	//ハッシュ値に変換
	uint32_t hash = GetHashNum(Name);
	//マップの中から該当するハッシュ値の要素を探す
	auto it = m_collisionMap.find(hash);
	//イテレーターが要素外であればfalse
	if (it == m_collisionMap.end()) 
	{
		return nullptr;
	}

	//次にイテレーターのコリジョンが有効かどうかを調べる
	if (auto shared = it->second.m_collisionPtr.lock())
	{
		return shared.get();
	}
	else
	{
		return nullptr;
	}
}

//マネージャー初期化
void GameCollisionManager::InitCollisionManager()
{

}

//マネージャー更新
void GameCollisionManager::UpdateCollisionManager()
{
	//リスト消去処理
	DeleteList();
}

void GameCollisionManager::DeleteList()
{
	//マップの要素分回す
	for (auto it = m_collisionMap.begin();
		it != m_collisionMap.end();)
	{
		//要素内のコリジョンが有効かどうかを調べる
		if (nullptr == it->second.m_collisionPtr.lock())
		{
			//リスト削除処理
			it = m_collisionMap.erase(it);
		}
		else
		{
			//次の要素へ
			it++;
		}
	}

}

void GameCollisionManager::SetCollisionEnable(
	CollisionObject* collision,
	bool is
)
{
	for (auto it = m_collisionMap.begin(); it != m_collisionMap.end(); it++)
	{
		auto shared = it->second.m_collisionPtr.lock();

		//その要素のコリジョンが有効かどうかを調べる
		if (nullptr == shared)
		{
			continue;
		}

		//要素のコリジョンがアドレスと同じか調べる
		if (collision == shared.get())
		{
			it->second.m_isValid = is;
		}
	}
}
