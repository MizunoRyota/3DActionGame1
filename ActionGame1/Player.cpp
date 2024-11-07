#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Pallet.h"
#include"Player.h"

const float Player::Scale = 0.006f;		// �X�P�[��

Player::Player()
	:position(VGet(0.0f, 0.0f, 0.0f))
	, shadowBottompos(VGet(0.0f, 0.0f, 0.0f))
	, shadowToppos(VGet(0.0f, 0.0f, 0.0f))
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
	ChangeMotion(AnimKind::SecondAttack);
	
	// �Đ����Ԃ̏�����
	playTime = 0.0f;
	
	// 3D���f���̃X�P�[������
	MV1SetScale(PlayerHandle, VGet(Scale, Scale, Scale));
	
	// �R�c���f����Y���̉�]�l���X�O�x�ɃZ�b�g����
	MV1SetRotationXYZ(PlayerHandle, VGet(0.0f, 180.0f * DX_PI_F / 180.0f, 0.0f));
}

/// <summary>
/// �A�j���[�V�����̕ύX
/// </summary>
/// <param name="motionNum"></param>
void Player::ChangeMotion(AnimKind motionNum)
{

	MV1DetachAnim(PlayerHandle, AttachIndex);
	// �Đ����Ԃ̏�����
	playTime = 0;
	// �Đ����Ԃ��Z�b�g����
	MV1SetAttachAnimTime(PlayerHandle, AttachIndex, playTime);

	this->PlayAnim = static_cast<int>(motionNum);

	// �R�c���f���̂O�Ԗڂ̃A�j���[�V�������A�^�b�`����
	AttachIndex = MV1AttachAnim(PlayerHandle, this->PlayAnim, -1, FALSE);
	// �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
	playTime = MV1GetAttachAnimTotalTime(PlayerHandle, AttachIndex);
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
/// <summary>
/// �X�V
/// </summary>
void Player::Update()
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
	VECTOR MoveVec;			// ���̃t���[���̈ړ��x�N�g��
	State prevState = currentState;


	//�A�j���[�V��������
	UpdateAnimation();

	//�e�̍X�V
	UpdateShadow();

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