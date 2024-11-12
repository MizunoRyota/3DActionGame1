#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Pallet.h"
#include"Player.h"
#include"Input.h"


Player::Player()
	:position(VGet(0.0f, 0.0f, 0.0f))
	, shadowBottompos(VGet(0.0f, 0.0f, 0.0f))
	, shadowToppos(VGet(0.0f, 0.0f, 0.0f))
	,PlayerHandle(-1)
	,currentState(State::Stand)
	, ShadowRad(0.3f)
	, playTime(0)
	, prevPlayAnim(-1)
	, prevPlayTime(0)
	, animBlendRate(0.0f)
{
	// �����Ȃ�
}

Player::~Player()
{
	// �����Ȃ�
}

void Player::Load()
{
	// ���f���̓ǂݍ���
	PlayerHandle = MV1LoadModel("data/model/Player/Player.mv1");

	//�l�̏�����
	position = VGet(0.0f, 0.0f, 0.0f);

	// �A�j���[�V�����̃u�����h����������
	animBlendRate = 1.0f;

	// 3D���f���̃X�P�[������
	MV1SetScale(PlayerHandle, VGet(Scale, Scale, Scale));
	
	//���[�V�����̕ύX
	ChangeMotion(AnimKind::Idol);
	
	// �Đ����Ԃ̏�����
	playTime = 0.0f;
	
	// �R�c���f����Y���̉�]�l���X�O�x�ɃZ�b�g����
	MV1SetRotationXYZ(PlayerHandle, VGet(0.0f, 180.0f * DX_PI_F / 180.0f, 0.0f));
}
/// <summary>
/// �X�V
/// </summary>
void Player::Update(const Input& input)
{

	// �Q�[����ԕω�
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		//���[�V�����̕ύX
		ChangeMotion(AnimKind::LastAttack);
	}
	if (CheckHitKey(KEY_INPUT_W))
	{
		//���[�V�����̕ύX
		ChangeMotion(AnimKind::FirstAttack);
	}	
	if (CheckHitKey(KEY_INPUT_R))
	{
		//���[�V�����̕ύX
		ChangeMotion(AnimKind::SecondAttack);
	}
	// �p�b�h���͂ɂ���Ĉړ��p�����[�^��ݒ肷��
	VECTOR moveVec;			// ���̃t���[���̈ړ��x�N�g��
	State prevState = currentState;

	currentState = UpdateMoveParameterWithPad(input, moveVec);

	// �ڂ��񂨂�����
	if (CheckHitKey(KEY_INPUT_G))
	{
		//printfDx("%f\n", position.x);
		//printfDx("%f\n", position.y);
		//printfDx("%f\n", position.z);
		printfDx("%d",prevState);
		printfDx("%d\n", currentState);
	}
	// �A�j���[�V�����X�e�[�g�̍X�V
	UpdateAnimationState(prevState);

	//�e�̍X�V
	UpdateShadow();

	//�|�W�V�����̍X�V
	Move(moveVec);

	//�A�j���[�V��������
	UpdateAnimation();


}
/// <summary>
/// �A�j���[�V�����̕ύX
/// </summary>
/// <param name="motionNum"></param>
void Player::ChangeMotion(AnimKind motionNum)
{
	// ����ւ����s���̂ŁA�P�O�̃��[�V���������L����������f�^�b�`����
	if (prevPlayAnim != -1)
	{
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(PlayerHandle, prevPlayAnim);
		prevPlayAnim = -1;
	}
	// ���܂ōĐ����̃��[�V�������������̂̏���Prev�Ɉړ�����
	prevPlayAnim = PlayAnim;
	prevPlayTime = playTime;

	//�V�����A�^�b�`�ԍ���ۑ�
	PlayAnim = MV1AttachAnim(PlayerHandle, static_cast<int>(motionNum));

	// �Đ����Ԃ̏�����
	playTime = 0;

	// �u�����h����Prev���L���ł͂Ȃ��ꍇ�͂P�D�O��( ���݃��[�V�������P�O�O���̏�� )�ɂ���
	animBlendRate = prevPlayAnim == -1 ? 1.0f : 0.0f;

}

/// <summary>
/// �A�j���[�V�����̍X�V����
/// </summary>
void Player::UpdateAnimation()
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
		animTotalTime= MV1GetAttachAnimTotalTime(PlayerHandle, PlayAnim);

		//�A�j���[�V������i�߂�
		playTime += playAnimSpeed;

		// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
		if (playTime >= animTotalTime)
		{
			playTime = static_cast<float>(fmod(playTime, animTotalTime));
		}

		// �ύX�����Đ����Ԃ����f���ɔ��f������
		MV1SetAttachAnimTime(PlayerHandle, PlayAnim, playTime);
		// �A�j���[�V�����P�̃��f���ɑ΂��锽�f�����Z�b�g
		MV1SetAttachAnimBlendRate(PlayerHandle, PlayAnim, animBlendRate);
	}
	// �Đ����Ă���A�j���[�V�����Q�̏���
	if (prevPlayAnim != -1)
	{
		// �A�j���[�V�����̑����Ԃ��擾
		animTotalTime = MV1GetAttachAnimTotalTime(PlayerHandle, prevPlayAnim);

		// �Đ����Ԃ�i�߂�
		prevPlayTime += playAnimSpeed;

		// �Đ����Ԃ������Ԃɓ��B���Ă�����Đ����Ԃ����[�v������
		if (prevPlayTime > animTotalTime)
		{
			prevPlayTime = static_cast<float>(fmod(prevPlayTime, animTotalTime));
		}

		// �ύX�����Đ����Ԃ����f���ɔ��f������
		MV1SetAttachAnimTime(PlayerHandle, prevPlayAnim, prevPlayTime);

		// �A�j���[�V�����Q�̃��f���ɑ΂��锽�f�����Z�b�g
		MV1SetAttachAnimBlendRate(PlayerHandle, prevPlayAnim, 1.0f - animBlendRate);
	}
}

/// <summary>
/// �e�̍X�V����
/// </summary>
void Player::UpdateShadow()
{
	shadowToppos = VGet(position.x, -0.1, position.z);
	shadowBottompos = VGet(position.x, position.y, position.z);
}


Player::State Player::UpdateMoveParameterWithPad(const Input& input, VECTOR& moveVec)
{
	State nextState = currentState;

	// ���̃t���[���ł̈ړ��x�N�g����������
	moveVec = VGet(0.0f, 0.0f, 0.0f);

	// �ړ��������ǂ����̃t���O��������Ԃł́u�ړ����Ă��Ȃ��v��\��FALSE�ɂ���
	bool isMoveStick = false;

	// �����{�^���u���v�����͂��ꂽ��J�����̌��Ă���������猩�č������Ɉړ�����
	if (input.GetNowFrameInput() & PAD_INPUT_LEFT)
	{
		// �ړ��x�N�g���Ɂu���v�����͂��ꂽ���̈ړ��x�N�g�������Z����
		moveVec = VAdd(moveVec, VGet(-1, 0, 0));

		// �ړ��������ǂ����̃t���O���u�ړ������v�ɂ���
		isMoveStick = true;
	}
	else if (input.GetNowFrameInput() & PAD_INPUT_RIGHT)
	{
		// �ړ��x�N�g���Ɂu���v�����͂��ꂽ���̈ړ��x�N�g�������Z����
		moveVec = VAdd(moveVec, VGet(1, 0, 0));

		// �ړ��������ǂ����̃t���O���u�ړ������v�ɂ���
		isMoveStick = true;
	}
	else if (input.GetNowFrameInput() & PAD_INPUT_UP)
	{
		// �ړ��x�N�g���Ɂu���v�����͂��ꂽ���̈ړ��x�N�g�������Z����
		moveVec = VAdd(moveVec, VGet(0, 0, 1));

		// �ړ��������ǂ����̃t���O���u�ړ������v�ɂ���
		isMoveStick = true;
	}
	else if (input.GetNowFrameInput() & PAD_INPUT_DOWN)
	{
		// �ړ��x�N�g���Ɂu���v�����͂��ꂽ���̈ړ��x�N�g�������Z����
		moveVec = VAdd(moveVec, VGet(0, 0, -1));

		// �ړ��������ǂ����̃t���O���u�ړ������v�ɂ���
		isMoveStick = true;
	}

	// �ړ��{�^���������ꂽ���ǂ����ŏ����𕪊�
	if (isMoveStick)
	{
		// �������܂Łu�����~�܂�v��Ԃ�������
		if (currentState == State::Stand)
		{
			// ��Ԃ��u����v�ɂ���
			nextState = State::Run;
		}

		// �ړ��x�N�g���𐳋K���������̂��v���C���[�������ׂ������Ƃ��ĕۑ�
		targetMoveDirection = VNorm(moveVec);

		// �v���C���[�������ׂ������x�N�g�����v���C���[�̃X�s�[�h�{�������̂��ړ��x�N�g���Ƃ���
		moveVec = VScale(targetMoveDirection, MoveSpeed);

	}
	else
	{
		// ���̃t���[���ňړ����Ă��Ȃ��āA����Ԃ��u����v��������
		if (currentState == State::Run)
		{
			// ��Ԃ��u�����~��v�ɂ���
			nextState = State::Stand;
		}
	}

	return nextState;

}

 void Player::UpdateAnimationState(State prevState)
 {
	 // �����~�܂肩�瑖��ɕς������
	 if (prevState == State::Stand && currentState == State::Run)
	 {
		 // ����A�j���[�V�������Đ�����
		 ChangeMotion(AnimKind::Run);
	 }
	 // ���肩�痧���~�܂�ɕς������
	 else if (prevState == State::Run && currentState == State::Stand)
	 {
		 // �����~��A�j���[�V�������Đ�����
		 ChangeMotion(AnimKind::Idol);
	 }

 }

 void Player::Move( VECTOR& moveVec)
 {

	 position = VAdd(position, moveVec);

	 // �v���C���[�̃��f���̍��W���X�V����
	 MV1SetPosition(PlayerHandle, position);
 }

/// <summary>
/// �e�̕`��
/// </summary>
void Player::DrawShadow()
{
	DrawCone3D(shadowToppos, shadowBottompos, ShadowRad, 8, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), TRUE);
}

/// <summary>
/// �`��
/// </summary>
void Player::Draw()
{
	//�`��
	DrawShadow();
	MV1DrawModel(PlayerHandle);
}