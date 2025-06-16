#pragma once

//汎用的なオブザーバーベース
template<typename... Args>
class ObserverBase
{
public:
	/// <summary>
	/// 仮想デストラクタ
	/// </summary>
	virtual ~ObserverBase() = default;
	/// <summary>
	/// サブジェクトからの通知を受け取る関数
	/// </summary>
	/// <param name="...args"></param>
	virtual void onNotify(Args... args) = 0;
};

