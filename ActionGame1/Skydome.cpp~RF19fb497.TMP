#include"DxLib.h"
#include"skydome.h"
Skydome::Skydome()
{
    // ３Ｄモデルの読み込み
    SkydomeHandle = MV1LoadModel("data/model/Skydome/Sunny/Dome_X501.pmx");
    pos = VGet(0, 0, -50);
    // プレイヤーのモデルの座標を更新する
    MV1SetPosition(SkydomeHandle, pos);
    // 3Dモデルのスケール決定
    MV1SetScale(SkydomeHandle, VGet(Scale, Scale, Scale));
}

Skydome::~Skydome()
{
    // モデルのアンロード.
    MV1DeleteModel(SkydomeHandle);
}

void Skydome::SkydomeUpdate()
{
    //スカイドームを回転させる
    pos.y -= 0.0003;
    MV1SetRotationXYZ(SkydomeHandle, VGet(0.0f, pos.y, 0.0f));
}

void Skydome::SkydomeTitle()
{
    pos.y -= 0.001;
    MV1SetRotationXYZ(SkydomeHandle, VGet(0.0f, pos.y, 0.0f));
}

void Skydome::SkydomeDraw()
{
    // ３Ｄモデルの描画
    MV1DrawModel(SkydomeHandle);
}