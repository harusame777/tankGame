/*!
 * @brief	画像を表示するためのシェーダー
 */

//ワイプのパラメーターの定数バッファー
cbuffer WipeCB : register(b1)
{
    float2 wipeDirection;	//ワイプの方向
    float wipeSize;			//ワイプサイズ
    float pramA;			//アルファ値
    int colorState;         //カラーステート
}

cbuffer cb : register(b0){
    float4x4 mvp;		//MVP行列
    float4 mulColor;	//乗算カラー
};
struct VSInput{
	float4 pos : POSITION;
	float2 uv  : TEXCOORD0;
};

struct PSInput{
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

Texture2D<float4> colorTexture : register(t0); // カラーテクスチャ
Texture2D<float4> oxygenGaugeAlphaTexture : register(t20); //アルファ値操作用のテクスチャ

sampler Sampler : register(s0);

PSInput VSMain(VSInput In) 
{
	PSInput psIn;
	psIn.pos = mul( mvp, In.pos );
	psIn.uv = In.uv;
	
	return psIn;
}
float4 PSMain( PSInput In ) : SV_Target0
{
    float4 color = colorTexture.Sample(Sampler, In.uv) * mulColor;
	
    float4 alphaTex = oxygenGaugeAlphaTexture.Sample(Sampler, In.uv);
	
	//ピクセル座標をワイプ方向に射影する
    float t = dot(wipeDirection, In.pos.xy);
    clip(t - wipeSize);
    
    if(colorState == 1 &&
        alphaTex.g < 0.9f)
    {
        color.r += 1.0f;
        color.b -= 0.9f;
    }
    else if (colorState == 2 &&
        alphaTex.g < 0.9f)
    {
        color.r += 1.0f;
        color.b -= 0.6f;
        color.g -= 0.6f;
    }
    
    if (alphaTex.g < 0.9f)
    {
        color.a = pramA;
    }

    return color;
}