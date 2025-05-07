#pragma once

#include "TankShellsAttribute.h"

namespace TankShellsManagerConstant {
	const int maxCannonball = 100;
}

class TankShellsEntity;
class TankShellsAttributeBase;
class TankShellsAttributeRegistry;

class GamePlayer;

class TankShellsManager : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	TankShellsManager() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~TankShellsManager() {};
	/// <summary>
	/// 砲弾を発射し、発射した砲弾のアドレスを取得する関数
	/// </summary>
	/// <returns></returns>
	void RequestFiringTankShells(
		const EnTankShellsAttribute tankShellsAttribute,
		const Vector3& firingPosition,
		const Vector3& firingForward
	);
	/// <summary>
	/// プレイヤーのポインタを取得
	/// </summary>
	/// <returns></returns>
	GamePlayer* GetPlayerPtr() const
	{
		return m_player;
	}
private:
	struct TankShellsData
	{
	public:
		/// <summary>
		/// 砲弾のポインタ
		/// </summary>
		TankShellsEntity* m_tankShellsPtr = nullptr;
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
	void CreateNewTankShells(
		const EnTankShellsAttribute tankShellsAttribute,
		const Vector3& firingPosition,
		const Vector3& firingForward
	);
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
	/// 砲弾の時間削除処理
	/// </summary>
	void DeleteTankShellsIsTime();
	/// <summary>
	/// 砲弾のリスト
	/// </summary>
	std::vector<TankShellsData> m_cannonballList;
	/// <summary>
	///	ゲームプレイヤーのインスタンス
	/// </summary>
	GamePlayer* m_player = nullptr;

};

