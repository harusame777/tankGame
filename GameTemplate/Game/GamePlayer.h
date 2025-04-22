#pragma once

class TankMovingComponent;

class GamePlayer : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GamePlayer() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GamePlayer() {};
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
	/// 履帯モデル
	/// </summary>
	ModelRender m_tankCrawkerTrack;
	/// <summary>
	/// 砲塔モデル
	/// </summary>
	ModelRender m_tankTurret;
	/// <summary>
	/// 戦車移動コンポーネント
	/// </summary>
	TankMovingComponent* m_tankMovingComponent = nullptr;

	Vector3 m_pos = Vector3::AxisZ;
	Vector3 m_forward = Vector3::AxisZ;

	//移動テスト
	Vector3 padVector;
	float maxMoveSpeed = 10.0f;
	float acceleration = 5.0f;
	float deceleration = 4.0f;
	float friction = 2.0f;
	CharacterController characterController;
	float rotSpeed = 0.0f;
};

