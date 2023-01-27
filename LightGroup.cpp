#include "LightGroup.h"

using namespace DirectX;

/// <summary>
/// 静的メンバー変数の実体
/// </summary>
ID3D12Device* LightGroup::device = nullptr;

void LightGroup::StaticInitialize(ID3D12Device* device)
{
	//再初期化チェック
	assert(!LightGroup::device);
	//nullptrチェック
	assert(device);
	//静的メンバー変数のセット
	LightGroup::device = device;
}