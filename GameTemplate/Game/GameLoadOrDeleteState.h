#pragma once
#include "StateBase.h"
#include "GameMain.h"

class GamePlayer;
class GameLoadingScreen;

class GameLoadOrDeleteState : public StateBase
{
	appState(GameLoadOrDeleteState);
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameLoadOrDeleteState(GameMain::LoadOrDelete* loadordelete)
	{
		m_loadOrDelete = loadordelete;
	};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameLoadOrDeleteState() {};
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
	/// <summary>
	/// ロード処理
	/// </summary>
	void LoadProcces();
	/// <summary>
	/// 削除処理
	/// </summary>
	void DeleteProcces();
private:
	/// <summary>
	/// 処理終了フラグ
	/// </summary>
	bool m_processEndFlag = false;
	/// <summary>
	/// プレイヤーのインスタンス
	/// </summary>
	GamePlayer* m_gamePlayer = nullptr;
	/// <summary>
	/// ロード画面のインスタンス
	/// </summary>
	GameLoadingScreen* m_gameLoad = nullptr;
	/// <summary>
	/// ロードまたは削除の状態
	/// </summary>
	GameMain::LoadOrDelete* m_loadOrDelete = nullptr;
};