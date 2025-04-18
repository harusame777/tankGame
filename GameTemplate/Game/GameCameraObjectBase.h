#pragma once
#include "GameCameraManager.h"

class GameCameraObjectBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameCameraObjectBase(
		GameCameraManager::CameraUpdateData* cameraUpdateData = nullptr,
		Camera* camera = nullptr
	)
	{
		m_cameraUpdateData = cameraUpdateData;
		m_camera = camera;
	};
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~GameCameraObjectBase() {};
	/// <summary>
	/// 純粋仮想関数、カメラ初期化
	/// </summary>
	/// <returns></returns>
	virtual bool InitCamera() = 0;
	/// <summary>
	/// 純粋仮想関数、カメラ更新
	/// </summary>
	virtual void UpdateCamera() = 0;
	/// <summary>
	/// カメラを更新するかどうかを設定
	/// </summary>
	/// <param name="isCameraUpdate"></param>
	void SetIsCameraUpdate(bool isCameraUpdate)
	{
		m_isCameraUpdate = isCameraUpdate;
	}
	/// <summary>
	/// カメラを更新するかどうかを取得
	/// </summary>
	/// <returns></returns>
	bool GetIsCameraUpdate() const
	{
		return m_isCameraUpdate;
	}
protected:
	/// <summary>
	/// カメラデータ
	/// </summary>
	Camera* m_camera;
	/// <summary>
	/// カメラマネージャー
	/// </summary>
	GameCameraManager::CameraUpdateData* m_cameraUpdateData = nullptr;
	/// <summary>
	/// カメラを更新するかどうか
	/// </summary>
	bool m_isCameraUpdate = false;
};

