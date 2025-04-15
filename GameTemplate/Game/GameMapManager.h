#pragma once
#include "GameMapObjectBase.h"

class GameMapManager : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameMapManager() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameMapManager() {};
private:
	/// <summary>
	/// スタート関数
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// アップデート関数
	/// </summary>
	void Update();
	/// <summary>
	/// オブジェクトリスト
	/// </summary>
	std::vector<GameMapObjectBase*> m_gameMapObjectList;
	/// <summary>
	/// 引数のオブジェクトをリストに登録
	/// </summary>
	/// <param name="object"></param>
	void SetObjectList(GameMapObjectBase* object)
	{
		m_gameMapObjectList.push_back(object);
	}
};

