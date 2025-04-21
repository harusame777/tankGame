#pragma once
class GamePlayer : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GamePlayer() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GamePlayer() {};
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
	/// 履帯モデル
	/// </summary>
	ModelRender m_tankCrawkerTrack;
	/// <summary>
	/// 砲塔モデル
	/// </summary>
	ModelRender m_tankTurret;

};

