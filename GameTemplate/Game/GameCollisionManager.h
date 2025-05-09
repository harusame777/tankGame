#pragma once

class GameCollisionManager
{
private:
	/// <summary>
	/// コリジョンタイプ
	/// </summary>
	using CollisionType = int;
	/// <summary>
	/// インスタンス
	/// </summary>
	static GameCollisionManager* m_collisionManagerInstance;
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameCollisionManager() {};
	/// <summary>
	/// コピー禁止
	/// </summary>
	/// <param name=""></param>
	GameCollisionManager(const GameCollisionManager&) = delete;
	/// <summary>
	/// 代入禁止
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	GameCollisionManager& operator = (const GameCollisionManager&) = delete;
public:
	/// <summary>
	/// インスタンス作成、または取得
	/// </summary>
	/// <returns></returns>
	static GameCollisionManager* GetCollisionManagerInstance()
	{
		if (m_collisionManagerInstance == nullptr)
		{
			m_collisionManagerInstance = new GameCollisionManager();
		}

		return m_collisionManagerInstance;
	}
	/// <summary>
	/// マネージャーを初期化
	/// </summary>
	void InitCollisionManager();
	/// <summary>
	/// マネージャーを更新
	/// </summary>
	void UpdateCollisionManager();
	/// <summary>
	/// 球状コリジョンを作成
	/// </summary>
	std::shared_ptr<CollisionObject> CreateSphereCollision(
		const Vector3& initPosition = Vector3::Zero,
		const Quaternion& initRotation = Quaternion::Identity,
		float initSize = 1.0f,
		const char* str = "nullName"
	);
	/// <summary>
	/// AのアドレスのコリジョンがBの名前のコリジョンに当たったかどうか
	/// </summary>
	/// <param name="A_ColisionAddress"></param>
	/// <param name="B_ColisionName"></param>
	/// <returns></returns>
	const bool Is_A_ColisionHits_B_Colision(
		CollisionObject* A_ColisionAddress,
		const char* B_ColisionName);
private:
	/// <summary>
	/// コリジョンのリストデータ
	/// </summary>
	struct GameCollisionListData
	{
		/// <summary>
		/// コリジョンオブジェクトポインタ
		/// </summary>
		std::weak_ptr<CollisionObject> m_collisionPtr;
		/// <summary>
		/// 有効かどうか、trueで有効、falseで無効
		/// </summary>
		bool m_isValid = true;
	};
	/// <summary>
	/// ハッシュ値取得
	/// </summary>
	/// <param name="str"></param>
	/// <returns></returns>
	constexpr uint32_t GetHashNum(const char* str);
	/// <summary>
	/// Addressのコリジョンがリストに存在していて、なおかつ有効かどうか
	/// </summary>
	/// <param name="Address"></param>
	/// <returns></returns>
	CollisionObject* Is_Address_PresentList(CollisionObject* Address);
	/// <summary>
	/// Nameのコリジョンがリストに存在していて、なおかつ有効かどうか
	/// </summary>
	/// <param name="Name"></param>
	/// <returns></returns>
	CollisionObject* Is_Name_PresentList(const char* Name,CollisionObject* Address);
	/// <summary>
	/// nameのコリジョンを複数探す
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	const std::vector<CollisionObject*>& FindListCollisionObjects(const char* name);
	/// <summary>
	/// 探したコリジョン
	/// </summary>
	std::vector<CollisionObject*> m_findCollisionObjcts;
	/// <summary>
	/// リスト消去処理
	/// </summary>
	void DeleteList();
	/// <summary>
	/// コリジョンのマップ型配列
	/// </summary>
	std::unordered_map<uint32_t,GameCollisionListData> m_collisionMap;
};

