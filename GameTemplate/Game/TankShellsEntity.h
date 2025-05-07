#pragma once

class TankShellsAttributeBase;

class TankShellsEntity : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	TankShellsEntity() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~TankShellsEntity() {};
	/// <summary>
	/// 砲弾の移動計算クラスのインスタンスを設定
	/// </summary>
	/// <param name="calcPtr"></param>
	void SetTankShellsAttribute(std::shared_ptr<TankShellsAttributeBase> attributePtr)
	{
		m_tankShellsAttributePtr = attributePtr;
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
	/// <summary>
	/// 削除処理
	/// </summary>
	void DeleteGOTankShells();
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
	/// 砲弾移動計算
	/// </summary>
	std::shared_ptr<TankShellsAttributeBase> m_tankShellsAttributePtr = nullptr;
	/// <summary>
	/// 砲弾のモデル
	/// </summary>
	ModelRender m_tankShellsModel;
};

