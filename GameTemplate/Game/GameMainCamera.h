#pragma once

#include "GameCameraObjectBase.h"

class GameMainCamera : 
	public GameCameraObjectBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameMainCamera(
		GameCameraManager::CameraUpdateData* cameraUpdateData = nullptr,
		Camera* camera = nullptr
	) : GameCameraObjectBase(cameraUpdateData,camera) {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameMainCamera() {};
private:
	/// <summary>
	/// カメラ初期化
	/// </summary>
	/// <returns></returns>
	bool InitCamera() override;
	/// <summary>
	/// カメラ更新
	/// </summary>
	void UpdateCamera() override;
};

