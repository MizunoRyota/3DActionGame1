#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Pallet.h"
#include"Player.h"
#include"Enemy.h"

Enemy::Enemy()
    :position(VGet(0.0f,0.0f,0.0f))
    ,angleVector(VGet(0,0,0))
    , shadowBottompos(VGet(0.0f, 0.0f, 0.0f))
    , shadowToppos(VGet(0.0f, 0.0f, 0.0f))
	, currentState(State::Run)
	, animBlendRate(0.0f)
	, prevPlayAnim(-1)
    , ShadowRad(1.7f)
	, prevPlayTime(0)
	,isAttack(false)
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

void Enemy::Update(const Player& player)
{
    //
	State prevState = currentState;

	currentState=UpdateEnemyState();

	UpdateAnimationState(prevState);

    //�v���C���[�̕��������N
    UpdateAngle(player);
    //Enemy�̉e�̍X�V
    UpdateShadow();

	//
	UpdateAnimation();
}

void Enemy::UpdateAngle(const Player& player)
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


Enemy::State Enemy::UpdateEnemyState()
{

    State nextState=currentState;

	bool isMoveStick = false;


	// �ړ��{�^���������ꂽ���ǂ����ŏ����𕪊�
	if (isMoveStick)
	{

		// �������܂Łu�����~�܂�v��Ԃ�������
		if (currentState == State::Idol)
		{
			// ��Ԃ��u����v�ɂ���
			nextState = State::Run;
		}

	}
	else
	{
		// ���̃t���[���ňړ����Ă��Ȃ��āA����Ԃ��u����v��������
		if (currentState == State::Run)
		{
			// ��Ԃ��u�����~��v�ɂ���
			nextState = State::Idol;
		}

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