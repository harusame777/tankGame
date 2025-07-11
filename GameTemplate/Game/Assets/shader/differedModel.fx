/*!
 * @brief	シンプルなモデルシェーダー。
 */


////////////////////////////////////////////////
// 定数バッファ。
////////////////////////////////////////////////
//モデル用の定数バッファ
cbuffer ModelCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
};

////////////////////////////////////////////////
// 構造体
////////////////////////////////////////////////

//スキニング用の頂点データをひとまとめ。
struct SSkinVSIn{
	int4  Indices  	: BLENDINDICES0;
    float4 Weights  : BLENDWEIGHT0;
};

//頂点シェーダーへの入力。
struct SVSIn{
	float4 pos 		: POSITION;		//モデルの頂点座標。
    float3 normal   : NORMAL;       //モデルの法線ベクトル。
	float2 uv 		: TEXCOORD0;	//UV座標。
    float3 tangent  : TANGENT;      //接ベクトル
    float3 biNormal : BINORMAL;     //従ベクトル
	SSkinVSIn skinVert;				//スキン用のデータ。
};

//ピクセルシェーダーへの入力。
struct SPSIn{
	float4 pos 			: SV_POSITION;	//スクリーン空間でのピクセルの座標。
    float3 normal       : NORMAL;       //法線ベクトル。
	float2 uv 			: TEXCOORD0;	//uv座標。
    float3 worldPos     : TEXCOORD1;    //ワールド空間でのピクセルの座標。
    float3 tangent      : TANGENT;      //接ベクトル
    float3 biNormal     : BINORMAL;     //従ベクトル
};

//ピクセルシェーダーの出力。
struct SPSOut
{
    float4 albedo   : SV_Target0; //アルベドカラー
    float4 normal   : SV_Target1; //法線ベクトル
    float4 worldPos : SV_Target2; //ワールド空間でのピクセルの座標
};

////////////////////////////////////////////////
// グローバル変数。
////////////////////////////////////////////////
Texture2D<float4> g_albedo : register(t0);				//アルベドマップ
Texture2D<float4> g_normalMap : register(t1);           //法線マップ
Texture2D<float4> g_specularMap : register(t2);         //スペキュラマップ
StructuredBuffer<float4x4> g_boneMatrix : register(t3);	//ボーン行列。
sampler g_sampler : register(s0);	//サンプラステート。

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
    float4x4 m;
    if (hasSkin)
    {
        m = CalcSkinMatrix(vsIn.skinVert);
    }
    else
    {
        m = mWorld;
    }
    psIn.pos = mul(m, vsIn.pos); // モデル空間でのピクセルの座標を計算
    
    psIn.worldPos = psIn.pos; // ワールド空間でのピクセルの座標を計算
    
    psIn.pos = mul(mView, psIn.pos);
    psIn.pos = mul(mProj, psIn.pos);
    psIn.normal = normalize(mul(m, vsIn.normal));

    psIn.tangent = normalize(mul(m, vsIn.tangent));
    psIn.biNormal = normalize(mul(m, vsIn.biNormal));
    
    psIn.uv = vsIn.uv;

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
SPSIn VSSkinMain( SVSIn vsIn ) 
{
	return VSMainCore(vsIn, true);
}
/// <summary>
/// ピクセルシェーダーのエントリー関数。
/// </summary>
SPSOut PSMain( SPSIn psIn )
{
    
    SPSOut psOut;
    
    //アルベドカラーを出力
    psOut.albedo = g_albedo.Sample(g_sampler, psIn.uv);
    
    //法線を出力
    float3 localNormal = g_normalMap.Sample(g_sampler, psIn.uv).xyz;
    
    //タンジェントスペースの法線を0～１の範囲から-1～1の範囲に復元する
    localNormal = (localNormal - 0.5f) * 2.0f;
    
    //タンジェントスペースの法線をワールドスペースに変換する
    float3 normal = psIn.tangent * localNormal.x + 
                    psIn.biNormal * localNormal.y + 
                    psIn.normal * localNormal.z;
    
    psOut.normal.xyz = (normal / 2.0f) + 0.5f;
    psOut.normal.w = 1.0f;
    
    psOut.normal.w = g_specularMap.Sample(g_sampler, psIn.uv).r;
    
    //ワールド空間でのピクセルの座標を出力
    psOut.worldPos.xyz = psIn.worldPos;
    psOut.worldPos.w = 1.0f;
    
    return psOut;
}
