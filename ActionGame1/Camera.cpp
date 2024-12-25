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
    ,shakeTime(0)
    ,isDamage(true)
    ,TargetHight(1.3f)
    ,position  (VGet(0, 0, 0))
    ,OriginalOffset(VGet(0, 1.50f, -5.0f))
{
    //奥行0.1～1000までをカメラの描画範囲とする
    SetCameraNearFar(0.10f, 1000.0f);
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
    Zoom = -4.0f;
    position = VGet(0, Hight, Zoom);
}

void Camera::Update(const Player& player)
{

    // TODO:z軸上で、プレイヤーから一定距離離れた状態でプレイヤーを常に見続けるよう位置調整
    // カメラに位置を反映.
    targetposition = VAdd(player.GetPos(), VGet(-0.0f, TargetHight, 0.0f));
    if (isDamage)
    {
        ShakeCamera(shakeIntensity, shakeDuration,player);
    }
    else
    {
        position = VAdd(player.GetPos(), VGet(-0.0f, Hight, Zoom));
    }
    // カメラに位置を反映.
    SetCameraPositionAndTarget_UpVecY(position, targetposition);

}

void Camera::ShakeCamera(float intensity, float duration,const Player& player)
{

    if (shakeTime < duration)
    {
        // ランダムな揺れを生成
        Offset.x = (rand() % 3 - 1) * intensity / 100.0f;
        Offset.y = (rand() % 3 - 1) * intensity / 100.0f;
        Offset.z = (rand() % 3 - 1) * intensity / 100.0f;

        // カメラ位置を更新
        position=VGet(OriginalOffset.x + Offset.x, OriginalOffset.y + Offset.y, OriginalOffset.z + Offset.z);

        // 時間を進める
        shakeTime += 0.50f;
    }
    else
    {
        // 揺れが終了したら元の位置に戻す
        position = VAdd(player.GetPos(), VGet(-0.0f, Hight, Zoom));
        shakeTime = 0.0f;
        isDamage = false;
    }
}