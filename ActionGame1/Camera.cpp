#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Player.h"
#include"Camera.h"

/// <summary>
/// コンストラクタ
/// </summary>
Camera::Camera()
    :Zoom  (0)
    ,Hight  (0)
    ,TargetHight(1.3f)
    ,position  (VGet(0, 0, 0))
{
    //奥行0.1～1000までをカメラの描画範囲とする
    SetCameraNearFar(0.1f, 10000.0f);
}

/// <summary>
/// デストラクタ
/// </summary>
Camera::~Camera()
{
    // 処理なし.
}

void Camera::Load()
{
    Hight = 1.5f;
    Zoom = -5.0f;
    position = VGet(0, Hight, Zoom);
}

void Camera::Update(const Player& player)
{

    // TODO:z軸上で、プレイヤーから一定距離離れた状態でプレイヤーを常に見続けるよう位置調整
    // カメラに位置を反映.

    targetposition = VAdd(player.GetPos(), VGet(-0.0f, TargetHight, 0.0f));
    position = VAdd(player.GetPos(), VGet(-0.0f, Hight, Zoom));

    // カメラに位置を反映.
    SetCameraPositionAndTarget_UpVecY(position, targetposition);

}

