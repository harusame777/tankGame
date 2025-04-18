#pragma once

class GameCameraObjectBase;

class GameCameraManager : public IGameObject
{
public:
	/// <summary>
	/// カメラデータ構造体
	/// </summary>
	struct CameraUpdateData
	{
	public:
		/// <summary>
		/// カメラ座標
		/// </summary>
		Vector3 m_position = Vector3::Zero;
		/// <summary>
		/// 注視点座標
		/// </summary>
		Vector3 m_targetPosition = Vector3::Zero;
		/// <summary>
		/// 近平面距離
		/// </summary>
		float m_near = 0.0f;
		/// <summary>
		/// 遠平面距離
		/// </summary>
		float m_far = 0.0f;

	};
	enum CameraModeState
	{
		en_cameraMain,
	};
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameCameraManager() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameCameraManager() {};
	/// <summary>
	/// ゲームカメラリストにカメラベースを継承しているオブジェクトを追加
	/// </summary>
	/// <param name="addCamera"></param>
	void AddGameCameraList(GameCameraObjectBase* addCamera = nullptr)
	{
		m_gameCameraList.push_back(addCamera);
	}
private:
	/// <summary>
	/// スタート関数
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// アップデート関数
	/// </summary>
	void Update();
	/// <summary>
	/// カメラデータ
	/// </summary>
	CameraUpdateData m_cameraUpdateData;
	/// <summary>
	/// カメラステート
	/// </summary>
	CameraModeState m_cameraModeState = CameraModeState::en_cameraMain;
	/// <summary>
	/// ゲームカメラのプログラムリスト
	/// </summary>
	std::vector<GameCameraObjectBase*> m_gameCameraList;
};

