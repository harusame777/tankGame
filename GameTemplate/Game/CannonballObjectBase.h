#pragma once

class CannonballStateBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CannonballStateBase() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~CannonballStateBase() {};
	/// <summary>
	/// 純粋仮想関数、ステート初期化
	/// </summary>
	virtual void InitState() = 0;
	/// <summary>
	/// 純粋仮想関数、ステート更新
	/// </summary>
	virtual void UpdateState() = 0;
	/// <summary>
	/// 純粋仮想関数、ステート終了
	/// </summary>
	virtual void EndState() = 0;
};

class CannonballObjectBase
{
public:
	enum EnCannonballState
	{
		//初期化
		en_init,
		//
		en_moving,

		en_end,

		en_stateNum,
	};
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CannonballObjectBase() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~CannonballObjectBase() {};
	/// <summary>
	/// ステート更新関数
	/// </summary>
	void UpdateCannonballState()
	{
		
		//ステート更新
		m_cannonballStateList[m_currentState]->UpdateState();

		//ステートの変更判定
		if (m_currentState != m_requestState)
		{
			//ステートが終了する時の処理を実行
			m_cannonballStateList[m_currentState]->EndState();
			//ステート変更
			m_currentState = m_requestState;
			//ステートの初期化処理
			m_cannonballStateList[m_currentState]->InitState();
		}
	}
	/// <summary>
	/// ステートを変更する
	/// </summary>
	/// <param name="changeState"></param>
	void ChangeState(const EnCannonballState changeState)
	{
		m_requestState = changeState;
	}
	/// <summary>
	/// ステート配列
	/// </summary>
	CannonballStateBase* m_cannonballStateList[EnCannonballState::en_stateNum] = {nullptr};
	/// <summary>
	/// 現在のステート
	/// </summary>
	EnCannonballState m_currentState = EnCannonballState::en_init;
	/// <summary>
	/// リクエストされたステート
	/// </summary>
	EnCannonballState m_requestState = EnCannonballState::en_init;
};

