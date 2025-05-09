#include "stdafx.h"
#include "TankShellsEntity.h"

#include "TankShellsAttributeBase.h"
#include "GameCollisionManager.h"

//スタート関数
bool TankShellsEntity::Start()
{
	//モデル設定
	m_tankShellsModel.Init(
		"Assets/modelData/tankShellsModel/tankShellsModelV1.tkm", 
		nullptr,
		0,
		enModelUpAxisZ,
		ModelRender::en_usuallyShader
	);

	//初期モデル位置回転設定
	m_tankShellsModel.SetPosition(m_position);

	float angle = atan2f(m_forward.x, m_forward.z);

	m_rotation.AddRotationY(angle);
	
	m_tankShellsModel.SetRotation(m_rotation);

	m_tankShellsModel.Update();

	m_tankShellsAttributePtr->InitData();

	m_collision = GameCollisionManager::GetCollisionManagerInstance()->CreateSphereCollision(
		m_position,
		m_rotation,
		7.0f,
		"testName"
	);

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

	if (GameCollisionManager::GetCollisionManagerInstance()
		->Is_A_ColisionHits_B_Colision(m_collision.get(), "testName"));
	{

	}

	//弾丸座標移動処理
	m_tankShellsModel.SetPosition(m_position);
	//弾丸回転処理
	m_tankShellsModel.SetRotation(m_rotation);

	m_collision->SetPosition(m_position);

	m_collision->Update();

	m_tankShellsModel.Update();
}

//レンダリング関数
void TankShellsEntity::Render(RenderContext& rc)
{
	//描画処理
	m_tankShellsModel.Draw(rc);
}

//削除関数
void TankShellsEntity::DeleteGOTankShells()
{
	//属性ごとの削除時の処理を実行
	m_tankShellsAttributePtr->DeleteTankShellsAttributeAction();

	DeleteGO(this);
}
