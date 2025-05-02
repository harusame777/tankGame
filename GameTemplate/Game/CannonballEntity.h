#pragma once

class CannonballAttributeBase;

class CannonballEntity : public IGameObject
{
public:
	enum EnCannonballState
	{
		//初期化
		en_init,
		//弾道計算
		en_trajectoryCalc,
		//移動処理
		en_move,
		//削除処理
		en_delete
	};
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CannonballEntity() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~CannonballEntity() {};
	/// <summary>
	/// 砲弾の移動計算クラスのインスタンスを設定
	/// </summary>
	/// <param name="calcPtr"></param>
	void SetCannonballAttribute(std::shared_ptr<CannonballAttributeBase> attributePtr)
	{
		m_cannonballAttributePtr = attributePtr;
	}
	/// <summary>
	/// 位置設定
	/// </summary>
	/// <param name="position"></param>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
	/// <summary>
	/// 位置を取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition() const
	{
		return m_position;
	}
	/// <summary>
	/// 正面ベクトルを設定
	/// </summary>
	/// <param name="forward"></param>
	void SetForward(const Vector3& forward)
	{
		m_forward = forward;
	}
	/// <summary>
	/// 回転を設定
	/// </summary>
	/// <param name="rotation"></param>
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}
	/// <summary>
	/// 回転を取得
	/// </summary>
	/// <returns></returns>
	const Quaternion& GetRotation() const
	{
		return m_rotation;
	}
	/// <summary>
	/// 正面ベクトルを取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetForward() const
	{
		return m_forward;
	}
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
	/// 位置
	/// </summary>
	Vector3 m_position = Vector3::Zero;
	/// <summary>
	/// 回転
	/// </summary>
	Quaternion m_rotation = Quaternion::Identity;
	/// <summary>
	/// 正面ベクトル
	/// </summary>
	Vector3 m_forward = Vector3::AxisZ;
	/// <summary>
	/// ステート
	/// </summary>
	EnCannonballState m_cannonballState = EnCannonballState::en_init;
	/// <summary>
	/// 砲弾移動計算
	/// </summary>
	std::shared_ptr<CannonballAttributeBase> m_cannonballAttributePtr = nullptr;
	/// <summary>
	/// 砲弾のモデル
	/// </summary>
	ModelRender m_cannonballModel;
};

