#pragma once

#include "CannonballObjectBase.h"

class CannonballEntity : 
public CannonballObjectBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CannonballEntity();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~CannonballEntity() {};
private:
	/// <summary>
	/// 砲弾のモデル
	/// </summary>
	ModelRender m_cannonballModel;
};

