#include "stdafx.h"
#include "TankShellsEntity.h"

#include "TankShellsAttributeBase.h"

//スタート関数
bool TankShellsEntity::Start()
{
	

	m_tankShellsAttributePtr->InitData();

	return true;
}

//アップデート関数
void TankShellsEntity::Update()
{
	//属性が未設定だったら戻す
	if (m_tankShellsAttributePtr == nullptr)
	{
		return;
	}

	//移動計算
	m_tankShellsAttributePtr->MoveCalc();

	//弾丸座標移動処理
	m_tankShellsModel.SetPosition(m_position);
	//弾丸回転処理
	m_tankShellsModel.SetRotation(m_rotation);
}

//レンダリング関数
void TankShellsEntity::Render(RenderContext& rc)
{
	//描画処理
	m_tankShellsModel.Draw(rc);
}
