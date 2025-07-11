/*!
 * @brief	ディファードレンダリングをするためのシェーダー
 */
////////////////////////////////////////////////
// 定数
////////////////////////////////////////////////
static const int NUM_DIRECTIONAL_LIGHT = 2; // ディレクションライトの数
static const int MAX_POINT_LIGHT = 10; // ポイントライトの最大数
static const int MAX_SPOT_LIGHT = 10; // スポットライトの最大数

////////////////////////////////////////////////
// ライトの構造体
////////////////////////////////////////////////
struct DirectionLight
{    
    //ライトのビュープロジェクション
    float4x4 mLVP;
	//ライトの方向
    float3 direction;
	//パディング1
    int pad1;
	//カラー
    float3 color;
	//パディング2
    int pad2;
	//ビュープロジェクションカメラのポジション
    float3 ligPos;
	//影をキャストするかしないか
    int m_castShadow;
	//使用されいているかどうか
    int isUse;
	//パディング3
    int pad3;
	//パディング4(配列ずれ合わせ分)
    int pad4[2];
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
Texture2D<float4> worldPosTexture : register(t2);//ワールド座標
sampler Sampler : register(s0);
////////////////////////////////////////////////
// 関数宣言
////////////////////////////////////////////////
//Lambert拡散反射光の計算
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal);
//Phonng鏡面反射光の計算
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal, float specPow);
//ディレクションライトの配列単位の計算
float3 CalcLigFromDirectionLightList(float3 worldPos,float3 normal,float spec);
//ディレクションライトの計算
float3 CalcLigFromDirectionLight(DirectionLight dirLig ,float3 worldPos ,float3 normal, float specPow);
////////////////////////////////////////////////
// 関数定義。
////////////////////////////////////////////////
// Lambert拡散反射光の計算
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal)
{
	//ピクセルの法線とライトの方向の内積を計算する
    float t = dot(normal, lightDirection) * -1.0f;
    
    //内積の結果が0より小さい時は0にする
    t = max(0.0f, t);
    
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
//配列単位のディレクションライトの計算
float3 CalcLigFromDirectionLightList(float3 worldPos ,float3 normal, float spec)
{
    float3 calcValue;
    
    calcValue.x = 0.0f;
    calcValue.y = 0.0f;
    calcValue.z = 0.0f;

    if (m_numDirectionLight == 0)
    {
        return calcValue;
    }
    
    //処理したディレクションライトの数を確認する変数
    int afpCountDi = 0;
        
        //ディレクションライトの配列を回して使用中のライトを探す
    for (int diLigNo = 0; diLigNo < NUM_DIRECTIONAL_LIGHT; diLigNo++)
    {
        if (m_directionalLight[diLigNo].isUse)
        {
            //ライトの計算処理
            calcValue += CalcLigFromDirectionLight(m_directionalLight[diLigNo],worldPos,normal, spec);
                //処理したライトの数を加算
            afpCountDi++;
                //処理した数が使用中のライトの数以上になったらfor文を抜ける
            if (afpCountDi >= m_numDirectionLight)
            {
                break;
            }
        }
    }
    
    return calcValue;
}
//ディレクションライトによる反射光を計算
float3 CalcLigFromDirectionLight(DirectionLight dirLig, float3 worldPos, float3 normal, float specPow)
{
    //ディレクションライトによるLambert拡散反射光を計算する
    float3 diffDirection = CalcLambertDiffuse(dirLig.direction, dirLig.color, normal);
	//ディレクションライトによるPhong鏡面反射光を計算する
    float3 specDirection = CalcPhongSpecular(dirLig.direction, dirLig.color, worldPos, normal, specPow);
	//ディレクションライトの最終的な反射光を返す
    return diffDirection + specDirection;
}

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
    float4 normal = normalTexture.Sample(Sampler, In.uv);
    
    float3 worldPos = worldPosTexture.Sample(Sampler, In.uv).xyz;
    normal = (normal * 2.0f) - 1.0f; //法線を-1.0～1.0に変換
	
	//ライト計算
    float3 lig = 0.0f;
    
    lig += CalcLigFromDirectionLightList(worldPos,normal.xyz, normal.w);
    
    float4 finalColor = albedo;
    finalColor.xyz *= lig;
    
    return finalColor;
}