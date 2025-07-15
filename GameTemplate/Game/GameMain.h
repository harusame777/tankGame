#pragma once

class GameMainContextClass;
class GameLoadingScreen;

class GameMainStateMachine;


class GameMain : public IGameObject
{
public:
	enum class LoadOrDelete
	{
		en_fadeOut,				//フェードアウト
		en_fadeIn,				//フェードイン
		en_modeLoad,			// ロード
		en_modeDelete,			// 削除
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
private:
	/// <summary>
	/// ロードか削除か
	/// </summary>
	LoadOrDelete m_desiredState = LoadOrDelete::en_modeLoad;	
	/// <summary>
	/// ロードのインスタンス
	/// </summary>
	GameLoadingScreen* m_gameLoad = nullptr;
	/// <summary>
	/// ステートマシン
	/// </summary>
	GameMainStateMachine* m_gameMainStateMachine = nullptr;
};
