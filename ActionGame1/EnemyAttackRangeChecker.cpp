#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Pallet.h"
#include"Player.h"
#include"Enemy.h"
#include"EnemyAttackRangeChecker.h"

EnemyAttackRangeChecker::EnemyAttackRangeChecker()
    :AttackRange(10.0f)
    , LengthRange(0)
{

}

EnemyAttackRangeChecker::~EnemyAttackRangeChecker()
{

}

void EnemyAttackRangeChecker::Update(const Player& player, const Enemy& enemy)
{
    //当たっているかのチェック
    isWithin = CheckHit(player, enemy);

}

bool EnemyAttackRangeChecker::CheckHit(const Player& player, const Enemy& enemy)
{
    //プレイヤーとEnemyの距離の合計を獲得
    keepDistance = VSub(player.GetPos(), enemy.GetPos());
    //プレイヤーとEnemyの半径の合計
    LengthRange = playerRadius + AttackRange;
    //ベクトルを2乗
    Distance = VSquareSize(keepDistance);
    //LengthよりDistanceちいさくなったとき返す
    return Distance <= (LengthRange * LengthRange);
}

void EnemyAttackRangeChecker::DrawCircle()
{
    if (CheckHitKey(KEY_INPUT_R))
    {
        clsDx();
        printfDx("isWithin%d\n", isWithin);
        printfDx("Distance%f\n", Distance);
        printfDx("LengthRange%f\n", LengthRange),
        DrawSphere3D(playerCircle, AttackRange, 16, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), false);

        DrawSphere3D(enemyCircle, AttackRange, 16, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), false);
    }
}