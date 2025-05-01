#include "stdafx.h"
#include "CannonballEntity.h"

#include "CannonballAttributeBase.h"

//スタート関数
bool CannonballEntity::Start()
{


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

	m_cannonballAttributePtr;

}

//レンダリング関数
void CannonballEntity::Render(RenderContext& rc)
{

}
