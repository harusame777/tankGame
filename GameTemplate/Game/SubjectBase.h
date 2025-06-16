#pragma once

//汎用的なサブジェクトベース
template<typename... Args>
class SubjectBase
{
	/// <summary>
	/// Args... 型のパラメータを持つ Observer クラスのエイリアス型を定義します。
	/// </summary>
	using ObserverType = Observer<Args...>;
};

