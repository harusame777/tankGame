#pragma once

#include "CannonballObjectBase.h"

class Cannonball : 
public IGameObject , 
public CannonballObjectBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Cannonball() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Cannonball() {};
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
	/// レンダリング関数
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// 砲弾のモデル
	/// </summary>
	ModelRender m_cannonballModel;

};

