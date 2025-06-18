#pragma once

//イベント仲介役クラス
class EventManager
{
private:
	/// <summary>
	/// インスタンス
	/// </summary>
	static EventManager* m_eventManagerInstance;
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EventManager() = default;
	/// <summary>
	/// デストラクタ
	/// </summary>
	~EventManager() = default;
	/// <summary>
	/// コピー禁止
	/// </summary>
	/// <param name=""></param>
	EventManager(const EventManager&) = delete;
	/// <summary>
	/// 代入禁止
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	EventManager& operator = (const EventManager&) = delete;
public:
	/// <summary>
	/// StructEventBase は、イベントの基底クラスとして機能します。
	/// </summary>
	struct StructEventBase
	{
		virtual ~StructEventBase() = default;
	};
	/// <summary>
	/// イベントマネージャーのインスタンスを取得します（シングルトンパターン）。
	/// </summary>
	/// <returns>EventManager の唯一のインスタンスへのポインタ。</returns>
	static EventManager* GetEventManagerInstance()
	{
		if (m_eventManagerInstance == nullptr)
		{
			m_eventManagerInstance = new EventManager();
		}

		return m_eventManagerInstance;
	}
	/// <summary>
	/// 関数格納
	/// </summary>
	/// <typeparam name="EventType"></typeparam>
	template<typename EventType>
	using Callback = std::function<void(const EventType)>;
	/// <summary>
	/// 指定したイベントタイプのコールバックを購読リストに追加します。
	/// </summary>
	/// <typeparam name="EventType">購読するイベントの型。</typeparam>
	/// <param name="callback">購読するイベントが発生したときに呼び出されるコールバック関数。</param>
	template<typename EventType>
	void Subscribe(Callback<EventType> callback)
	{
		std::vector<Callback<EventType>>& list 
			= GetListeners<EventType>();

		list.emplace_back(std::move(callback));
	}
	/// <summary>
	/// 指定されたイベントをすべてのリスナーに通知します。
	/// </summary>
	/// <typeparam name="EventType">通知するイベントの型。</typeparam>
	/// <param name="event">通知するイベントオブジェクト。</param>
	template<typename EventType>
	void Publish(const EventType& event)
	{
		for (auto& cb : GetListeners<EventType>())
		{
			cb(event);
		}
	}
private:
	template<typename EventType>
	std::vector<Callback<EventType>>& GetListeners(){
		static std::vector<Callback<EventType>> listeners;
		return listeners;
	}
};

