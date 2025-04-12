#pragma once

class GameTitle : public IGameObject
{
public:
	/// <summary>
	/// ゲームタイトルのステート
	/// </summary>
	enum GameTitleState
	{
		//待機状態
		en_standby,
		//実行状態
		en_update,
	};
private:
	/// <summary>
	/// ゲームタイトルのステート
	/// </summary>
	GameTitleState m_gameTitleState = GameTitleState::en_standby;
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameTitle() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameTitle() {};
	/// <summary>
	/// ゲームタイトルを起動する
	/// </summary>
	void BootGameTitle()
	{
		if (m_gameTitleState != GameTitleState::en_standby)
		{
			return;
		}

		m_gameTitleState = GameTitleState::en_update;
	}
	/// <summary>
	/// ゲームタイトルを停止する
	/// </summary>
	void StopGameTitle()
	{
		if (m_gameTitleState != GameTitleState::en_update)
		{
			return;
		}

		m_gameTitleState = GameTitleState::en_standby;
	}
	/// <summary>
	/// ゲームタイトルが起動中かどうか
	/// </summary>
	/// <returns></returns>
	bool IsGameTitleBoot()
	{
		if (m_gameTitleState == GameTitleState::en_standby)
		{
			return false;
		}
		else
		{
			return true;
		}
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
	/// ゲームタイトル更新
	/// </summary>
	void GameTitleUpdate();
	/// <summary>
	/// レンダー関数
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
};

