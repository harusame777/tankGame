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
	/// <summary>
	/// ゲームメインを経由して他のリストのステートを変更
	/// </summary>
	/// <param name="switchingGameOutState"></param>
	void ChangeContextListState(GameMainState changeMainState, int changeListStateNum);
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
	/// <summary>
	/// ステートナンバー
	/// </summary>
	int m_stateNum = 0;
	/// <summary>
	/// ステート最大数
	/// </summary>
	int m_stateNumMax = 0;
	/// <summary>
	/// 外部からステートが変更されたか判定
	/// </summary>
	bool m_isStateChange = false;
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
	/// ステートの最大数を設定
	/// </summary>
	/// <param name="stateMax"></param>
	void SetGameStateMax(int stateMax)
	{
		m_stateNumMax = stateMax;
	}
	/// <summary>
	/// ステートを変更する
	/// </summary>
	/// <param name="stateNumber"></param>
	void SetGameStateNumber(int stateNumber)
	{
		m_stateNum = stateNumber;
		//ステートが外部から変更されたと伝える
		m_isStateChange = true;
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
		,GameMain* gameMainAddress = nullptr
		,int stateMax = 0)
		: m_state(nullptr)
	{
		if (m_state != nullptr)
		{
			delete this->m_state;
		}
		this->m_state = state;
		this->m_state->SetContext(this);
		this->m_state->SetGameMainAddress(gameMainAddress);
		this->m_state->SetGameStateMax(stateMax);
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
	/// <summary>
	/// 外部からステートを変更する関数
	/// </summary>
	/// <param name="stateNumber"></param>
	void RequestGameStateChange(int stateNumber)
	{
		this->m_state->SetGameStateNumber(stateNumber);
	}
};