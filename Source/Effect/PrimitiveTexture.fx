//ワールド転置逆行列
float4x4 gMatWIT;

//ワールドビュー射影変換行列宣言
float4x4 gMatWVP;

//アンビエントライトの色
float4 gAmbientColor;

//ディレクショナルライトの方向
float3 gLightDir;

//ディレクショナルライトの色
float4 gLightColor;

//マテリアルの色
float4 gMaterialDiffuse;

//マテリアルのアンビエント
float4 gMaterialAmbient;

//テクスチャー
texture gTexture;
sampler texSampler = sampler_state
{
	Texture = <gTexture>;

	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;

	AddressU = WRAP;
	AddressV = WRAP;
};

//頂点シェーダー入力用
struct VS_INPUT
{
	float3 position : POSITION;
	float3 normal   : NORMAL;
	float2 texCoord : TEXCOORD0;
};

//頂点シェーダー出力用
struct VS_OUTPUT {
	float4 position : POSITION;
	float4 color    : COLOR0;
	float2 texCoord : TEXCOORD0;
};

//ピクセルシェーダー入力用
struct PS_INPUT {
	float4 position : POSITION;
	float4 color    : COLOR0;
	float2 texCoord : TEXCOORD0;
};

//ピクセルシェーダー出力用
struct PS_OUTPUT {
	float4 color : COLOR0;
};

// 頂点シェーダ
VS_OUTPUT TextureVS(VS_INPUT In)
{
	VS_OUTPUT Out;

	//頂点に変換行列を乗算する
	Out.position = mul(float4(In.position, 1.0f), gMatWVP);

	//float4へ変換
	float4 normal = normalize(mul(float4(In.normal, 0.0f), gMatWIT));

	//ディレクショナルライトの方向を逆にする（次の計算のため）
	float4 revLightDir = -float4(gLightDir, 0.0f);

	//法線とディレクショナルライトの方向の内積にディレクショナルライトの色を乗算しアンビエントライトの色と加算
	//saturate　→　結果を0.0から1.0までの範囲に収める
	Out.color = saturate(gAmbientColor * gMaterialAmbient + gLightColor * gMaterialDiffuse * max(0, dot(revLightDir, normal)));

	//UV座標の設定
	Out.texCoord = In.texCoord;

	return Out;
}

// ピクセルシェーダ
PS_OUTPUT TexturePS(PS_INPUT In)
{
	PS_OUTPUT Out;

	//テクスチャーの色を取得
	float4 texColor = tex2D(texSampler, In.texCoord);

	//ライティング済みの色とテクスチャーの色を乗算する
	Out.color = texColor * In.color;

	return Out;
}

// 頂点シェーダ
VS_OUTPUT NonTextureVS(VS_INPUT In)
{
	VS_OUTPUT Out;

	//頂点に変換行列を乗算する
	Out.position = mul(float4(In.position, 1.0f), gMatWVP);

	//float4へ変換
	float4 normal = normalize(mul(float4(In.normal, 0.0f), gMatWIT));

	//ディレクショナルライトの方向を逆にする（次の計算のため）
	float4 revLightDir = -float4(gLightDir, 0.0f);

	//法線とディレクショナルライトの方向の内積にディレクショナルライトの色を乗算しアンビエントライトの色と加算
	//saturate　→　結果を0.0から1.0までの範囲に収める
	Out.color = saturate(gAmbientColor * gMaterialAmbient + gLightColor * gMaterialDiffuse * max(0, dot(revLightDir, normal)));

	//UV座標の設定
	Out.texCoord = In.texCoord;

	return Out;
}

// ピクセルシェーダ
PS_OUTPUT NonTexturePS(PS_INPUT In)
{
	PS_OUTPUT Out;

	Out.color = In.color;

	return Out;
}

//テクニック
technique PrimitiveTextureTec
{
	pass P0
	{
		VertexShader = compile vs_3_0 TextureVS();
		PixelShader = compile ps_3_0 TexturePS();
	}
	pass P1
	{
		VertexShader = compile vs_3_0 NonTextureVS();
		PixelShader = compile ps_3_0 NonTexturePS();
	}
}