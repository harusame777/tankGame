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

class GameMain : public IGameObject
{
public:
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
	/// ゲームメインステート切り替え
	/// </summary>
	void SwitchingGameMainState(GameMainState switchingGameMainState)
	{
		m_gameMainState = switchingGameMainState;
	}
private:
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
public:
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
		this->m_context = context;
	}
	/// <summary>
	/// 純粋仮想関数
	/// ゲーム状態初期化
	/// </summary>
	virtual void InitGameState() = 0;
	/// <summary>
	/// 純粋仮想関数
	/// ゲーム状態更新
	/// </summary>
	virtual void UpdateGameState() = 0;
};

class GameMainContextClass
{
private:
	/// <summary>
	/// ステート
	/// </summary>
	GameMainStateClass* m_state = nullptr;
	/// <summary>
	/// ゲームメインのインスタンス
	/// </summary>
	GameMain* m_gameMain = nullptr;
public: 
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="state"></param>
	GameMainContextClass(GameMainStateClass* state,GameMain* gameMain) 
		: m_state(nullptr),m_gameMain(nullptr)
	{
		if (m_state != nullptr)
		{
			delete this->m_state;
		}
		this->m_state = state;
		this->m_gameMain = gameMain;
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
	/// 継承したクラスのステート初期化を行う
	/// </summary>
	void RequestGameStateInit()
	{
		this->m_state->InitGameState();
	}
	/// <summary>
	/// 継承したクラスのステートアップデートを行う
	/// </summary>
	void RequestGameStateUpdate()
	{
		this->m_state->UpdateGameState();
	}
};