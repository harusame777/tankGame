#include "stdafx.h"
#include "EnemyTankStateMachine.h"

#include "EnemyTankEntity.h"
#include "StateBase.h"

//アップデート関数
void EnemyTankStateMachine::Update()
{
	if (m_currentState)
	{
		//ハッシュ値、リクエストされたステート
		uint32_t requestState;
		if (m_currentState->RequestState(requestState))
		{
			//ステートの終了を実行
			m_currentState->Exit();
			//ステートをハッシュマップから探して変更
			m_currentState = FindState(requestState);
			//ステートの初期化処理を実行
			m_currentState->Enter();
		}
	}
	//ステートを更新
	m_currentState->Update();
}