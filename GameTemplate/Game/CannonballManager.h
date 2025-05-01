#pragma once

#include "CannonballAttribute.h"

namespace CannonballManagerConstant {
	const int maxCannonball = 100;
}

class CannonballEntity;
class CannonballAttributeBase;
class CannonballAttributeRegistry;

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
	/// <summary>
	/// 砲弾を発射し、発射した砲弾のアドレスを取得する関数
	/// </summary>
	/// <returns></returns>
	void RequestFiringCannonball(const EnCannonballAttribute cannonballAttribute);
private:
	struct CannonballData
	{
	public:
		/// <summary>
		/// 砲弾のポインタ
		/// </summary>
		CannonballEntity* m_cannonballPtr = nullptr;
		/// <summary>
		/// 砲弾生存時間
		/// </summary>
		float m_timer = 0.0f;
		/// <summary>
		/// 使用中か否か
		/// </summary>
		bool m_isUse = false;
	};
	/// <summary>
	/// 新しい砲弾を作成する
	/// </summary>
	/// <returns></returns>
	void CreateNewCannonball(const EnCannonballAttribute cannonballAttribute);
	/// <summary>
	/// 砲弾の種類から計算方法を取得
	/// </summary>
	/// <returns></returns>
	CannonballAttributeBase* GetCannonballCalc(const EnCannonballAttribute cannonballAttribute);
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
	/// 砲弾のリスト
	/// </summary>
	std::vector<CannonballData> m_cannonballList;
};

