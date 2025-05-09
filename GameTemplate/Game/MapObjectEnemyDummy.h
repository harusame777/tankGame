#pragma once
#include "GameMapObjectBase.h"

class MapObjectEnemyDummy :
	public IGameObject,
	public GameMapObjectBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	MapObjectEnemyDummy() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~MapObjectEnemyDummy() {};
	/// <summary>
	/// ファイルパスを設定
	/// </summary>
	/// <param name="filePath"></param>
	void SetFilePath(const char* filePath)
	{
		m_filePath = filePath;
	}
	/// <summary>
	/// モデル使用シェーダーを設定
	/// </summary>
	/// <param name="useShader"></param>
	void SetModelUseShader(ModelRender::EnShader useShader)
	{
		m_modelUseShader = useShader;
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
	/// レンダリング関数
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// ファイルパス
	/// </summary>
	const char* m_filePath = nullptr;
	/// <summary>
	/// モデルレンダー
	/// </summary>
	ModelRender m_modelRender;
	/// <summary>
	/// モデル仕様シェーダー
	/// </summary>
	ModelRender::EnShader m_modelUseShader;
	/// <summary>
	/// 当たり判定
	/// </summary>
	std::shared_ptr<CollisionObject> m_collision;
};

