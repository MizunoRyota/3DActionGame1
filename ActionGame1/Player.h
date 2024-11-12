#pragma once

class Input;

class Player
{
public:
	// ���
	enum class State : int
	{
		Stand = 0,		// �����~�܂�
		Run = 1,		// ����
	};
	enum class AnimKind : int
	{
		None = -1,		// �Ȃ�
		Unkown = 0,	// �s��
		FinishAttack = 1,		// ����
		FirstAttack = 2,		// �����~�܂�
		SecondAttack = 3,		// �W�����v
		LastAttack = 4,			// ������
		Squat = 5,				//���Ⴊ��
		Roll = 6,				//���[�����O
		Idol = 7,				//�����~�܂�
		Run = 8,				//����
		TakeDamage=9,			//�_���[�W���󂯂�
	};
	Player();
	~Player();

	void Load();	//������
	void Update(const Input& input);  //�X�V
	State UpdateMoveParameterWithPad(const Input& input, VECTOR& moveVec);//�p�b�h�̓��͍X�V
	void Move( VECTOR& moveVec);
	void Draw();	//�`��

	void UpdateShadow();	//�v���C���[�̉e
	void DrawShadow();

	// ���f���n���h���̎擾.
	const VECTOR& GetPos() const { return position; }

private:
	// �ÓI�萔.
	//�v���C���[���g�Ɋւ��郁���o�ÓI�萔
	static constexpr float Scale=0.006f;		//�傫��
	//�A�j���[�V�����Ɋւ��郁���o�ÓI�萔
	static constexpr float playAnimSpeed=0.5f;		//�A�j���[�V������i�߂鑬�x
	static constexpr float AnimBlendSpeed = 0.1f;	// �A�j���[�V�����̃u�����h���ω����x
	static constexpr float	MoveSpeed = 0.250f;		// �ړ����x

	//�v���C���[���g�Ɋւ��郁���o�ϐ�
	VECTOR	velocity;					// �ړ���.
	VECTOR position;					// �|�W�V����.
	VECTOR Dir;							// ��]����.
	VECTOR targetMoveDirection;			// ���f���������ׂ������̃x�N�g��
	int PlayerHandle;					// �v���C���[�̃��f���n���h��

	//�A�j���[�V�����Ɋւ��郁���o�ϐ�
	State currentState;			//���݂̃A�j���[�V�����̏��
	float playTime;				//�A�j���[�V�����̎��Ԃ̍��v
	int PlayAnim;				//���݂̃A�j���[�V�����A�^�b�`�ԍ�
	int AttachIndex;			//�A�j���[�V������t�^�����ϐ�
	float AnimTime;				//�A�j���[�V������i�߂�ϐ�

	int prevPlayAnim;			//�O�̃A�j���[�V�����A�^�b�`�ԍ�
	float prevPlayTime;			//�O�̃A�j���[�V�����̎��Ԃ̍��v
	
	float animBlendRate;		//�ߋ��ƌ��݂̃A�j���[�V�����̃u�����h��

	//�v���C���[�̉e
	VECTOR shadowToppos;		//�e�̒��_
	VECTOR shadowBottompos;		//�e�̒��
	float ShadowRad;			//�e�̔��a

	void ChangeMotion(AnimKind  motionNum);					//���[�V�����ύX
	void UpdateAnimation();									//Player�̃A�j���[�V�����X�V
	void UpdateAnimationState(State prevState);				// �A�j���[�V�����X�e�[�g�̍X�V
	void UpdateAnimationAnimKind(AnimKind prevAnimKind);	//�v���C���[�̍s���A�j���[�V�����̍X�V


};