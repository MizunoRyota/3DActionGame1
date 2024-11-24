#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Pallet.h"
#include"Player.h"
#include"Enemy.h"

Enemy::Enemy()
    :position(VGet(0,-0.60f,20))
    ,angleVector(VGet(0,0,0))
    , shadowBottompos(VGet(0.0f, 0.0f, 0.0f))
    , shadowToppos(VGet(0.0f, 0.0f, 0.0f))
    , ShadowRad(1.7f)
{
    //処理なし
}

Enemy::~Enemy()
{
    MV1DeleteModel(EnemyHandle);
}

void Enemy::Load()
{
    // モデルの読み込み
    EnemyHandle = MV1LoadModel("data/model/Enemy/Enemy.mv1");
    // 3Dモデルのスケール決定
    MV1SetScale(EnemyHandle, VGet(Scale, Scale, Scale));
    // プレイヤーのモデルの座標を更新する
    MV1SetPosition(EnemyHandle, position);
}

void Enemy::Update(const Player& player)
{
    //

    //プレイヤーの方向をムク
    UpdateAngle(player);
    //Enemyの影の更新
    UpdateShadow();
}

void Enemy::UpdateAngle(const Player& player)
{
    float Angle;
    // ３Ｄモデル２から３Ｄモデル１に向かうベクトルを算出
    angleVector = VSub(player.GetPos(), position);

    // atan2 を使用して角度を取得
    Angle = atan2(angleVector.x, angleVector.z);

    // atan2 で取得した角度に３Ｄモデルを正面に向かせるための補正値( DX_PI_F )を
    // 足した値を３Ｄモデルの Y軸回転値として設定
    MV1SetRotationXYZ(EnemyHandle, VGet(0.0f, Angle + DX_PI_F, 0.0f));

}

void Enemy::UpdateShadow()
{
    shadowToppos = VGet(position.x, -0.7f, position.z);
    shadowBottompos = VGet(position.x, position.y, position.z);
}

void Enemy::DrawShadow()
{
    DrawCone3D(shadowToppos, shadowBottompos, ShadowRad, 8, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), TRUE);
}

void Enemy::Draw()
{
    DrawShadow();
    MV1DrawModel(EnemyHandle);
}