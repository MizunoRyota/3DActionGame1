#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Stage.h"

Stage::Stage()
    :position(VGet(0,0,0))
    ,StageHandle(-1)
{
    //�����Ȃ�
}

Stage::~Stage()
{

}

void Stage::Load()
{
    StageHandle = MV1LoadModel("data/model/stage/Stage.mv1");
    // 3D���f���̃X�P�[������
    MV1SetScale(StageHandle, VGet(Scale, Scale, Scale));
}

void Stage::Draw()
{
    MV1DrawModel(StageHandle);
}

