#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Pallet.h"
#include"Enemy.h"
#include"HitChecker.h"
#include"EnemyAttackRangeChecker.h"
#include"Player.h"

EnemyAttackRangeChecker::EnemyAttackRangeChecker()
    :AttackShrotRange(5.0f)
    , AttackMiddleRange(15.0f)
    , AttackLongRange(50.0f)
    , LengthRange(0)
{

}

EnemyAttackRangeChecker::~EnemyAttackRangeChecker()
{

}

void EnemyAttackRangeChecker::Update(const Player& player, const Enemy& enemy)
{
    //当たっているかのチェック
    isShortWithin = CheckShortHit(player, enemy);
    isMiddleWithin = CheckMiddleHit(player, enemy);
    isLongWithin = CheckLongHit(player, enemy);
}

bool EnemyAttackRangeChecker::CheckShortHit(const Player& player, const Enemy& enemy)
{
    //プレイヤーとEnemyの距離の合計を獲得
    keepDistance = VSub(player.GetPos(), enemy.GetPos());
    //プレイヤーとEnemyの半径の合計
    LengthRange = playerRadius + AttackShrotRange;
    //ベクトルを2乗
    Distance = VSquareSize(keepDistance);
    //LengthよりDistanceちいさくなったとき返す
    return Distance <= (LengthRange * LengthRange);
}

bool EnemyAttackRangeChecker::CheckMiddleHit(const Player& player, const Enemy& enemy)
{
    //プレイヤーとEnemyの距離の合計を獲得
    keepDistance = VSub(player.GetPos(), enemy.GetPos());
    //プレイヤーとEnemyの半径の合計
    LengthRange = playerRadius + AttackMiddleRange;
    //ベクトルを2乗
    Distance = VSquareSize(keepDistance);
    //LengthよりDistanceちいさくなったとき返す
    return Distance <= (LengthRange * LengthRange);
}

bool EnemyAttackRangeChecker::CheckLongHit(const Player& player, const Enemy& enemy)
{
    //プレイヤーとEnemyの距離の合計を獲得
    keepDistance = VSub(player.GetPos(), enemy.GetPos());
    //プレイヤーとEnemyの半径の合計
    LengthRange = playerRadius + AttackLongRange;
    //ベクトルを2乗
    Distance = VSquareSize(keepDistance);
    //LengthよりDistanceちいさくなったとき返す
    return Distance <= (LengthRange * LengthRange);
}

void EnemyAttackRangeChecker::DrawCircle()
{
    if (CheckHitKey(KEY_INPUT_T))
    {
        clsDx();
        printfDx("isShortWithin%d\n", isShortWithin);
        printfDx("isMiddleWithin%d\n", isMiddleWithin);
        printfDx("isLongWithin%d\n", isLongWithin);
        printfDx("Distance%f\n", Distance);
        printfDx("LengthRange%f\n", LengthRange),
            DrawSphere3D(enemyCircle, AttackShrotRange, 16, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), false);
        DrawSphere3D(enemyCircle, AttackMiddleRange, 16, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), false);
        DrawSphere3D(enemyCircle, AttackLongRange, 16, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), false);
    }
}