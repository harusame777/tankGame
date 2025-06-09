#pragma once

class EnemyAttackPoint
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyAttackPoint() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyAttackPoint() {};
	/// <summary>
	/// 半径設定
	/// </summary>
	/// <param name="radius"></param>
	void SetRadius(const float radius)
	{
		m_radius = radius;
	}
	/// <summary>
	/// 半径取得
	/// </summary>
	/// <returns></returns>
	const float GetRadius() const
	{
		return m_radius;
	}
	/// <summary>
	/// 半径2乗取得
	/// </summary>
	const float GetRadiusSq() const 
	{
		return m_radius * m_radius;
	}
	/// <summary>
	/// 設置方向を設定
	/// </summary>
	/// <param name="direction"></param>
	void SetDirection(const Vector3& direction)
	{
		m_direction = direction;
	}
	/// <summary>
	/// 設置位置を取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetDirection() const
	{
		return m_direction;
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
	/// 位置取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition() const
	{
		return m_position;
	}
private:
	/// <summary>
	/// 座標
	/// </summary>
	Vector3 m_position = Vector3::Zero;
	/// <summary>
	/// 設置方向
	/// </summary>
	Vector3 m_direction = Vector3::AxisZ;
	/// <summary>
	/// 感知半径
	/// </summary>
	float m_radius = 0.0f;
};

