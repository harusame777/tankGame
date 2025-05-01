#pragma once

class CannonballAttributeBase;

class CannonballEntity
{
public:
	enum EnCannonballState
	{
		//初期化
		en_init,
		//弾道計算
		en_trajectoryCalc,
		//移動処理
		en_move,
		//削除処理
		en_delete
	};
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CannonballEntity();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~CannonballEntity() {};
	/// <summary>
	/// 砲弾の移動計算クラスのインスタンスを設定
	/// </summary>
	/// <param name="calcPtr"></param>
	void SetCannonballCalc(CannonballAttributeBase* calcPtr)
	{
		m_cannonballMoveCalc = calcPtr;
	}
private:
	/// <summary>
	/// ステート
	/// </summary>
	EnCannonballState m_cannonballState = EnCannonballState::en_init;
	/// <summary>
	/// 砲弾移動計算
	/// </summary>
	CannonballAttributeBase* m_cannonballMoveCalc = nullptr;
	/// <summary>
	/// 砲弾のモデル
	/// </summary>
	ModelRender m_cannonballModel;
};

