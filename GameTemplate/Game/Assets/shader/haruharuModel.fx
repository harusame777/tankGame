/*!
 * @brief	シンプルなモデルシェーダー。
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

////////////////////////////////////////////////
// 定数バッファ。
////////////////////////////////////////////////
//モデル用の定数バッファ
cbuffer ModelCb : register(b0){
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
	float2 uv 		: TEXCOORD0;	//UV座標。
    float3 normal	: NORMAL;		//法線
    float3 tangent  : TANGENT;      //接ベクトル
    float4 biNormal : BINORMAL;     //従ベクトル
	SSkinVSIn skinVert;				//スキン用のデータ。
};
//ピクセルシェーダーへの入力。
struct SPSIn{
	float4 pos 			: SV_POSITION;	//スクリーン空間でのピクセルの座標。
	float2 uv 			: TEXCOORD0;	//uv座標。
    float3 normal		: NORMAL;		//法線
    float3 tangent      : TANGENT;      //接ベクトル
    float3 biNormal     : BINORMAL;     //従ベクトル
    float3 worldPos		: TEXCOORD1;	//ワールド座標系でのポジション
    float3 normalInView : TEXCOORD2;    //カメラ空間の法線
};

////////////////////////////////////////////////
// グローバル変数。
////////////////////////////////////////////////
Texture2D<float4> g_albedo : register(t0);				//アルベドマップ
Texture2D<float4> g_normalMap : register(t1);           //法線マップ
Texture2D<float4> g_speclarMap : register(t2);          //スペキュラマップ
StructuredBuffer<float4x4> g_boneMatrix : register(t3);	//ボーン行列。
sampler g_sampler : register(s0);	                    //サンプラステート。

////////////////////////////////////////////////
// 関数宣言
////////////////////////////////////////////////
//ディレクションライトの計算
float3 CalcLigFromDirectionLight(SPSIn psIn, DirectionLight dirLig, float specPow);
//Lambert拡散反射光の計算
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal);
//Phonng鏡面反射光の計算
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal, float specPow);
//ポイントライトの計算
float3 CalcLigFromPointLight(SPSIn psIn, PointLight ptlig, float specPow);
//スポットライトの計算
float3 CalcLigFromSpotLight(SPSIn psIn, SpotLight spLig, float specPow);
////////////////////////////////////////////////
// 関数定義。
////////////////////////////////////////////////

//ディレクションライトによる反射光を計算
float3 CalcLigFromDirectionLight(SPSIn psIn, DirectionLight dirLig, float specPow)
{
    //ディレクションライトによるLambert拡散反射光を計算する
    float3 diffDirection = CalcLambertDiffuse(dirLig.direction, dirLig.color, psIn.normal);
	//ディレクションライトによるPhong鏡面反射光を計算する
    float3 specDirection = CalcPhongSpecular(dirLig.direction, dirLig.color, psIn.worldPos, psIn.normal, specPow);
	//ディレクションライトの最終的な反射光を返す
    return diffDirection + specDirection;
}

//ポイントライトの計算
float3 CalcLigFromPointLight(SPSIn psIn, PointLight ptlig, float specPow)
{
    //サーフェイスに入射するポイントライトの光の向きを計算する
    float3 ligDir = psIn.worldPos - ptlig.position;
    
    //正規化
    ligDir = normalize(ligDir);
    
    //ポイントライトによるLambert拡散反射光を計算する
    float3 diffPoint = CalcLambertDiffuse(
    ligDir,
    ptlig.color,
    psIn.normal
    );
    
    //ポイントライトによるPhong鏡面反射光を計算する
    float3 specPoint = CalcPhongSpecular(
    ligDir,
    ptlig.color,
    psIn.worldPos,
    psIn.normal,
    specPow
    );
    
    //距離による影響率を計算する
    //ポイントライトとの距離を計算する
    float3 distance = length(psIn.worldPos - ptlig.position);
    
    //影響率を距離によって変化させる
    float affect = 1.0f - 1.0f / ptlig.attn.x * distance;
    
    //影響率がマイナスにならないようにする
    affect = max(0.0f, affect);
    
    //乗算して影響率の変化を指数関数的にする
    affect = pow(affect, ptlig.attn.y);
    
    return (diffPoint + specPoint) * affect;
}

//スポットライトの計算
float3 CalcLigFromSpotLight(SPSIn psIn, SpotLight spLig, float specPow)
{
    //サーフェイスに入射するスポットライトの光の向きを計算
    float3 ligDir = psIn.worldPos - spLig.position;
    
    //正規化する
    ligDir = normalize(ligDir);
    
    //スポットライトによるLambert拡散反射光を計算する
    float3 diffLight = CalcLambertDiffuse(
    ligDir,
    spLig.color,
    psIn.normal
    );
    
    //ポイントライトによるPhong鏡面反射光を計算する
    float3 specLight = CalcPhongSpecular(
    ligDir,
    spLig.color,
    psIn.worldPos,
    psIn.normal,
    specPow
    );
    
    //距離による影響率を計算する
    //スポットライトとの距離を計算する
    float3 distance = length(psIn.worldPos - spLig.position);
    
    //影響率を距離に応じて小さくする
    float affect = 1.0f - 1.0f / spLig.range * distance;
    
    //影響率がマイナスにならないように
    affect = max(0.0f, affect);
    
    //影響の仕方を指数関数的にする
    affect = pow(affect, spLig.pow.x);
    
    //影響率を乗算して反射光を弱める
    diffLight *= affect;
    specLight *= affect;
    
    //角度による影響率を計算する
    //入射光と射出方向の角度を求める
    float angle = dot(ligDir, spLig.direction);
    
    //dotで求めた値をacosに渡して角度を求める
    angle = abs(acos(angle));
    
    //角度に比例して小さくなっていく影響率を計算
    affect = 1.0f - 1.0f / spLig.angle * angle;
    
    //影響率がマイナスにならないように
    affect = max(0.0f, affect);
    
    //影響の仕方を指数関数的にする
    affect = pow(affect, spLig.pow.y);
    
    //影響率に反射光を乗算して、影響を弱める
    diffLight *= affect;
    specLight *= affect;
    
    return diffLight + specLight;
}

// Lambert拡散反射光の計算
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal)
{
	//ピクセルの法線とライトの方向の内積を計算する
    float t = dot(normal, lightDirection) * -1.0f;
    
    //内積の結果が0より小さい時は0にする
    t = max(0.0f, t);
    
    //拡散反射光を計算する
    return lightColor * t;
}

//Phonng鏡面反射光の計算
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal, float specPow)
{
	//反射ベクトルを求める
    float3 refVec = reflect(lightDirection, normal);
	
	//光が当たったサーフェイスから視点に伸びるベクトルを求める
    float3 toEye = m_eyePos - worldPos;
	
	//正規化
    toEye = normalize(toEye);
	
	//鏡面反射の強さを求める
    float t = dot(refVec, toEye);
    
    //内積の結果が0より小さい時は0にする
    t = max(0.0f, t);
    
    //鏡面反射の強さを絞る
    t = pow(t, 5.0f);
    
    //鏡面反射光を求める
    float3 specularLig = lightColor * t;
    
    return specularLig * specPow;
}
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
	if( hasSkin ){
		m = CalcSkinMatrix(vsIn.skinVert);
	}else{
		m = mWorld;
	}
    // モデルの頂点をワールド座標系に変換
    psIn.pos = mul(m, vsIn.pos); 
    psIn.worldPos = psIn.pos;
    // ワールド座標系からカメラ座標系に変換
	psIn.pos = mul(mView, psIn.pos);
    // カメラ座標系からスクリーン座標系に変換
	psIn.pos = mul(mProj, psIn.pos);
	//法線を回転させる
    psIn.normal = mul(m, vsIn.normal); 

	psIn.uv = vsIn.uv;

    //カメラ空間の法線
    psIn.normalInView = mul(mView, psIn.normal);

    //接ベクトルと従ベクトルをワールド空間に変換
    psIn.tangent = normalize(mul(m, vsIn.tangent));
    psIn.biNormal = normalize(mul(m, vsIn.biNormal));
    
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
float4 PSMain( SPSIn psIn ) : SV_Target0
{
    //UV座標をサンプリング
    float3 localNormal = g_normalMap.Sample(g_sampler, psIn.uv);
    localNormal = (localNormal - 0.5) * 2.0f;
    
    psIn.normal = psIn.tangent * localNormal.x
                + psIn.biNormal * localNormal.y
                + psIn.normal * localNormal.z;
    
    psIn.normal = normalize(psIn.normal);

    float specPow = g_speclarMap.Sample(g_sampler, psIn.uv);
        
    //最終的合成
    float3 finalLig;
    
    finalLig.x = 0.0f;
    finalLig.y = 0.0f;
    finalLig.z = 0.0f;
    
    //ココからディレクションライトの計算
    
    for (int dirligNo = 0; dirligNo < NUM_DIRECTIONAL_LIGHT; dirligNo++)
    {
        finalLig += CalcLigFromDirectionLight(psIn, m_directionalLight[dirligNo], specPow);
    }

    //ココからポイントライトの計算
    
    //使用されているポイントライトがあるか確認
    if (m_numPointLight <= 0 == false)
    {
        //処理したポイントライトの数を確認する変数
        int afpCountPt = 0;
        
        //ポイントライトの配列を回して使用中のライトを探す
        for (int ptLigNo = 0; ptLigNo < MAX_POINT_LIGHT; ptLigNo++)
        {
            if (m_pointLights[ptLigNo].isUse)
            {
                //ライトの計算処理
                finalLig += CalcLigFromPointLight(psIn, m_pointLights[ptLigNo], specPow);
                //処理したライトの数を加算
                afpCountPt++;
                //処理した数が使用中のライトの数以上になったらfor文を抜ける
                if (afpCountPt >= m_numPointLight)
                {
                    break;
                }
            }
        }
    }
    
    //使用されているスポットライトがあるか確認
    if (m_numSpotLight <= 0  == false)
    {
        //処理したスポットライトの数を確認する変数
        int afpCountSp = 0;
        
        //スポットライトの配列を回して使用中のライトを探す
        for (int spLigNo = 0; spLigNo < MAX_SPOT_LIGHT; spLigNo++)
        {
            if (m_spotLights[spLigNo].isUse)
            {
                //ライトの計算処理
                finalLig += CalcLigFromSpotLight(psIn, m_spotLights[spLigNo], specPow);
                //処理したライトの数を加算
                afpCountSp++;
                //処理した数が使用中のライトの数以上になったらfor文を抜ける
                if (afpCountSp >= m_numSpotLight)
                {
                    break;
                }
            }
        }
    }
    
    //環境光の合成
    finalLig += m_ambientLight;
    
    //最終合成
    
    float4 finalColor = g_albedo.Sample(g_sampler, psIn.uv);
    
    finalColor.xyz *= finalLig;
    
    return finalColor;
}
