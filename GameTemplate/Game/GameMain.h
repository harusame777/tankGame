#pragma once

class GameMainContextClass;
class GameLoad;


class GameMain : public IGameObject
{
public:
	/// <summary>
	/// ステート
	/// </summary>
	enum GameMainState
	{
		en_outGame,

		en_inGame,

		enum_Num,
	};
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
	void ChangeGameMainState(GameMainState switchingGameMainState)
	{
		m_gameMainState = switchingGameMainState;
	}
private:
	/// <summary>
	/// ロードのインスタンス
	/// </summary>
	GameLoad* m_gameLoad = nullptr;
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
	/// ゲームメイン設定
	/// </summary>
	/// <param name="gameMainAddress"></param>
	void SetGameMainAddress(GameMain* gameMainAddress)
	{
		this->m_gameMain = gameMainAddress;
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
public: 
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="state"></param>
	GameMainContextClass(
		GameMainStateClass* state
		,GameMain* gameMainAddress = nullptr)
		: m_state(nullptr)
	{
		if (m_state != nullptr)
		{
			delete this->m_state;
		}
		this->m_state = state;
		this->m_state->SetContext(this);
		this->m_state->SetGameMainAddress(gameMainAddress);
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