#pragma once

#include "TankShellsAttribute.h"

namespace TankShellsManagerConstant {
	const int maxCannonball = 100;
}

class TankShellsEntity;
class TankShellsAttributeBase;
class TankShellsAttributeRegistry;

class GamePlayer;

class TankShellsManager
{
private:
	/// <summary>
	/// インスタンス
	/// </summary>
	static TankShellsManager* m_tankShellsManagerInstance;
	/// <summary>
	/// コンストラクタ
	/// </summary>
	TankShellsManager() {};
	/// <summary>
	/// コピー禁止
	/// </summary>
	/// <param name=""></param>
	TankShellsManager(const TankShellsManager&) = delete;
	/// <summary>
	/// 代入禁止
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	TankShellsManager& operator = (const TankShellsManager&) = delete;
public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	~TankShellsManager() {};
	/// <summary>
	/// インスタンス作成、または取得
	/// </summary>
	/// <returns></returns>
	static TankShellsManager* GetTankShellsManagerInstance()
	{
		if (m_tankShellsManagerInstance == nullptr)
		{
			m_tankShellsManagerInstance = new TankShellsManager();
		}

		return m_tankShellsManagerInstance;
	}
	/// <summary>
	/// 砲弾マネージャー初期化
	/// </summary>
	void InitTankShellsManager();
	/// <summary>
	/// 砲弾マネージャークラス更新
	/// </summary>
	void UpdateTankShellsManager();
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
	/// 砲弾が何かに当たった時の処理
	/// </summary>
	void HitTankShells(TankShellsEntity* hitShells);
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
		/// <summary>
		/// 消去フラグ
		/// </summary>
		bool m_deleteFlag = false;
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
	/// 砲弾の時間削除処理
	/// </summary>
	void DeleteTankShells();
	/// <summary>
	/// 砲弾のリスト
	/// </summary>
	std::vector<TankShellsData> m_cannonballList;
	/// <summary>
	///	ゲームプレイヤーのインスタンス
	/// </summary>
	GamePlayer* m_player = nullptr;

};

