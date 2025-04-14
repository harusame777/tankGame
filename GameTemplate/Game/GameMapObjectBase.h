#pragma once

class GameMapObjectBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameMapObjectBase() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~GameMapObjectBase() {};
private:
	/// <summary>
	/// 位置座標
	/// </summary>
	Vector3 m_position = Vector3::Zero;
	/// <summary>
	/// 回転値
	/// </summary>
	Quaternion m_rotation = Quaternion::Identity;
	/// <summary>
	/// 拡大率
	/// </summary>
	Vector3 m_scale = Vector3::One;
public:
	/// <summary>
	/// 位置設定
	/// </summary>
	/// <param name="position"></param>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
	/// <summary>
	/// 位置取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition() const
	{
		return m_position;
	}
	/// <summary>
	/// 回転設定
	/// </summary>
	/// <param name="rotation"></param>
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}
	/// <summary>
	/// 回転取得
	/// </summary>
	/// <returns></returns>
	const Quaternion& GetRotation() const
	{
		return m_rotation;
	}
	/// <summary>
	/// 拡大率設定
	/// </summary>
	/// <param name="scale"></param>
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}
	/// <summary>
	/// 拡大率取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetScale() const
	{
		return m_scale;
	}
};

