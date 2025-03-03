#pragma once
#include "level3D/TklFile.h"

namespace nsK2EngineLow {
	/*!
	* @brief	オブジェクト名。
	*/
	//LevelクラスのLevelObjectDataとかぶるので_Renderを付けておく
	struct LevelObjectData_Render
	{
		/// <summary>
		/// 座標
		/// </summary>
		Vector3 m_position;
		/// <summary>
		/// 回転
		/// </summary>
		Quaternion m_rotation;
		/// <summary>
		/// 拡大率
		/// </summary>
		Vector3 m_scalse;
		/// <summary>
		/// 名前
		/// </summary>
		const wchar_t* name;
		/// <summary>
		/// ナンバー
		/// </summary>
		int number = 0;
		/// <summary>
		/// 引数で渡したオブジェクト名のオブジェクトか調べる。
		/// </summary>
		/// <param name="objName = 調べる名前。"></param>
		/// <returns></returns>
		bool EqualObjectName(const wchar_t* objName)
		{
			return wcscmp(objName, name) == 0;
		}
		bool ForwardMatchName(const wchar_t* n)
		{
			auto len = wcslen(n);
			auto namelen = wcslen(name);
			if (len > namelen)
			{
				//名前が長いので不一致
				return false;
			}
			return wcsncmp(n, name, len) == 0;
		}
	};
	/// <summary>
	/// レベル
	/// </summary>
	class LevelRender
	{
	public:
		/// <summary>
		/// デストラクタ
		/// </summary>
		~LevelRender();
		/// <summary>
		/// レベルを初期化	
		///フックしないならnullptrを指定すればよい、
		///この関数オブジェクトがfalseを返すと、オブジェクトの情報から、
		///静的オブジェクトのMapChipクラスのインスタンスが生成されます。
		///オブジェクトの名前などで、ドアやジャンプ台、アイテムなどの特殊なクラスのインスタンスを生成したときに、
		///デフォルトで作成されるMapChipクラスのインスタンスが不要な場合はtrueを返してください。
		///例えば、フック関数の中で、渡されたオブジェクトデータの名前のモデルを描画するクラスのインスタンスを
		///生成したときに、falseを返してしまうと、同じモデルが二つ描画されることになります。
		/// </summary>
		/// <param name="filePath = tklファイルのファイルパス。"></param>
		/// <param name="hookFunc = オブジェクトを作成する時の処理をフックするための関数オブジェクト。"></param>
		void Init(const char* filePath, std::function<bool(LevelObjectData_Render& objData)> hookFunc);
		/// <summary>
		/// 更新処理
		/// </summary>
		void Update();
		/// <summary>
		/// モデルを描画
		/// </summary>
		/// <param name="rc = レンダーコンテキスト。"></param>
		void Draw(RenderContext& rc);
	private:
		/// <summary>
		/// Tklファイルの行列を変換する。
		/// </summary>
		void MatrixTklToLevel();
	private:
		using BonePtr = std::unique_ptr<Bone>;
		std::vector<BonePtr> m_boneList;
		std::unique_ptr<Matrix[]> m_matrixList;
		TklFile m_tklFile;
	};
}

