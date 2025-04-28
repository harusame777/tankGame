#include "stdafx.h"
#include "CannonballObjectBase.h"

#include "CannonballStateBase.h"

void CannonballObjectBase::UpdateCannonballState()
{

	//ステート更新
	m_cannonballStateList[m_currentState]->UpdateState();

	//ステートの変更判定
	if (m_currentState != m_requestState)
	{
		//ステートが終了する時の処理を実行
		m_cannonballStateList[m_currentState]->EndState();
		//ステート変更
		m_currentState = m_requestState;
		//ステートの初期化処理
		m_cannonballStateList[m_currentState]->InitState();
	}
}
