#pragma once

class TankCrawkerMovingComponent;
class TankTurretMovingComponent;

class GamePlayer : public IGameObject
{
public:
	enum EnPlayerState
	{
		//待機
		en_idle,
		//移動
		en_moving,
		//ロード待機など
		en_standby,
	};
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GamePlayer() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GamePlayer() {};
	/// <summary>
	/// ステート変更
	/// </summary>
	/// <param name="changeState"></param>
	void ChangeState(const EnPlayerState changeState)
	{
		m_playerState = changeState;
	}
	/// <summary>
	/// ステートを取得
	/// </summary>
	/// <returns></returns>
	const EnPlayerState GetState() const
	{
		return m_playerState;
	}
	/// <summary>
	/// プレイヤーの位置座標の取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition() const
	{
		return m_position;
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
	/// <summary>	/// <summary>
	/// 履帯モデル
	/// </summary>
	ModelRender m_tankCrawkerTrack;
	/// <summary>
	/// 砲塔モデル
	/// </summary>
	ModelRender m_tankTurret;
	/// </summary>
	/// プレイヤーのステート
	/// </summary>
	EnPlayerState m_playerState = EnPlayerState::en_idle;
	/// <summary>
	/// 戦車移動コンポーネント
	/// </summary>
	TankCrawkerMovingComponent* m_tankMovingComponent = nullptr;
	/// <summary>
	/// 戦車砲塔コンポーネント
	/// </summary>
	TankTurretMovingComponent* m_tankTurretMovingComponent = nullptr;
	/// <summary>
	/// 当たり判定
	/// </summary>
	std::shared_ptr<CollisionObject> m_collision;
	/// <summary>
	/// 履帯位置
	/// </summary>
	Vector3 m_position = Vector3::AxisZ;
	/// <summary>
	/// 砲塔位置
	/// </summary>
	Vector3 m_turretPosition = Vector3::Zero;
	/// <summary>
	/// 正面ベクトル
	/// </summary>
	Vector3 m_forward = Vector3::AxisZ;
	/// <summary>
	/// 砲塔正面ベクトル
	/// </summary>
	Vector3 m_turretForward = Vector3::AxisZ;

	//移動テスト
	Vector3 padLVector;
	Vector3 padRVector;
	float maxMoveSpeed = 100.0f;
	float acceleration = 5.0f;
	float deceleration = 4.0f;
	float friction = 2.0f;
	CharacterController characterController;
	float rotSpeed = 10.0f;
};

