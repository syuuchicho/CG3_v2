#include "LightGroup.h"

using namespace DirectX;

/// <summary>
/// �ÓI�����o�[�ϐ��̎���
/// </summary>
ID3D12Device* LightGroup::device = nullptr;

void LightGroup::StaticInitialize(ID3D12Device* device)
{
	//�ď������`�F�b�N
	assert(!LightGroup::device);
	//nullptr�`�F�b�N
	assert(device);
	//�ÓI�����o�[�ϐ��̃Z�b�g
	LightGroup::device = device;
}