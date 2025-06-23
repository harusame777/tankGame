#pragma once

class StateMachineBase;
class EnemyTankStateMachine;
class GamePlayer;
class EnemyTankAttributeBase;
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
	/// 敵戦車のIDを設定します。
	/// </summary>
	/// <param name="enemyTankId">設定する敵戦車のID。</param>
	void SetEnemyTankId(int enemyTankId)
	{
		m_myId = enemyTankId;
	}
	/// <summary>
	/// 敵戦車のIDを取得します。
	/// </summary>
	/// <returns>敵戦車のID（整数値）。</returns>
	int GetEnemyTankId() const
	{
		return m_myId;
	}
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
	/// <summary>
	/// ゲームプレイヤーのインスタンスを設定
	/// </summary>
	/// <param name="playerPtr"></param>
	void SetGamePlayerInstance(GamePlayer* playerPtr)
	{
		m_player = playerPtr;
	}
	/// <summary>
	/// 属性を設定
	/// </summary>
	/// <param name="setAttribute"></param>
	void SetAttribute(std::shared_ptr<EnemyTankAttributeBase> setAttribute)
	{
		m_enemyTankAttribute = setAttribute;
	}
	/// <summary>
	/// 射撃フラグ設定
	/// </summary>
	/// <param name="isFire"></param>
	void SetFireFlag(bool isFire)
	{
		m_fireFlag = isFire;
	}
	/// <summary>
	/// コリジョンが有効かどうかを設定します。
	/// </summary>
	/// <param name="isEnable"></param>
	void SetCollisionEnable(bool isEnable);
	/// <summary>
	/// 描画フラグ設定
	/// </summary>
	/// <param name="isDraw"></param>
	void SetDrawFlag(const bool isDraw)
	{
		m_drawFlag = isDraw;
	}
	/// <summary>
	/// 戦車の砲塔移動コンポーネントへの参照を取得します。
	/// </summary>
	/// <returns>TankTurretMovingComponent オブジェクトへの定数参照。</returns>
	TankTurretMovingComponent& GetTurretCompornentAddress() const
	{
		return *m_tankTurretMovingCom;
	}
	/// <summary>
	/// 削除フラグを設定します。
	/// </summary>
	/// <param name="is">削除フラグとして設定する値。</param>
	/// <returns>なし。</returns>
	void SetDeleteFlag(bool is)
	{
		m_isDeleteFlag = is;
	}
	/// <summary>
	/// 削除フラグを取得します。
	/// </summary>
	/// <returns>削除フラグが設定されていれば true、そうでなければ false を返します。</returns>
	bool GetDeleteFlag() const
	{
		return m_isDeleteFlag;
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
	Vector3 m_targetForward = Vector3::Zero;
	/// <summary>
	/// 履帯モデル
	/// </summary>
	ModelRender m_tankCrawkerTrack;
	/// <summary>
	/// 砲塔モデル
	/// </summary>
	ModelRender m_tankTurret;
	/// <summary>
	/// デリートフラグ
	/// </summary>
	bool m_isDeleteFlag = false;
	/// <summary>
	/// 射撃フラグ
	/// </summary>
	bool m_fireFlag = false;
	/// <summary>
	/// 描画フラグ
	/// </summary>
	bool m_drawFlag = true;
	/// <summary>
	/// このエネミータンクの属性
	/// </summary>
	std::shared_ptr<EnemyTankAttributeBase> m_enemyTankAttribute = nullptr;
	/// <summary>
	/// 当たり判定
	/// </summary>
	std::shared_ptr<CollisionObject> m_collision;
	/// <summary>
	/// ゲームプレイヤーのインスタンス
	/// </summary>
	GamePlayer* m_player;
	/// <summary>
	/// ID格納変数
	/// </summary>
	int m_myId = 0;
	
	float m_moveSpeed = 50.0f;
	float maxMoveSpeed = 50.0f;
	CharacterController characterController;
	float rotSpeed = 10.0f;
};

