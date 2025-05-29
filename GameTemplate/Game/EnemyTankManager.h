#pragma once

namespace TankManagerConstant
{
	const float initDeleteDelayTime = 0.1f;
}

#include "EnemyTankAttribute.h"

class EnemyTankAttribute;
class EnemyTankEntity;
class GamePlayer;

class EnemyTankManager
{
private:
	/// <summary>
	/// インスタンス
	/// </summary>
	static EnemyTankManager* m_enemyTankManagerInstance;
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyTankManager() {};
	/// <summary>
	/// コピー禁止
	/// </summary>
	/// <param name=""></param>
	EnemyTankManager(const EnemyTankManager&) = delete;
	/// <summary>
	/// 代入禁止
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	EnemyTankManager& operator = (const EnemyTankManager&) = delete;
public:
	struct EnemyTankData
	{
		/// <summary>
		/// 敵タンクポインタ
		/// </summary>
		EnemyTankEntity* m_enemyTankPtr = nullptr;
		/// <summary>
		/// デリートフラグ
		/// </summary>
		bool m_deleteFlag = false;
		/// <summary>
		/// 削除遅延
		/// </summary>
		float m_deleteDelayTime = TankManagerConstant::initDeleteDelayTime;
	};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyTankManager() {};
	/// <summary>
	/// インスタンス作成、または取得	
	/// </summary>
	/// <returns></returns>
	static EnemyTankManager* GetEnemyTankManagerInstance()
	{
		if (m_enemyTankManagerInstance == nullptr)
		{
			m_enemyTankManagerInstance = new EnemyTankManager();
		}

		return m_enemyTankManagerInstance;
	}
	/// <summary>
	/// 敵タンクマネージャー初期化
	/// </summary>
	void InitEnemyTankManager();
	/// <summary>
	/// 敵タンクマネージャークラス更新
	/// </summary>
	void UpdateEnemyTankManager();

	void CreateNewEnemyTank(
		EnEnemyTankAttribute attribute,
		const Vector3& createPos
	);
	/// <summary>
	/// 削除フラグを有効にする
	/// </summary>
	void ActivateDeleteFlag(EnemyTankEntity* subjectEnemyTank);
private:
	/// <summary>
	/// リスト削除
	/// </summary>
	void DeleteList();
	/// <summary>
	/// データが削除条件を満たしているかどうか
	/// </summary>
	/// <param name="listData"></param>
	/// <returns></returns>
	const bool IsDataDelteConditions(EnemyTankData* listData)
	{
		//削除条件判定
		if (listData->m_deleteFlag == true)
		{
			return true;
		}
		return false;
	}
	/// <summary>
	/// 敵タンクリスト
	/// </summary>
	std::vector<EnemyTankData> m_enemyTankList;
	/// <summary>
	/// プレイヤーのインスタンス
	/// </summary>
	GamePlayer* m_player = nullptr;
};

