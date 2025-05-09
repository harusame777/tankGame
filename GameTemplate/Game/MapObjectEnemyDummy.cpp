#include "stdafx.h"
#include "MapObjectEnemyDummy.h"

#include "GameCollisionManager.h"

//スタート関数
bool MapObjectEnemyDummy::Start()
{
	//モデルのファイルパス設定
	m_modelRender.Init(
		m_filePath,
		nullptr,
		0,
		enModelUpAxisZ,
		m_modelUseShader);

	m_modelRender.SetShadowChasterFlag(false);

	//モデル更新
	UpdateModel(m_modelRender);

	Vector3 colPos = GetPosition();

	colPos.y += 35.0f;

	m_collision = GameCollisionManager::GetCollisionManagerInstance()->CreateSphereCollision(
		colPos,
		GetRotation(),
		30.0f,
		"DummyCollision"
	);

	return true;
}

//アップデート関数
void MapObjectEnemyDummy::Update()
{
	//モデル更新
	UpdateModel(m_modelRender);
}

//レンダリング関数
void MapObjectEnemyDummy::Render(RenderContext& rc)
{
	//描画する
	m_modelRender.Draw(rc);
}