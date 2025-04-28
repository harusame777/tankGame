#pragma once

namespace CannonballManagerConstant {
	const int maxCannonball = 100;
}

class CannonballEntity;
class CannonballObjectBase;

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
	const std::unique_ptr<CannonballEntity>& FiringCannonball();
private:
	/// <summary>
	/// 砲弾のリストデータ構造体
	/// </summary>
	struct CannonballListData
	{
	private:
		/// <summary>
		/// 使用中か
		/// </summary>
		bool m_isUse = false;
		/// <summary>
		/// 砲弾
		/// </summary>
		std::unique_ptr<CannonballEntity> m_cannonballObject = nullptr;
	public:

		const bool IsDataUse() const
		{
			return m_isUse;
		}

	};
	/// <summary>
	/// 砲弾リストに空きがあるかどうか調べる関数
	/// 未使用の砲弾があるとtrueを返す
	/// </summary>
	/// <returns></returns>
	bool IsThereSpaceOnList();
	/// <summary>
	/// 新しい砲弾を作成し、そのアドレスを取得する
	/// </summary>
	const std::unique_ptr<CannonballEntity>& CreateNewCannonballAndGetAddress();
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
	std::vector<CannonballListData> m_cannonballList;
};

