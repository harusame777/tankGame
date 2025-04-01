#pragma once
#include "GameMain.h"

class GameIn : public GameMainStateClass
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameIn() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~GameIn() {};
	/// <summary>
	/// ステート初期化
	/// </summary>
	void InitGameState() override;
	/// <summary>
	/// ステートアップデート
	/// </summary>
	void UpdateGameState() override;
private:

	

};

