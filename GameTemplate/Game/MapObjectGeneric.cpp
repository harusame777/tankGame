#include "stdafx.h"
#include "MapObjectGeneric.h"

//スタート関数
bool MapObjectGeneric::Start()
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

	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	return true;
}

//アップデート関数
void MapObjectGeneric::Update()
{
	//モデル更新
	UpdateModel(m_modelRender);
}

//レンダリング関数
void MapObjectGeneric::Render(RenderContext& rc)
{
	//描画する
	m_modelRender.Draw(rc);
}