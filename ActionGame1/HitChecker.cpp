#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Pallet.h"
#include"HitChecker.h"
#include"Player.h"
HitChecker::HitChecker()
    //�v���C���[�̔���
    :playerRadius(0.3f)
    , playerCircle(VGet(0, 0, 0))
    //�v���C���[�̍U������
    ,playerAttackRadius(0.5f)
    , playerAttackCircle(VGet(0, 0, 0))
{
    //�����Ȃ�
}

HitChecker::~HitChecker()
{

}

void HitChecker::Update(const Player& player)
{
    playerCircle = VAdd(player.GetPos(), VGet(0.0f, PlayerHight, 0.0f));
    playerAttackCircle = VAdd(player.GetPos(), VGet(0.0f, PlayerHight, AttackFront));

}

void HitChecker::circleDraw()
{
    DrawSphere3D(playerCircle, playerRadius, 16, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), false);
    DrawSphere3D(playerAttackCircle, playerRadius, 16, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), false);
}

