#pragma once

class GameTitle : public IGameObject
{
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
	/// ゲームタイトルが終了したかどうか
	/// </summary>
	/// <returns></returns>
	bool IsGameTitleEnd()
	{
		return m_isGameTitleEnd;
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
	/// レンダー関数
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// ゲームタイトルが終了したかどうか
	/// </summary>
	bool m_isGameTitleEnd = false;
};

