#pragma once

class Player
{
public:
	// ���
	enum class State : int
	{
		Stand = 0,		// �����~�܂�
		Run = 1,		// ����
		Jump = 2,		// �W�����v
	};
	enum class AnimKind : int
	{
		None = -1,		// �Ȃ�
		Unknown = 0,	// �s��
		Run = 1,		// ����
		FirstAttack = 2,		// �����~�܂�
		LastAttack = 3,		// �W�����v
		SecondAttack = 4,		// ������
	};
	Player();
	~Player();

	void Load();	//������
	void Update();  //�X�V
	void Draw();	//�`��

	void UpdateShadow();	//�v���C���[�̉e
	void DrawShadow();

	// ���f���n���h���̎擾.
	const VECTOR& GetPos() const { return position; }

private:
	//�v���C���[���g�Ɋւ��郁���o�ϐ�
	VECTOR	velocity;					// �ړ���.
	VECTOR position;						// �|�W�V����.
	VECTOR	Dir;						// ��]����.
	int PlayerHandle;					// �v���C���[�̃��f���n���h��

	//�A�j���[�V�����Ɋւ��郁���o�ϐ�
	static constexpr float playAnimSpeed=0.7f;		//�A�j���[�V������i�߂鑬�x
	static constexpr float AnimBlendSpeed = 0.1f;		// �A�j���[�V�����̃u�����h���ω����x
	
	State currentState;			//���݂̃A�j���[�V�����̏��
	float playTime;				//�A�j���[�V�����̎��Ԃ̍��v
	int PlayAnim;				//���݂̃A�j���[�V�����A�^�b�`�ԍ�
	int AttachIndex;			//�A�j���[�V������t�^�����ϐ�
	float AnimTime;				//�A�j���[�V������i�߂�ϐ�

	int prevPlayAnim;			//�O�̃A�j���[�V�����A�^�b�`�ԍ�
	float prevPlayTime;			//�O�̃A�j���[�V�����̑�����
	
	float animBlendRate;		//�ߋ��ƌ��݂̃A�j���[�V�����̃u�����h��
	//�v���C���[�̉e
	VECTOR shadowToppos;		//�e�̒��_
	VECTOR shadowBottompos;		//�e�̒��
	float ShadowRad;			//�e�̔��a

	void ChangeMotion(AnimKind  motionNum);	//���[�V�����ύX
	void UpdateAnimation();				//Player�̃A�j���[�V�����X�V
	void UpdateAnimationState(State prevState);	// �A�j���[�V�����X�e�[�g�̍X�V
	// �ÓI�萔.
	static const float Scale;		//�傫��

};