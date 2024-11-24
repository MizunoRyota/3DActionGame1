#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Stage.h"

Stage::Stage()
    :position(VGet(0, 0, -20))
    , StageHandle(-1)
{
    //処理なし
}

Stage::~Stage()
{

}

void Stage::Load()
{
    StageHandle = MV1LoadModel("data/model/stage/NewStage.mv1");
    // 3Dモデルのスケール決定
    MV1SetScale(StageHandle, VGet(Scale, Scale, Scale));
    // ３ＤモデルのY軸の回転値を正面にセットする
    MV1SetRotationXYZ(StageHandle, VGet(0.0f, 180.0f * DX_PI_F / 180.0f, 0.0f));
    // ステーのモデルの座標を更新する
    MV1SetPosition(StageHandle, position);
}

void Stage::Draw()
{
    MV1DrawModel(StageHandle);
}