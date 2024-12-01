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
    //�������Ă��邩�̃`�F�b�N
    isWithin = CheckHit(player, enemy);

}

bool EnemyAttackRangeChecker::CheckHit(const Player& player, const Enemy& enemy)
{
    //�v���C���[��Enemy�̋����̍��v���l��
    keepDistance = VSub(player.GetPos(), enemy.GetPos());
    //�v���C���[��Enemy�̔��a�̍��v
    LengthRange = playerRadius + AttackRange;
    //�x�N�g����2��
    Distance = VSquareSize(keepDistance);
    //Length���Distance���������Ȃ����Ƃ��Ԃ�
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