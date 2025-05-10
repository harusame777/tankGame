#pragma once

class GameCameraObjectBase;

class GameCameraManager
{
private:
	/// <summary>
	/// インスタンス
	/// </summary>
	static GameCameraManager* m_gameCameraManagerInstance;
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameCameraManager() {};
	/// <summary>
	/// コピー禁止
	/// </summary>
	/// <param name=""></param>
	GameCameraManager(const GameCameraManager&) = delete;
	/// <summary>
	/// 代入禁止
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	GameCameraManager& operator = (const GameCameraManager&) = delete;
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
	/// デストラクタ
	/// </summary>
	~GameCameraManager() {};
	/// <summary>
	/// インスタンス作成、または取得
	/// </summary>
	/// <returns></returns>
	static GameCameraManager* GetGameCameraManagerInstance()
	{
		if (m_gameCameraManagerInstance == nullptr)
		{
			m_gameCameraManagerInstance = new GameCameraManager();
		}

		return m_gameCameraManagerInstance;
	}
	/// <summary>
	/// ゲームカメラリストにカメラベースを継承しているオブジェクトを追加
	/// </summary>
	/// <param name="addCamera"></param>
	void AddGameCameraList(GameCameraObjectBase* addCamera = nullptr)
	{
		m_gameCameraList.push_back(addCamera);
	}
	/// <summary>
	/// 初期化
	/// </summary>
	void InitGameCameraManager();
	/// <summary>
	/// アップデート関数
	/// </summary>
	void UpdateGameCameraManager();
private:
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

