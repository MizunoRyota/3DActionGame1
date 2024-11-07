#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Player.h"
#include"Camera.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Camera::Camera()
    :Zoom  (0)
    ,Hight  (0)
    ,TargetHight(1.0f)
    ,position  (VGet(0, 0, 0))
{
    //���s0.1�`1000�܂ł��J�����̕`��͈͂Ƃ���
    SetCameraNearFar(0.1f, 10000.0f);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Camera::~Camera()
{
    // �����Ȃ�.
}

void Camera::Load()
{
    Hight = 1.5f;
    Zoom = -3.0f;
    position = VGet(0, Hight, Zoom);
}

void Camera::Update(const Player& player)
{

    // TODO:z����ŁA�v���C���[�����苗�����ꂽ��ԂŃv���C���[����Ɍ�������悤�ʒu����
    // �J�����Ɉʒu�𔽉f.

    targetposition = VAdd(player.GetPos(), VGet(-0.0f, TargetHight, 0.0f));



    // �J�����Ɉʒu�𔽉f.
    SetCameraPositionAndTarget_UpVecY(position, targetposition);

}
