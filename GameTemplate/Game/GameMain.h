#pragma once

class GameMainContextClass;

/// <summary>
/// ステート
/// </summary>
enum GameMainState
{
	en_outGame,

	en_inGame,

	enum_Num,
};

class GameMain : IGameObject
{
public:
	/// <summary>
	/// スタート関数
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// コンテキストリスト
	/// </summary>
	GameMainContextClass* m_contextList[enum_Num];
	/// <summary>
	/// ゲームメインステート
	/// </summary>
	GameMainState m_gameMainState = GameMainState::en_outGame;
};

class GameMainStateClass
{
protected:
	/// <summary>
	/// コンテキスト
	/// </summary>
	GameMainContextClass* m_context = nullptr;
	/// <summary>
	/// ゲームメインのインスタンス
	/// </summary>
	GameMain* m_gameMain = nullptr;
public:
	GameMainStateClass(GameMain* gameMain)
	{
		m_gameMain = gameMain;
	}
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~GameMainStateClass() 
	{
	
	};
	/// <summary>
	/// コンテキスト設定
	/// </summary>
	/// <param name="context"></param>
	void SetContext(GameMainContextClass* context)
	{
		m_context = context;
	}
	/// <summary>
	/// ゲームメインステート切り替え
	/// </summary>
	void SwitchingGameMainState(GameMainState gameMainState)
	{
		
	}
	/// <summary>
	/// 純粋仮想関数
	/// ステートアップデート
	/// </summary>
	virtual void GameStateUpdate() = 0;
};

class GameMainContextClass
{
private:
	/// <summary>
	/// ステート
	/// </summary>
	GameMainStateClass* m_state = nullptr;
public: 
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="state"></param>
	GameMainContextClass(GameMainStateClass* state) : m_state(nullptr) 
	{
		if (m_state != nullptr)
		{
			delete this->m_state;
		}
		this->m_state = state;
		this->m_state->SetContext(this);
	};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameMainContextClass() 
	{
		delete m_state;
	};
	/// <summary>
	/// 継承したクラスのステートアップデートを行う
	/// </summary>
	void RequestGameStateUpdate()
	{
		this->RequestGameStateUpdate();
	}
};