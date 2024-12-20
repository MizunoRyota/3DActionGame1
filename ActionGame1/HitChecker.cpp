#include"DxLib.h"
#include"Pallet.h"
#include"Player.h"
#include"Enemy.h"
#include"HitChecker.h"

HitChecker::HitChecker()
//プレイヤーの判定
    :playerRadius(1.00f)
    , playerCircle(VGet(0, 0, 0))
    //Enemyの判定
    , enemyRadius(2.0f)
    , enemyCircle(VGet(0, 0, 0))
    //当たっているか
    , isHit(false)
    , Length (0)
{
    //処理なし
}

HitChecker::~HitChecker()
{
}

void HitChecker::Update(const Player& player,const Enemy& enemy  )
{
    //プレイヤーの球
    playerCircle = VAdd(player.GetPos(), VGet(0.0f, PlayerHight, 0.0f));
    //Enemyの球
    enemyCircle = VAdd(enemy.GetPos(), VGet(0.0f, PlayerHight, 0.0f));
    //当たっているかのチェック
    isHit = CheckHit(player, enemy);

}

bool HitChecker::CheckHit(const Player& player, const Enemy& enemy)
{
    //プレイヤーとEnemyの距離の合計を獲得
    keepDistance = VSub(player.GetPos(), enemy.GetPos());
    //プレイヤーとEnemyの半径の合計
    Length = playerRadius + enemyRadius;
    //ベクトルを2乗
    Distance = VSquareSize(keepDistance);
    //LengthよりDistanceちいさくなったとき返す
    return Distance <= (Length * Length);
}

void HitChecker::DrawCircle()
{
    if (CheckHitKey(KEY_INPUT_F))
    {
        clsDx();
        printfDx("isHit%d\n", isHit);
        printfDx("Distance%f\n", Distance);
        printfDx("Length%f\n",Length),
        DrawSphere3D(playerCircle, playerRadius, 16, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), false);
        DrawSphere3D(enemyCircle, enemyRadius, 16, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), false);
    }
}

