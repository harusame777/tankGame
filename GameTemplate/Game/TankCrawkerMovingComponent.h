#pragma once
class TankCrawkerMovingComponent
{
public:
	/// <summary>
	/// 正面、後方移動ステート
	/// </summary>
	enum EnFrontRearMoveMode
	{
		//移動しない
		en_neutralFR,
		//正面に移動
		en_moveForward,
		//後方に移動
		en_moveBackward,
	};
	/// <summary>
	/// 左右回転ステート
	/// </summary>
	enum EnLeftRightMoveMode
	{
		//移動しない
		en_neutralLR,
		//左正面に回転
		en_trunLeftForward,
		//左背面に回転
		en_trunLeftBackward,
		//右正面に回転
		en_trunRightForward,
		//右背面に回転
		en_trunRightBackward,
	};
	/// <summary>
	/// コンストラクタ
	/// </summary>
	TankCrawkerMovingComponent() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~TankCrawkerMovingComponent() {};
	/// <summary>
	/// 戦車移動初期化
	/// </summary>
	/// <param name="moveDirection"></param>
	/// <param name="forward"></param>
	/// <param name="maxMoveSpeed"></param>
	/// <param name="characterControoler"></param>
	/// <param name="trunSpeed"></param>
	/// <param name="rotModel"></param>
	void InitTankCrawkerMoveingData(
		Vector3& moveDirection,						//移動方向
		Vector3& forward,							//正面方向
		float& maxMoveSpeed,						//最大速度
		CharacterController& characterControoler,	//キャラコン
		float& trunSpeed,							//回転速度
		ModelRender& rotModel						//回転させるモデル
	);
	/// <summary>
	/// 計算とモデル更新を行う
	/// </summary>
	/// <returns></returns>
	const Vector3& CalcCrawkerMovingDataAndModelUpdate();
	/// <summary>
	/// 現在速度を返す
	/// </summary>
	/// <returns></returns>
	const float GetMoveSpeed()const
	{
		return m_moveSpeed;
	}
private:
	/// <summary>
	/// どう移動するかを判定
	/// </summary>
	const EnFrontRearMoveMode MoveDetermination();
	/// <summary>
	/// どう回転するかを判定
	/// </summary>
	const EnLeftRightMoveMode RotDetermination();
	/// <summary>
	/// 移動計算
	/// </summary>
	void GunnerIsPlayerMoveCalc();
	/// <summary>
	/// 回転計算
	/// </summary>
	void RotateCalc();
	/// <summary>
	/// 正面、後方移動ステート
	/// </summary>
	EnFrontRearMoveMode m_moveFRModeState = EnFrontRearMoveMode::en_neutralFR;
	/// <summary>
	/// 左右回転ステート
	/// </summary>
	EnLeftRightMoveMode m_moveLRModeState = EnLeftRightMoveMode::en_neutralLR;
	/// <summary>
	/// 現在速度
	/// </summary>
	float m_moveSpeed = 0.0f;
	/// <summary>
	/// 現在回転値
	/// </summary>
	Quaternion m_rotaiton = Quaternion::Identity;
	/// <summary>
	/// モデル位置
	/// </summary>
	Vector3 m_modelPosition = Vector3::Zero;
	/// <summary>
	/// 移動方向
	/// </summary>
	Vector3* m_moveDirection = nullptr;
	/// <summary>
	/// 正面方向
	/// </summary>
	Vector3* m_forward = nullptr;
	/// <summary>
	/// 最大速度
	/// </summary>
	float* m_maxMoveSpeed = nullptr;
	/// <summary>
	/// キャラクターコントローラー
	/// </summary>
	CharacterController* m_characterController = nullptr;
	/// <summary>
	/// 回転速度
	/// </summary>
	float* m_trunSpeed = nullptr;
	/// <summary>
	/// 回転させるモデル
	/// </summary>
	ModelRender* m_rotModel = nullptr;
};

