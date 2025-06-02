#pragma once

class GamePlayer;

class GamePlayerManager
{
private:
	/// <summary>
	/// インスタンス
	/// </summary>
	static GamePlayerManager* m_gamePlayerManagerInstance;
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GamePlayerManager() {};
	/// <summary>
	/// コピー禁止
	/// </summary>
	/// <param name=""></param>
	GamePlayerManager(const GamePlayerManager&) = delete;
	/// <summary>
	/// 代入禁止
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	GamePlayerManager& operator = (const GamePlayerManager&) = delete;
public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GamePlayerManager() {};
	/// <summary>
	/// インスタンス作成、または取得	
	/// </summary>
	/// <returns></returns>
	static GamePlayerManager* GetGamePlayerManagerInstance()
	{
		if (m_gamePlayerManagerInstance == nullptr)
		{
			m_gamePlayerManagerInstance = new GamePlayerManager();
		}

		return m_gamePlayerManagerInstance;
	}
	/// <summary>
	/// ゲームプレイヤーマネージャーの初期化関数
	/// </summary>
	void InitGamePlayerManager();
	/// <summary>
	/// ゲームプレイヤーを作成する関数
	/// </summary>
	void CreateGamePlayer();
	/// <summary>
	/// ゲームプレイヤーのインスタンスを取得する関数
	/// </summary>
	/// <returns></returns>
	GamePlayer* GetGamePlayerInstance() const
	{
		return m_gamePlayer;
	}
	/// <summary>
	/// プレイヤーが移動可能かどうかを設定する関数
	/// </summary>
	/// <param name="isMoving"></param>
	void SetIsGamePlayerCanMoving(const bool isCanMoving);
	/// <summary>
	/// ゲームプレイヤーが移動が移動可能かどうかを取得する関数
	/// </summary>
	/// <returns></returns>
	bool IsGamePlayerCanMoving() const;
	/// <summary>
	/// ゲームプレイヤーマネージャーの更新関数
	/// </summary>
	void UpdateGamePlayerManager();
private:
	/// <summary>
	/// ゲームプレイヤー
	/// </summary>
	GamePlayer* m_gamePlayer = nullptr; 

};

