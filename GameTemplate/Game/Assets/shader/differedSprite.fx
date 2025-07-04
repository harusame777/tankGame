/*!
 * @brief	ディファードレンダリングをするためのシェーダー
 */
////////////////////////////////////////////////
// 定数
////////////////////////////////////////////////
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

cbuffer cb : register(b0){
    float4x4 mvp;       //MVP行列
    float4 mulColor;    //乗算カラー
};

struct VSInput{
	float4 pos : POSITION;
	float2 uv  : TEXCOORD0;
};

struct PSInput{
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

Texture2D<float4> albedoTexture : register(t0); //アルベド
Texture2D<float4> normalTexture : register(t1); //法線マップ
sampler Sampler : register(s0);
////////////////////////////////////////////////
// 関数宣言
////////////////////////////////////////////////
//ディレクションライトの計算
//float3 CalcLigFromDirectionLight(SPSIn psIn, DirectionLight dirLig, float specPow);
////////////////////////////////////////////////
// 関数定義。
////////////////////////////////////////////////
//ディレクションライトによる反射光を計算
//float3 CalcLigFromDirectionLight(SPSIn psIn, DirectionLight dirLig, float specPow)
//{
//    //ディレクションライトによるLambert拡散反射光を計算する
//    float3 diffDirection = CalcLambertDiffuse(dirLig.direction, dirLig.color, psIn.normal);
//	//ディレクションライトによるPhong鏡面反射光を計算する
//    float3 specDirection = CalcPhongSpecular(dirLig.direction, dirLig.color, psIn.worldPos, psIn.normal, specPow);
//	//ディレクションライトの最終的な反射光を返す
//    return diffDirection + specDirection;
//}

PSInput VSMain(VSInput In) 
{
	PSInput psIn;
	psIn.pos = mul( mvp, In.pos );
	psIn.uv = In.uv;
	return psIn;
}

float4 PSMain( PSInput In ) : SV_Target0
{
	//アルベドを取得
    float4 albedo = albedoTexture.Sample(Sampler, In.uv);
	//法線を取得
    float3 normal = normalTexture.Sample(Sampler, In.uv).xyz;
    normal = (normal * 2.0f) - 1.0f; //法線を-1.0～1.0に変換
	
	//ライト計算
    float3 lig = 0.0f;
    
    float t = max(0.0f, dot(normal, m_directionalLight[0].direction) * -1.0f);
    lig = m_directionalLight[0].color * t;
    float4 finalColor = albedo;
    finalColor.xyz *= lig;
    
    return finalColor;
}