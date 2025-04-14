#pragma once
#include "GameMapObjectBase.h"

class MapObjectFloor :
	public IGameObject,
	public GameMapObjectBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	MapObjectFloor() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~MapObjectFloor() {};
private:
};

