#pragma once

class EnemyAttackRangeChecker;
class Player;

class Enemy
{
public:

	enum class State :int
	{
		None = -1,			//�Ȃ�
		Die = 0,			//����
		Walk = 1,			//����
		Run = 2,		//��_���[�W
		Idol = 3,	//���_���[�W
		Muscle = 4,			//���@
		TireIdol = 5,			//�����~�܂�
		Smalldmege = 6,			//�}�b�X��
		BigDamage = 7,			//����
		Missile = 8,			//����f��
		Blow = 9,			//��
	};
	enum class AnimKind : int
	{
		None = -1,			//�Ȃ�
		Die = 0,			//����
		Walk = 1,			//����
		Run = 2,		//��_���[�W
		Idol = 3,	//���_���[�W
		Muscle = 4,			//���@
		TireIdol = 5,			//�����~�܂�
		Smalldmege = 6,			//�}�b�X��
		BigDamage = 7,			//����
		Missile = 8,			//����f��
		Blow = 9,			//��
	};

	Enemy();
	~Enemy();
	void Load();									//������
	void InitializeAttack();
	void ChangeTire();
	void TireTimer();
	void Update(const Player& player,const EnemyAttackRangeChecker& attackRange);				//�X�V
	State UpdateEnemyState(const EnemyAttackRangeChecker& attackRange);						//
	void UpdateShadow();							//�e�̍X�V
	void UpdateAngle(const Player& player);			//�����̍X�V
	void UpdateAnimationState(State prevState);		//
	void UpdateAnimation();							//
	void ChangeMotion(AnimKind  motionNum);			//���[�V�����ύX
	void DrawShadow();								//�e�̕`��
	void Draw();									//�e�̕\��
	// ���f���n���h���̎擾.
	const VECTOR& GetPos() const { return position; }
private:
	//�A�j���[�V�����Ɋւ��郁���o�ÓI�萔
	static constexpr float playAnimSpeed = 0.7f;		//�A�j���[�V������i�߂鑬�x
	static constexpr float AnimBlendSpeed = 0.1f;	// �A�j���[�V�����̃u�����h���ω����x
	static constexpr float	MoveSpeed = 0.250f;		// �ړ����x
	static constexpr float Scale = 0.04f;  //�傫��
	static constexpr float	AngleSpeed = 0.6f;		// �p�x�ω����x

	//Enemy���g�Ɋւ��郁���o�ϐ�
	VECTOR position;
	VECTOR angleVector;
	float angle;
	int EnemyHandle;
	int hp;
	//Enemy�̍U���Ɋւ��郁���o�ϐ�
	bool isAttack;
	bool isShortAttack;
	bool isMiddleAttack;
	bool isLongAttack;
	bool tire;
	bool attackReady;
	float tireTimer;

	//�A�j���[�V�����Ɋւ��郁���o�ϐ�
	State currentState;				//���݂̃A�j���[�V�����̏��
	float playTime;					//�A�j���[�V�����̎��Ԃ̍��v
	int PlayAnim;					//���݂̃A�j���[�V�����A�^�b�`�ԍ�
	int AttachIndex;				//�A�j���[�V������t�^�����ϐ�
	float AnimTime;					//�A�j���[�V������i�߂�ϐ�

	int prevPlayAnim;				//�O�̃A�j���[�V�����A�^�b�`�ԍ�
	float prevPlayTime;				//�O�̃A�j���[�V�����̎��Ԃ̍��v
	float animBlendRate;			//�ߋ��ƌ��݂̃A�j���[�V�����̃u�����h��


	//Enemy�[�̉e
	VECTOR shadowToppos;			//�e�̒��_
	VECTOR shadowBottompos;			//�e�̒��
	float ShadowRad;				//�e�̔��a

};

