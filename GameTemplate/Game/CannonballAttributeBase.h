#pragma once

class CannonballEntity;


class CannonballAttributeBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CannonballAttributeBase(){};
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual~CannonballAttributeBase() {};
	/// <summary>
	/// この属性を持っている砲弾のポインタを設定
	/// </summary>
	/// <param name="hostCannonball"></param>
	void SetHostPtr(CannonballEntity* hostCannonball)
	{
		m_hostCannonballPtr = hostCannonball;
	}
	/// <summary>
	/// データ設定
	/// </summary>
	/// <param name="hostData"></param>
	virtual void InitData() = 0;
	/// <summary>
	/// 移動計算を行う、ポインタで送るので引数の内容は更新される
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="rot"></param>
	/// <param name="forward"></param>
	virtual void MoveCalc() = 0;
	/// <summary>
	/// 接触時のふるまい
	/// </summary>
	virtual void HitAction() = 0;
private:
	/// <summary>
	/// この属性を持っている砲弾本体
	/// </summary>
	CannonballEntity* m_hostCannonballPtr = nullptr;
};

