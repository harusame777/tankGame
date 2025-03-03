#pragma once

#include "graphics/light/SceneLight.h"
#include "graphics/Render/ShadowMapRender.h"

namespace nsK2EngineLow {
	class ShadowMapModelRender;

	/// <summary>
	/// モデルを描画するためのヤツ
	/// </summary>
	class ModelRender : public IRenderer, public ShadowMapRender{
	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		ModelRender();
		/// <summary>
		/// デストラクタ
		/// </summary>
		~ModelRender();

		enum EnShader
		{
			en_usuallyShader,
			en_shadowShader,
			en_crystalShader
		};

		
		Light* m_light;

		struct ShadowMapParam
		{
			Matrix mLVP;
			Vector3 ligPos;
		};

		ShadowMapParam shadowparam;

		/// <summary>
		/// 初期化処理
		/// </summary>
		/// <param name="tkmfilePath">モデルのファイルパス</param>
		/// <param name="animationClips">アニメーションクリップ</param>
		/// <param name="numAnimationClips">アニメーションクリップの数</param>
		/// <param name="enModelUpAxis">モデルの上方向</param>
		/// <param name="dithering">ディザリングフラグ、tureならディザリングを行う</param>
		/// <param name="isRecieverShadow">影を落とすか決めるフラグ、tureなら影が落ちる</param>
		void Init(
			const char* tkmfilePath,
			AnimationClip* animationClips = nullptr,
			int numAnimationClips = 0,
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ,
			const EnShader& shader = ModelRender::en_usuallyShader
		);

		void InitNormalModel(
			const char* tkmfilePath,
			AnimationClip* animationClips = nullptr,
			int numAnimationClips = 0,
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ,
			const EnShader& shader = ModelRender::en_usuallyShader
		);

		void InitShadowModel(
			const char* tkmfilePath,
			EnModelUpAxis modelUpAxis
		);

		/// <summary>
		/// GBuffer描画用のモデルを初期化。
		/// </summary>
		/// <param name="renderingEngine">レンダリングエンジン</param>
		/// <param name="tkmFilePath">tkmファイルパス</param>
		void InitModelOnRenderGBuffer(
			RenderingEngine& renderingEngine,
			const char* tkmFilePath,
			EnModelUpAxis enModelUpAxis,
			bool isShadowReciever
		);

		//スケルトンの初期化
		void InitSkeleton(const char* filePath);

		//アニメーションの初期化
		void InitAnimation(
			AnimationClip* animationClips,
			int numAnimationClips
		);

		//アニメーション再生
		void PlayAnimation(int animNo, float interpolateTime = 0.0f)
		{
			m_animation.Play(animNo, interpolateTime);
		}

		//アニメーションが再生中かどうか
		bool IsPlayingAnimation() const
		{
			return m_animation.IsPlaying();
		}

		//アニメーションの速度を設定
		void SetAnimationSpeed(const float animationSpeed)
		{
			m_animationSpeed = animationSpeed;
		}

		//アニメーションイベント(後で調べる)
		void AddAnimationEvent(AnimationEventListener eventListener)
		{
			m_animation.AddAnimationEventListener(eventListener);
		}

		//更新処理
		void Update();

		//座標を設定
		void SetPosition(Vector3 pos)
		{
			m_position = pos;
		}

		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x,y,z });
		}

		//回転を設定
		void SetRotation(Quaternion rot)
		{
			m_rotation = rot;
		}

		//拡大率を設定
		void SetScale(Vector3 scale)
		{
			m_scale = scale;
		}

		void SetScale(float x, float y, float z)
		{
			SetScale({ x,y,z });
		}

		Model& GetModel()
		{
			return m_model;
		}

		//描画処理
		void Draw(RenderContext& rc);

		//3Dモデルの描画処理
		void OnRenderModel(RenderContext& rc) override;

		//シャドウマップへの描画パスから呼ばれる処理
		void OnRenderShadowMap(RenderContext& rc) override;

		//G-Buffer描画パスから呼ばれる処理
		void OnRenderToGBuffer(RenderContext& rc) override;

		//影を描画するかしないかを設定
		void SetShadowChasterFlag(bool flag)
		{
			m_isShadowChaster = flag;
		}


	protected:
		//モデルレンダーに設定されているモデル
		Model m_model;
		//モデルレンダーに設定されているスケルトン
		Skeleton m_skeleton;
		//モデルレンダーに設定されているアニメーションクリップ
		AnimationClip* m_animationClips = nullptr;
		//アニメーションクリップの数
		int m_numAnimationClips = 0;
		//アニメーションスピード
		float m_animationSpeed = 1.0f;
		//アニメーションクラス
		Animation m_animation;

		//モデルレンダーに設定されている座標
		Vector3 m_position = Vector3::Zero;
		//モデルレンダーに設定されている回転値
		Quaternion m_rotation = Quaternion::Identity;
		//モデルレンダーに設定されているモデルの大きさ
		Vector3 m_scale = Vector3::One;

		Model m_shadowMapModel;
		
		Model m_gBufferModel;

		//影を落とすか管理するフラグ
		bool m_isShadowChaster = true;		
	};
}

