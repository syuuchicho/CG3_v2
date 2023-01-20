#include "OBJShaderHeader.hlsli"
//5-2
VSOutput main(float4 pos : POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD)
{

	////右,下,奥の方向を向いたライト
	//float3 lightdir = float3(1, -1, 1);
	//lightdir = normalize(lightdir);
	////ライトの色(白)
	//float3 lightcolor = float3(1, 1, 1);
	//法線にワールド行列によるスケーリング 回転を適用
	float4 wnormal = normalize(mul(world, float4(normal, 0)));
	float4 wpos = mul(world, pos);
	// ピクセルシェーダーに渡す値
	VSOutput output; 
	output.svpos = mul(mul(viewproj,world),pos);
	float3 ambient = m_ambient;
	//拡散反射光
	float3 diffuse = dot(lightv,wnormal.xyz) * m_diffuse;
	//光沢度
	const float shininess = 4.0f;
	////頂点から視点への方向ベクトル
	float3 eyedir = normalize(cameraPos - wpos.xyz);
	//環境反射光
	////視点座標
	//const float3 eye = float3(0, 0, -20);
	
	//反射光ベクトル
	float3 reflect = normalize(-lightv + 2 * dot(lightv, wnormal.xyz) * wnormal.xyz);
	//鏡面反射光
	float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * m_specular;

	//全て加算する
	output.color.rgb = (ambient + diffuse + specular) * lightcolor;
	output.color.a = m_alpha;
	output.uv = uv;
	//output.normal = normal;
	return output;
}
