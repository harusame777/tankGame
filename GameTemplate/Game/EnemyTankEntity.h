#pragma once

class StateMachineBase;
class EnemyTankStateMachine;
class TankCrawkerMovingComponent;
class TankTurretMovingComponent;	

class EnemyTankEntity : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyTankEntity();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyTankEntity() 
	{
		delete m_stateMashine;
		delete m_tankCrawkerMovingCom;
		delete m_tankTurretMovingCom;
	};
	/// <summary>
	/// 移動方向設定
	/// </summary>
	/// <param name="direction"></param>
	void SetMoveDirection(const Vector3& direction)
	{
		m_moveForward = direction;
	}
	/// <summary>
	/// 攻撃方向設定
	/// </summary>
	/// <param name="direction"></param>
	void SetAttackTargetDirection(const Vector3& direction)
	{
		m_targetForward = direction;
	}
	/// <summary>
	/// 位置設定
	/// </summary>
	/// <param name="setPos"></param>
	void SetPosition(const Vector3& setPos)
	{
		m_position = setPos;
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
	/// エネミータンク削除実行
	/// </summary>
	void DeleteGOEnemyTank();
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
	/// ステートマシン
	/// </summary>
	EnemyTankStateMachine* m_stateMashine = nullptr;
	/// <summary>
	/// 戦車移動コンポーネント
	/// </summary>
	TankCrawkerMovingComponent* m_tankCrawkerMovingCom = nullptr;
	/// <summary>
	/// 戦車砲塔移動コンポーネント
	/// </summary>
	TankTurretMovingComponent* m_tankTurretMovingCom = nullptr;
	/// <summary>
	/// 履帯位置
	/// </summary>
	Vector3 m_position = Vector3::AxisZ;
	/// <summary>
	/// 回転値
	/// </summary>
	Quaternion m_rotation = Quaternion::Identity;
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
	/// <summary>
	/// 移動方向ベクトル
	/// </summary>
	Vector3 m_moveForward = Vector3::AxisZ;
	/// <summary>
	/// 攻撃方向ベクトル
	/// </summary>
	Vector3 m_targetForward = Vector3::AxisZ;
	/// <summary>
	/// 履帯モデル
	/// </summary>
	ModelRender m_tankCrawkerTrack;
	/// <summary>
	/// 砲塔モデル
	/// </summary>
	ModelRender m_tankTurret;
	/// <summary>
	/// 当たり判定
	/// </summary>
	std::shared_ptr<CollisionObject> m_collision;

	
	float m_moveSpeed = 50.0f;
	float maxMoveSpeed = 50.0f;
	CharacterController characterController;
	float rotSpeed = 10.0f;
};

