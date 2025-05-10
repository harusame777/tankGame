#pragma once
#include "GameMapObjectBase.h"

class GameMapManager
{
private:
	/// <summary>
	/// インスタンス
	/// </summary>
	static GameMapManager* m_gameMapManagerInstance;
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameMapManager() {};
	/// <summary>
	/// コピー禁止
	/// </summary>
	/// <param name=""></param>
	GameMapManager(const GameMapManager&) = delete;
	/// <summary>
	/// 代入禁止
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	GameMapManager& operator = (const GameMapManager&) = delete;
public:
	/// <summary>
	/// インスタンス作成、または取得
	/// </summary>
	/// <returns></returns>
	static GameMapManager* GetCollisionManagerInstance()
	{
		if (m_gameMapManagerInstance == nullptr)
		{
			m_gameMapManagerInstance = new GameMapManager();
		}

		return m_gameMapManagerInstance;
	}
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameMapManager() {};
	/// <summary>
	/// 初期化
	/// </summary>
	void InitGameMapManager();
	/// <summary>
	/// アップデート関数
	/// </summary>
	void UpdateGameMapManager();
private:
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

