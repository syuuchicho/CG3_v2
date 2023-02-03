#pragma once

#include<DirectXMath.h>

/// <summary>
/// 点光源
/// </summary>
class PointLight
{
private://エイリアス
//DirectX::を省略
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;

	//DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public://サブクラス
//定数バッファ用データ構造体
	struct ConstBufferData
	{
		XMFLOAT3 lightPos;
		float pad1;
		XMFLOAT3 lightColor;
		float pad2;
		XMFLOAT3 lightatten;
		unsigned int active;
	};
public://メンバー関数

	inline void SetLightPos(const XMFLOAT3& lightPos) {
		this->lightPos = lightPos;
	}
	inline const XMFLOAT3& GetLightPos


};

