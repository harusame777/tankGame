#pragma once
#include "StateMachineBase.h"
#include "StateBase.h"

class GameMainStateMachine :
    public StateMachineBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GameMainStateMachine() {};
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~GameMainStateMachine() {};
    /// <summary>
    /// 初期化関数
    /// </summary>
    void InitState()
    {
        m_currentState->Enter();
    }
    /// <summary>
    /// 更新
    /// </summary>
    void Update() override;
};

