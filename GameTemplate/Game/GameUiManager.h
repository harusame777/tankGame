#pragma once

#include "CRC32.h"

//ハッシュ値取得のためのマクロ定義
#define appState(name)	\
public:\
	static constexpr uint32_t ID() { return Hash32(#name); }

class GameUiBase; 

/// <summary>
/// ゲームのUI状態を表す列挙型です。
/// </summary>
enum EnGameUiState
{
	//初期化中
	en_init,
	//表示
	en_application,
	//表示中更新
	en_updateUi,
	//非表示
	en_extinction
};

/// <summary>
/// T型がGameUiBaseおよびIGameObjectの両方を基底クラスに持つかどうかを判定します。
/// </summary>
/// <typeparam name="T">判定対象となる型。</typeparam>
template<class T>
constexpr bool IsComponentData = 
std::is_base_of<GameUiBase, T>::value && 
std::is_base_of<IGameObject, T>::value;

class GameUiManager
{
private:
	/// <summary>
	/// インスタンス
	/// </summary>
	static GameUiManager* m_gameUiManagerInstance;
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameUiManager() = default;
	/// <summary>
	/// コピー禁止
	/// </summary>
	/// <param name=""></param>
	GameUiManager(const GameUiManager&) = delete;
	/// <summary>
	/// 代入禁止
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	GameUiManager& operator=(const GameUiManager&) = delete;
	/// <summary>
	/// 名前定義。ステートペア
	/// </summary>
	using GameUiPair = std::pair<uint32_t, GameUiBase*>;
public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameUiManager() = default;
	/// <summary>
	/// ゲームUIマネージャーのインスタンスを取得します（シングルトンパターン）。
	/// </summary>
	/// <returns>GameUiManager の唯一のインスタンスへのポインタ。</returns>
	static GameUiManager* GetGameUiManagerInstance()
	{
		if (m_gameUiManagerInstance == nullptr)
		{
			m_gameUiManagerInstance = new GameUiManager();
		}
		
		return m_gameUiManagerInstance;
	}
	/// <summary>
	/// テンプレートによるゲームUI要素の生成を行います。
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <typeparam name=""></typeparam>
	/// <param name="drawNum"></param>
	/// <param name="pos"></param>
	template<class T, std::enable_if_t<IsComponentData<T>,int> = 0>
	void CreateGameUi(int drawNum)
	{
		//生成するゲームUI要素のポインタを取得します。
		auto NewGameUi = NewGO<T>(drawNum, "gameUi");
		//生成したゲームUI要素をリストに追加します。
		m_gameUiList.insert(GameUiPair(T::ID(), NewGameUi));
	}
	/// <summary>
	/// 指定のゲームUI要素の状態を変更します。
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <typeparam name=""></typeparam>
	template<class T, std::enable_if_t<IsComponentData<T>, int> = 0>
	void ChangeStateGameUi(EnGameUiState changeState)
	{
		//IDを使用してゲームUI要素を検索します。
		auto it = m_gameUiList.find(T::ID());

		//要素が見つからない場合は何もしません。
		if (it == m_gameUiList.end())
		{
			return;
		}

		//見つかった要素の状態を変更します。
		it->second->SetState(changeState);
	}
private:
	/// <summary>
	/// ゲームUI要素のリストを保持するベクターです。
	/// </summary>
	std::unordered_map<uint32_t, GameUiBase*> m_gameUiList;
};

