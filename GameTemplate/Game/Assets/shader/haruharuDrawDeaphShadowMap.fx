/*!
 * @brief	シンプルなモデルシェーダー。
 */

static const int NUM_DIRECTIONAL_LIGHT = 4; // ディレクションライトの数
static const int MAX_POINT_LIGHT = 32; // ポイントライトの最大数
static const int MAX_SPOT_LIGHT = 32; // スポットライトの最大数

////////////////////////////////////////////////
// ライトの構造体
////////////////////////////////////////////////
struct DirectionLight
{
	//ライトの方向
    float3 direction;
	//ライトのカラー
    float3 color;
    //使用中かどうか
    int isUse;
    //
    float4x4 mLVP;
    //
    float3 ligPos;
};

//ポイントライト
struct PointLight
{
	//座標
    float3 position;
	//使用中フラグ
    int isUse;
	//ライトのカラー
    float3 color;
	//減衰パラメータ
	//xに影響範囲,yに影響率に累乗するパラメータ
    float3 attn;
};

//スポットライト
struct SpotLight
{
    //座標
    float3 position;
    //使用中フラグ
    int isUse;
    //ライトのカラー
    float3 color;
    //影響範囲
    float range;
     //射出方向
    float3 direction;
    //射出角度
    float angle;
    //影響率に累乗するパラメータ
    float3 pow;
};

////////////////////////////////////////////////
// 定数バッファ。
////////////////////////////////////////////////
//モデル用の定数バッファ
cbuffer ModelCb : register(b0)
{
    float4x4 mWorld;
    float4x4 mView;
    float4x4 mProj;
};

//ユーザー拡張
cbuffer LightCb : register(b1)
{
	//ディレクションライトの配列
    DirectionLight m_directionalLight[NUM_DIRECTIONAL_LIGHT];
	//ポイントライトの配列
    PointLight m_pointLights[MAX_POINT_LIGHT];
    //スポットライトの配列
    SpotLight m_spotLights[MAX_SPOT_LIGHT];
	//視点の位置
    float3 m_eyePos;
	//使用中のポイントライトの数
    int m_numPointLight;
	//環境光
    float3 m_ambientLight;
    //使用中のスポットライトの数
    int m_numSpotLight;
    //使用中のディレクションライトの数
    int m_numDirectionLight;
};

////////////////////////////////////////////////
// 構造体
////////////////////////////////////////////////
//スキニング用の頂点データをひとまとめ。
struct SSkinVSIn
{
    int4 Indices : BLENDINDICES0;
    float4 Weights : BLENDWEIGHT0;
};
//頂点シェーダーへの入力。
struct SVSIn
{
    float4 pos : POSITION; //モデルの頂点座標。
    float3 normal : NORMAL; // 法線
    float2 uv : TEXCOORD0; //UV座標。
    SSkinVSIn skinVert; //スキン用のデータ。
};
//ピクセルシェーダーへの入力。
struct SPSIn
{
    float4 pos : SV_POSITION; //スクリーン空間でのピクセルの座標。
    float3 normal : NORMAL; // 法線
    float2 uv : TEXCOORD0; //uv座標
    float2 depth : TEXCOORD1; // ライト空間での座標。
};

////////////////////////////////////////////////
// グローバル変数。
////////////////////////////////////////////////
Texture2D<float4> g_albedo : register(t0); //アルベドマップ
StructuredBuffer<float4x4> g_boneMatrix : register(t3); //ボーン行列。
Texture2D<float4> g_shadowMap : register(t10); // シャドウマップ
sampler g_sampler : register(s0); //サンプラステート。

////////////////////////////////////////////////
// 関数定義。
////////////////////////////////////////////////

/// <summary>
//スキン行列を計算する。
/// </summary>
float4x4 CalcSkinMatrix(SSkinVSIn skinVert)
{
    float4x4 skinning = 0;
    float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += g_boneMatrix[skinVert.Indices[i]] * skinVert.Weights[i];
        w += skinVert.Weights[i];
    }
    
    skinning += g_boneMatrix[skinVert.Indices[3]] * (1.0f - w);
	
    return skinning;
}

/// <summary>
/// 頂点シェーダーのコア関数。
/// </summary>
SPSIn VSMainCore(SVSIn vsIn, uniform bool hasSkin)
{
    SPSIn psIn;
    float4x4 mSkinWorld;
    if (hasSkin)
    {
        mSkinWorld = CalcSkinMatrix(vsIn.skinVert);
    }
    else
    {
        mSkinWorld = mWorld;
    }
    psIn.pos = mul(mSkinWorld, vsIn.pos);
    float3 worldPos = psIn.pos;
    psIn.pos = mul(mView, psIn.pos);
    psIn.pos = mul(mProj, psIn.pos);

    psIn.uv = vsIn.uv;
	
    psIn.normal = mul(mSkinWorld, vsIn.normal);
    
    psIn.depth.x = length(worldPos - m_directionalLight[0].ligPos) / 10000.0f;
    psIn.depth.y = psIn.depth.x * psIn.depth.x;

    return psIn;
}

/// <summary>
/// スキンなしメッシュ用の頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSMain(SVSIn vsIn)
{
    return VSMainCore(vsIn, false);
}
/// <summary>
/// スキンありメッシュの頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSSkinMain(SVSIn vsIn)
{
    return VSMainCore(vsIn, true);
}
/// <summary>
/// シャドウマップ描画用のピクセルシェーダー
/// </summary>
float4 PSMain(SPSIn psIn) : SV_Target0
{
    // step-3 シャドウマップにZ値を描き込む
    return float4(psIn.depth.x,psIn.depth.y,0.0f, 1.0f);
}
