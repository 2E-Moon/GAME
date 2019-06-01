//==============================================================
// グローバル変数
//==============================================================
// 変換行列
float4x4 mW;		// ワールド行列
float4x4 mV;		// ビュー行列
float4x4 mP;		// 射影行列

// マテリアル関係
float4	Diffuse = float4(1, 1, 1, 1);	// 基本色
float	Ambient = 0.3;				// 環境光の強さ
float4	Specular = float4(1, 1, 1, 1);	// 反射色
float	Power = 50;					// 反射色の力

texture MeshTex;	// マテリアルのテクスチャ
sampler MeshSmp = sampler_state {	// MeshTex用サンプラ
	Texture = <MeshTex>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

// ライト用
float3 LightDir;	// ライトの方向

// カメラ用
float3 CamPos;		// 視点の位置

// トゥーン用
texture ToonTex;	// 陰影用テクスチャ
sampler ToonSmp = sampler_state {	// ToonTex用サンプラ
	Texture = <ToonTex>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = Clamp;
	AddressV = Clamp;
};

//==============================================================
// 頂点シェーダからピクセルシェーダに渡すデータ用構造体
//==============================================================
struct VS_OUT {
	float4 Pos		: POSITION;		// 2D座標
	float2 MeshUV	: TEXCOORD0;	// テクスチャUV

	float3 wPos		: TEXCOORD1;	// 3D座標
	float3 wN		: TEXCOORD2;	// 法線
};

//==============================================================
// 頂点シェーダ
//	・頂点が１つ送られてくるので、それを処理しピクセルシェーダに渡す。
//==============================================================
VS_OUT VS(
	float4 pos : POSITION,				// 座標
	float3 normal : NORMAL,				// 法線
	float2 mesh_uv : TEXCOORD0			// テクスチャUV
	) {
	VS_OUT Out = (VS_OUT)0;		// ピクセルデータに渡すデータ用構造体

	// 頂点座標
	Out.Pos = mul(pos, mW);
	Out.wPos = Out.Pos.xyz;	// 3D空間での座標になる
	Out.Pos = mul(Out.Pos, mV);	// 3Dカメラ座標系での座標になる
	Out.Pos = mul(Out.Pos, mP);	// 2D空間での座標になる

	// テクスチャ座標
	Out.MeshUV = mesh_uv;

	// 法線
	float3 w_normal = normalize(mul(normal, (float3x3)mW));	// ワールド系に変換
		Out.wN = w_normal;

	return Out;
}


//==================================================================
// ピクセルシェーダ
//	・ピクセルの色を決定し、その色を返す(R,G,B,Aのfloat4型)
//==================================================================
float4 PS(VS_OUT In) : COLOR0
{
	// 法線を正規化
	float3 w_normal = normalize(In.wN);

	//================================================
	// ライティング(ランバート照明)
	//================================================
	float LPow = dot(-LightDir, w_normal);	// 光の強さ -1～1
	LPow = max(0, LPow);	// 0～1

	//================================================
	// トゥーンテクスチャから明るさ取得
	//================================================
	float4 ToonCol = tex2D(ToonSmp, float2(LPow + Ambient, 0));

	//================================================
	// スペキュラ
	//================================================
	float3 vCam = normalize(CamPos - In.wPos);		// 目(カメラ)への方向
	float3 vRef = LightDir + 2.0f * dot(w_normal, -LightDir) * w_normal;
	float SpePow = pow(max(0, dot(vCam, vRef)), Power);
	float4 Spe = Specular * SpePow;

	//================================================
	// モデル色算出
	//================================================
	// 最終的なモデルの色を入れる変数
	float4 Col = tex2D(MeshSmp, In.MeshUV);	// まずはテクスチャ色を入れる

	//================================================
	// 材質色合成
	//================================================
	Col *= Diffuse;

	//================================================
	// ライティング適用
	//================================================
	// ライトの当たりの強さ+環境光
	Col.rgb *= ToonCol.rgb;// min(1, LPow + Ambient);

	//================================================
	// 色を出力
	//================================================
	return Col + Spe;
}

//==============================================================
// テクニック
//==============================================================
technique Tech {
	pass P0 {
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS();
	}
}
