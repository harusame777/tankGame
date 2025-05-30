#pragma once
#include "StateBase.h"

class GameTitle;
class GameLoadingScreen;

class GameTitleState : public StateBase
{
	appState(GameTitleState);
public: 
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameTitleState() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~GameTitleState() {};
	/// <summary>
	/// 初期化
	/// </summary>
	void Enter() override;
	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;
	/// <summary>
	/// 終了
	/// </summary>
	void Exit() override;
	/// <summary>
	/// ステート遷移
	/// </summary>
	/// <param name="request"></param>
	/// <returns></returns>
	bool RequestState(uint32_t& request) override;
private:
	/// <summary>
	/// フェードアウトしたか？
	/// </summary>
	bool m_fadeOutFlag = false;
	/// <summary>
	/// ゲームタイトルのインスタンス
	/// </summary>
	GameTitle* m_gameTitle = nullptr;
	/// <summary>
	/// ロード画面
	/// </summary>
	GameLoadingScreen* m_gameLoad = nullptr;
};

