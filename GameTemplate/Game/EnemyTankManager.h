#pragma once

namespace TankManagerConstant
{
	const float initDeleteDelayTime = 0.1f;
}

#include "EnemyTankAttribute.h"
#include "EventManager.h"

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
	/// <summary>
	/// 新規エネミータンク作成
	/// </summary>
	/// <param name="attribute"></param>
	/// <param name="createPos"></param>
	int CreateNewEnemyTank(
		EnEnemyTankAttribute attribute,
		const Vector3& createPos
	);
	/// <summary>
	/// エネミータンクのリストを取得する
	/// </summary>
	/// <returns></returns>
	std::vector<int> GetEnemyTankList();
	/// <summary>
	/// 削除フラグを有効にする
	/// </summary>
	void ActivateDeleteFlag(int enemyTankId);
	/// <summary>
	/// 指定された敵戦車IDの削除フラグを取得します。
	/// </summary>
	/// <param name="enemyTankId">削除フラグを取得する敵戦車のID。</param>
	/// <returns>敵戦車が削除対象であれば true、そうでなければ false。</returns>
	bool GetIdEnemyTankDeleteFlag(int enemyTankId);
	/// <summary>
	/// 指定されたIDの敵タンクの位置を取得します。
	/// </summary>
	/// <param name="enemyTankId">位置を取得したい敵タンクのID。</param>
	/// <returns>敵タンクが見つかった場合はその位置（Vector3型）への参照。見つからない場合はVector3::Zeroへの参照。</returns>
	const Vector3& GetIdEnemyTankPosition(int enemyTankId);
private:
	/// <summary>
	/// 新しい一意のIDを生成します。
	/// </summary>
	/// <returns>生成された一意の整数ID。</returns>
	int CreateId();
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
	std::unordered_map<int,EnemyTankData> m_enemyTankListMap;
	/// <summary>
	/// 次に使用されるIDを保持する整数変数です。
	/// </summary>
	int m_nextId = 0;
	/// <summary>
	/// 関数で送り返す用のリスト
	/// </summary>
	std::vector<EnemyTankEntity*> m_returnEnemyTankList;
	/// <summary>
	/// 解放されたIDのリストを保持するベクターです。
	/// </summary>
	std::vector<int> m_freeIdList;
	/// <summary>
	/// プレイヤーのインスタンス
	/// </summary>
	GamePlayer* m_player = nullptr;
};

