#include "stdafx.h"
#include "CannonballStateBase.h"

#include "CannonballObjectBase.h"

//このステートを保持している砲弾のステート変更
void CannonballStateBase::ChangeConnectCannonballState(const EnCannonballState changeState)
{
	m_connectCannonball->ChangeState(changeState);
}