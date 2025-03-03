/*!
 * @brief	画像を表示するためのシェーダー
 */

//ワイプのパラメーターの定数バッファー
cbuffer WipeCB : register(b1)
{
    float wipeSize;			//ワイプサイズ
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
	    
    float2 topDir = float2(0.0f, 1.0f);
    
    float2 bottomDir = float2(0.0f, -1.0f);
    
    float t;
	
    if (In.pos.y > 450.0f)
    {
    t = dot(bottomDir, In.pos.xy);
    float final = wipeSize  + -900.0f;
    clip(t - final);
    }
    else
    {
        t = dot(topDir, In.pos.xy);
        clip(t - wipeSize);
    }
    
    
    return color;
}