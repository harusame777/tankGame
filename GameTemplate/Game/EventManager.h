#pragma once
#include <typeindex>

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
	using ConditionFunc = std::function<bool()>;
	using HandlerFunc = std::function<void(const StructEventBase&)>;
	/// <summary>
	/// イベントマネージャーにリスナーを登録
	/// </summary>
	/// <typeparam name="EventType"></typeparam>
	/// <param name="object"></param>
	/// <param name="condition"></param>
	/// <param name="handler"></param>
	template<typename EventType,typename ObjectType>
	void RegisterListener(
		std::weak_ptr<ObjectType> object,
		std::function<bool(std::shared_ptr<ObjectType>)> condition,
		std::function<void(std::shared_ptr<ObjectType>, const EventType&)> handler
	)
	{
		//型判別するためにtype_indexに代入
		std::type_index type = typeid(EventType);

		//配列の末尾にイベントリスナーを追加
		m_listnersList[type].emplace_back(
			[object, condition]()-> bool 
			{
				//このオブジェクトが削除済みでないかを確認
				if (auto sp = object.lock())
				{
					//関数が起動可能かどうかを返す
					return condition(sp);
				}
				return false;
			},
			[object, handler](const StructEventBase& event)
			{
				//このオブジェクトが削除済みでないかを確認
				if (auto sp = object.lock())
				{
					//イベント処理
                    handler(sp, dynamic_cast<const EventType&>(event));
				}
			}
		);
	}
	/// <summary>
	/// 指定されたイベントをすべてのリスナーに通知します。
	/// </summary>
	/// <typeparam name="EventType">通知するイベントの型。</typeparam>
	/// <param name="event">通知するイベントオブジェクト。</param>
	void NotifyListeners(const StructEventBase& event)
	{
		//比較のためtype_indexに代入
		std::type_index type = typeid(event);
		//該当するイベントリスナーを探す
		auto it = m_listnersList.find(type);

		if (it != m_listnersList.end())
		{
			for(auto& pair : it->second)
			{
				//関数のアドレスを取り出す
				auto& condition = pair.first;
				auto& handler = pair.second;

				//実行できる状態であれば
				if (condition() == true)
				{
					//実行する
					handler(event);
				}
			}
		}
	}
private:
	/// <summary>
	/// リスナーを格納するリスト
	/// </summary>
	std::unordered_map <
		std::type_index,
		std::vector<std::pair<ConditionFunc, HandlerFunc>>
	> m_listnersList;
};

