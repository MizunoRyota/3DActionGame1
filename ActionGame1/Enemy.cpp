#include"DxLib.h"
#include"EffekseerForDXLib.h"

#include"Pallet.h"
#include"Player.h"
#include"Enemy.h"
#include"HitChecker.h"
#include"EnemyAttackRangeChecker.h"

Enemy::Enemy()
    :position(VGet(0.0f,0.0f,10.0f))
    ,angleVector(VGet(0,0,0))
    , shadowBottompos(VGet(0.0f, 0.0f, 0.0f))
    , shadowToppos(VGet(0.0f, 0.0f, 0.0f))
	, currentState(State::Idol)
	, animBlendRate(0.0f)
	, prevPlayAnim(-1)
    , ShadowRad(1.7f)
	,tireTimer(0)
	, prevPlayTime(0)
	,isAttack(false)
	,isShortAttack(false)
	,isMiddleAttack(false)
	,isLongAttack(false)
	,tire(false)
	, playTime(0)
{
    //�����Ȃ�
}

Enemy::~Enemy()
{
    MV1DeleteModel(EnemyHandle);
}

void Enemy::Load()
{
    // ���f���̓ǂݍ���
    EnemyHandle = MV1LoadModel("data/model/Enemy/Enemy.mv1");



    // 3D���f���̃X�P�[������
    MV1SetScale(EnemyHandle, VGet(Scale, Scale, Scale));
    // �v���C���[�̃��f���̍��W���X�V����
    MV1SetPosition(EnemyHandle, position);
}

void Enemy::InitializeAttack()
{
	isAttack = false;
	isShortAttack = false;
	isMiddleAttack = false;
	isLongAttack = false;
}

void Enemy::ChangeTire()
{
	if (isAttack==true)
	{
		tire = true;
	}
	else
	{
		tire = false;
	}
}

void Enemy::TireTimer()
{
	if (tire == true)
	{
		// ����̌Ăяo�����ɊJ�n������ݒ�
		if (tireTimer == 0)
		{
			tireTimer = GetNowCount();  // �~���b�P�ʂŌ��ݎ������擾
		}

		// �o�ߎ��Ԃ�3000�~���b(3�b)�ȏ�o�߂�����t���O��؂�ւ���
		if (GetNowCount() - tireTimer >= 3000)
		{
			tire = false;
			tireTimer = 0;
		}
	}
}

void Enemy::Update(const Player& player, const EnemyAttackRangeChecker& attackRange)
{
    //���̏�Ԃ�O�̏�ԂɕύX
	State prevState = currentState;

	//���Ă����Ԃ̐������ԍX�V����
	TireTimer();
	
	if (CheckHitKey(KEY_INPUT_R))
	{
		clsDx();
		printfDx("xpos%f\n", position.x);
		printfDx("ypos%f\n", position.y);
		printfDx("zpos%f\n", position.z);
		printfDx("currentState%d\n", currentState);
		printfDx("prevState%d\n", prevState);
		printfDx("PlayAnim%d\n", PlayAnim);
		printfDx("isAttack%d\n", isAttack);
		printfDx("isShortAttack%d\n", isShortAttack);
		printfDx("isMiddleAttack%d\n", isMiddleAttack);
		printfDx("isLongAttack%d\n", isLongAttack);

	}
	//���݂̃A�j���[�V�����̏�ԍX�V����
	currentState=UpdateEnemyState(attackRange);
	//�A�j���[�V�����̕ύX
	UpdateAnimationState(prevState);


    //�v���C���[�̕��������N
    UpdateAngle(player);
    //Enemy�̉e�̍X�V
    UpdateShadow();

	//�A�j���[�V�����X�V
	UpdateAnimation();
}

void Enemy::UpdateAngle(const Player& player)
{
	if (!isAttack)
	{
		float Angle;
		// �R�c���f���Q����R�c���f���P�Ɍ������x�N�g�����Z�o
		angleVector = VSub(player.GetPos(), position);

		// atan2 ���g�p���Ċp�x���擾
		Angle = atan2(angleVector.x, angleVector.z);

		// atan2 �Ŏ擾�����p�x�ɂR�c���f���𐳖ʂɌ������邽�߂̕␳�l( DX_PI_F )��
		// �������l���R�c���f���� Y����]�l�Ƃ��Đݒ�
		MV1SetRotationXYZ(EnemyHandle, VGet(0.0f, Angle + DX_PI_F, 0.0f));
	}
}

Enemy::State Enemy::UpdateEnemyState(const EnemyAttackRangeChecker& attackRange)
{

	State nextState = currentState;
	//�����͈͓��ɂ��邩�U�����łȂ������Ă��Ȃ�
	if (attackRange.GetisLongWithin()&&!isAttack && !tire)
	{
		// �������܂Łu�����~�܂�v��Ԃ�������
		if (currentState == State::Idol)
		{
			// ��Ԃ��u����v�ɂ���
			nextState = State::Missile;
		}
	}
	//���������͈͓��ɂ��邩�U�����łȂ������Ă��Ȃ�
	if (attackRange.GetisMiddleWithin() && !isAttack && !tire)
	{
		// �������܂Łu�����~�܂�v��Ԃ�������
		if (currentState == State::Idol)
		{
			// ��Ԃ��u����v�ɂ���
			nextState = State::Muscle;
		}
	}
	//�����͈͓��ɂ��邩�U�����łȂ������Ă��Ȃ�

	if (attackRange.GetisShortWithin() && !isAttack && !tire)
	{
		// �������܂Łu�����~�܂�v��Ԃ�������
		if (currentState == State::Idol)
		{
			// ��Ԃ��u����v�ɂ���
			nextState = State::Blow;
		}
	}
	//�U�����̎��ɑҋ@��Ԃɂ���
	if (isAttack)
	{
			nextState = State::Idol;
	}
	// ���Ă���A�j���[�V��������ԃt���O�����Ă��Ȃ����ҋ@��Ԃɂ���
	if (currentState == State::TireIdol&&!tire)
	{
		// ��Ԃ��u�ҋ@�v�ɂ���
		nextState = State::Idol;
	}
	//��ԃt���O�����Ă���Ƃ���Ԃ�tireIdol�ɂ���
	if (tire)
	{
		nextState = State::TireIdol;
	}

	return nextState;

}

void Enemy::ChangeMotion(AnimKind motionNum)
{
	// ����ւ����s���̂ŁA�P�O�̃��[�V���������L����������f�^�b�`����
	if (prevPlayAnim != -1)
	{
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(EnemyHandle, prevPlayAnim);
		prevPlayAnim = -1;
	}
	// ���܂ōĐ����̃��[�V�������������̂̏���Prev�Ɉړ�����
	prevPlayAnim = PlayAnim;
	prevPlayTime = playTime;

	//�V�����A�^�b�`�ԍ���ۑ�
	PlayAnim = MV1AttachAnim(EnemyHandle, static_cast<int>(motionNum));

	// �Đ����Ԃ̏�����
	playTime = 0;

	// �u�����h����Prev���L���ł͂Ȃ��ꍇ�͂P�D�O��( ���݃��[�V�������P�O�O���̏�� )�ɂ���
	animBlendRate = prevPlayAnim == -1 ? 1.0f : 0.0f;

}

void Enemy::UpdateAnimation()
{

	{
		// �Đ����Ă���A�j���[�V�����̑�����
		float animTotalTime;

		// �u�����h�����P�ȉ��̏ꍇ�͂P�ɋ߂Â���
		if (animBlendRate < 1.0f)
		{
			animBlendRate += AnimBlendSpeed;
			if (animBlendRate > 1.0f)
			{
				animBlendRate = 1.0f;
			}
		}

		//�Đ����Ă���A�j���[�V�����̏����P
		if (PlayAnim != -1)
		{
			// �A�j���[�V�����̑����Ԃ��擾
			animTotalTime = MV1GetAttachAnimTotalTime(EnemyHandle, PlayAnim);

			//�A�j���[�V������i�߂�
			playTime += playAnimSpeed;

			// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
			if (playTime >= animTotalTime)
			{
				ChangeTire();
				InitializeAttack();
				playTime = static_cast<float>(fmod(playTime, animTotalTime));
			}

			// �ύX�����Đ����Ԃ����f���ɔ��f������
			MV1SetAttachAnimTime(EnemyHandle, PlayAnim, playTime);
			// �A�j���[�V�����P�̃��f���ɑ΂��锽�f�����Z�b�g
			MV1SetAttachAnimBlendRate(EnemyHandle, PlayAnim, animBlendRate);
		}
		// �Đ����Ă���A�j���[�V�����Q�̏���
		if (prevPlayAnim != -1)
		{
			// �A�j���[�V�����̑����Ԃ��擾
			animTotalTime = MV1GetAttachAnimTotalTime(EnemyHandle, prevPlayAnim);

			// �Đ����Ԃ�i�߂�
			prevPlayTime += playAnimSpeed;

			// �Đ����Ԃ������Ԃɓ��B���Ă�����Đ����Ԃ����[�v������
			if (prevPlayTime > animTotalTime)
			{
				prevPlayTime = static_cast<float>(fmod(prevPlayTime, animTotalTime));
			}

			// �ύX�����Đ����Ԃ����f���ɔ��f������
			MV1SetAttachAnimTime(EnemyHandle, prevPlayAnim, prevPlayTime);

			// �A�j���[�V�����Q�̃��f���ɑ΂��锽�f�����Z�b�g
			MV1SetAttachAnimBlendRate(EnemyHandle, prevPlayAnim, 1.0f - animBlendRate);
		}
	}
}

/// <summary>
/// �A�j���[�V�����̍X�V����
/// </summary>
void Enemy::UpdateAnimationState(State prevState)
{
	if (prevState == State::Idol && currentState == State::Missile)
	{
		isAttack = true;
		isLongAttack = true;
		ChangeMotion(AnimKind::Missile);
	}
	if (prevState == State::Idol && currentState == State::Muscle)
	{
		isAttack = true;
		isMiddleAttack = true;
		ChangeMotion(AnimKind::Muscle);
	}
	if (prevState == State::Idol && currentState==State::Blow)
	{
		isAttack = true;
		isShortAttack = true;
		ChangeMotion(AnimKind::Blow);
	}
	// �����~�܂肩�瑖��ɕς������
	if (prevState == State::Idol && currentState == State::Run)
	{
		// ����A�j���[�V�������Đ�����
		ChangeMotion(AnimKind::Run);
	}
	// ���肩�痧���~�܂�ɕς������
	if (prevState == State::Run && currentState == State::Idol)
	{
		// �����~��A�j���[�V�������Đ�����
		ChangeMotion(AnimKind::Idol);
	}

	if (prevState == State::Idol&&currentState==State::TireIdol)
	{
		ChangeMotion(AnimKind::TireIdol);
	}
}

void Enemy::UpdateShadow()
{
    shadowToppos = VGet(position.x, -0.1f, position.z);
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