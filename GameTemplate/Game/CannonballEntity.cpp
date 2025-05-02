#include "stdafx.h"
#include "CannonballEntity.h"

#include "CannonballAttributeBase.h"

//スタート関数
bool CannonballEntity::Start()
{
	

	m_cannonballAttributePtr->InitData();

	return true;
}

//アップデート関数
void CannonballEntity::Update()
{
	//属性が未設定だったら戻す
	if (m_cannonballAttributePtr == nullptr)
	{
		return;
	}

	//移動計算
	m_cannonballAttributePtr->MoveCalc();

	//弾丸座標移動処理
	m_cannonballModel.SetPosition(m_position);
	//弾丸回転処理
	m_cannonballModel.SetRotation(m_rotation);
}

//レンダリング関数
void CannonballEntity::Render(RenderContext& rc)
{
	//描画処理
	m_cannonballModel.Draw(rc);
}
