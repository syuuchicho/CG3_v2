#pragma once

#include<DirectXMath.h>

/// <summary>
/// �_����
/// </summary>
class PointLight
{
private://�G�C���A�X
//DirectX::���ȗ�
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;

	//DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public://�T�u�N���X
//�萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData
	{
		XMFLOAT3 lightPos;
		float pad1;
		XMFLOAT3 lightColor;
		float pad2;
		XMFLOAT3 lightatten;
		unsigned int active;
	};
public://�����o�[�֐�

	inline void SetLightPos(const XMFLOAT3& lightPos) {
		this->lightPos = lightPos;
	}
	inline const XMFLOAT3& GetLightPos


};

