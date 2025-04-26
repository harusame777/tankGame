#pragma once

class Cannonball;

class CannonballManager : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CannonballManager() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~CannonballManager() {};
private:
	/// <summary>
	/// 砲弾のリストデータ構造体
	/// </summary>
	struct CannonballListData
	{
		
	};
	/// <summary>
	/// スタート関数
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// アップデート関数
	/// </summary>
	void Update();
};

