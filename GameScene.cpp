﻿#include "GameScene.h"
#include "Model.h"
#include <cassert>
#include <sstream>
#include <iomanip>
#include<imgui.h>

using namespace DirectX;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	delete spriteBG;
	delete objSkydome;
	delete objGround;
	delete objFighter;
	delete objSphere;
	delete objSphere2;
	delete modelSkydome;
	delete modelGround;
	delete modelFighter;
	delete modelSphere;
	delete modelSphere2;
	delete camera;
	delete lightGroup;
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input)
{
	// nullptrチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	this->input = input;

	// デバッグテキスト用テクスチャ読み込み
	Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
	// デバッグテキスト初期化
	debugText.Initialize(debugTextTexNumber);

	// テクスチャ読み込み
	Sprite::LoadTexture(1, L"Resources/background.png");

	// カメラ生成
	camera = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight, input);

	// カメラ注視点をセット
	camera->SetTarget({ 0, 1, 0 });
	camera->SetDistance(3.0f);

	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera);

	// 背景スプライト生成
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });
	// 3Dオブジェクト生成
	objSkydome = Object3d::Create();
	objGround = Object3d::Create();
	objFighter = Object3d::Create();
	objSphere = Object3d::Create();
	objSphere2 = Object3d::Create();


	//ライト生成
	lightGroup = LightGroup::Create();
	//3Dオブジェクトにライトをセット
	Object3d::SetLightGroup(lightGroup);

	// テクスチャ2番に読み込み
	Sprite::LoadTexture(2, L"Resources/texture.png");

	modelSkydome = Model::CreateFromOBJ("skydome");
	modelGround = Model::CreateFromOBJ("ground");
	modelFighter = Model::CreateFromOBJ("chr_sword");
	//modelFighter = Model::CreateFromOBJ("sphere");
	modelSphere = Model::CreateFromOBJ("sphere", true);
	modelSphere2= Model::CreateFromOBJ("sphere");

	objSkydome->SetModel(modelSkydome);
	objGround->SetModel(modelGround);
	objFighter->SetModel(modelFighter);
	objSphere->SetModel(modelSphere);
	objSphere2->SetModel(modelSphere2);
	objFighter->SetPosition({ +1,2,0 });
	//objFighter->SetPosition({ -1,1,0 });
	objSphere->SetPosition({ -1,1,0 });
	objSphere2->SetPosition({ +1,1,0 });


}

void GameScene::Update()
{
	camera->Update();
	lightGroup->Update();

	objSkydome->Update();
	objGround->Update();
	objFighter->Update();
	objSphere->Update();
	objSphere2->Update();


#pragma region オブジェクトの回転
	XMFLOAT3 rot = objSphere->GetRotation();
	rot.y += 1.0f;
	objSphere->SetRotation(rot);
	objSphere2->SetRotation(rot);
	objFighter->SetRotation(rot);
#pragma endregion

	//光線方向初期値			   上奥
	static XMVECTOR lightDir = { 0,1,5,0 };

	if (input->PushKey(DIK_W))
	{
		lightDir.m128_f32[1] += 1.0f;
	}
	else if (input->PushKey(DIK_S))
	{
		lightDir.m128_f32[1] -= 1.0f;
	}
	if (input->PushKey(DIK_D))
	{
		lightDir.m128_f32[0] += 1.0f;
	}
	else if (input->PushKey(DIK_A))
	{
		lightDir.m128_f32[0] -= 1.0f;
	}

	//lightGroup->SetLightDir(lightDir);

	std::ostringstream debugstr;
	debugstr << "lightDirFactor("
		<< std::fixed << std::setprecision(2)
		<< lightDir.m128_f32[0] << ","
		<< lightDir.m128_f32[1] << ","
		<< lightDir.m128_f32[2] << ")";
	debugText.Print(debugstr.str(), 50, 50, 1.0f);
	debugstr.str("");
	debugstr.clear();

	const XMFLOAT3& cameraPos = camera->GetEye();
	debugstr << "cameraPos("
		<< std::fixed << std::setprecision(2)
		<< cameraPos.x << ","
		<< cameraPos.y << ","
		<< cameraPos.z << ")";
	debugText.Print(debugstr.str(), 50, 70, 1.0f);

	/*debugText.Print("AD: move camera LeftRight", 50, 50, 1.0f);
	debugText.Print("WS: move camera UpDown", 50, 70, 1.0f);
	debugText.Print("ARROW: move camera FrontBack", 50, 90, 1.0f);*/

	//imguiからのライトパラメータを反映
	lightGroup->SetAmbientColor(XMFLOAT3(ambientColor));
	lightGroup->SetDirLightDir(0, XMVECTOR({ lightDir0[0],lightDir0[1] ,lightDir0[2],0 }));
	lightGroup->SetDirLightColor(0, XMFLOAT3(lightColor0));
	lightGroup->SetDirLightDir(1, XMVECTOR({ lightDir1[0],lightDir1[1] ,lightDir1[2],0 }));
	lightGroup->SetDirLightColor(1, XMFLOAT3(lightColor1));
	lightGroup->SetDirLightDir(2, XMVECTOR({ lightDir2[0],lightDir2[1] ,lightDir2[2],0 }));
	lightGroup->SetDirLightColor(2, XMFLOAT3(lightColor2));
}

void GameScene::Draw()
{
	ImGui::Begin("light");
	ImGui::SetWindowPos(ImVec2( 0,0 ));
	ImGui::SetWindowSize(ImVec2(500, 200));
	ImGui::ColorEdit3("ambientColor", ambientColor, ImGuiColorEditFlags_Float);
	ImGui::InputFloat3("lightDir0", lightDir0);
	ImGui::ColorEdit3("lightColor0", lightColor0, ImGuiColorEditFlags_Float);
	ImGui::InputFloat3("lightDir1", lightDir1);
	ImGui::ColorEdit3("lightColor1", lightColor1, ImGuiColorEditFlags_Float);
	ImGui::InputFloat3("lightDir2", lightDir2);
	ImGui::ColorEdit3("lightColor2", lightColor2, ImGuiColorEditFlags_Float);
	ImGui::End();


	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画
	//spriteBG->Draw();

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	spriteBG->Draw();
	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(cmdList);

	// 3Dオブクジェクトの描画
	objSkydome->Draw();
	objGround->Draw();
	objFighter->Draw();
	objSphere->Draw();
	objSphere2->Draw();


	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	//// 描画
	//sprite1->Draw();
	//sprite2->Draw();

	// デバッグテキストの描画
	debugText.DrawAll(cmdList);

	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}
