#pragma once

class Player;

class Enemy
{
public:

	enum class State :int
	{
		None = -1,			//�Ȃ�
		Walk = 0,			//����
		Run = 1,			//����
		BigDamage = 2,		//��_���[�W
		SmallDamage = 3,	//���_���[�W
		Magic = 4,			//���@
		Idol = 5,			//�����~�܂�
		Muscle = 6,			//�}�b�X��
		Blow = 7,			//����
		Breath = 8,			//����f��
		Die = 9,			//��
	};
	enum class AnimKind : int
	{
		None = -1,			//�Ȃ�
		Walk = 0,			//����
		Run = 1,			//����
		BigDamage = 2,		//��_���[�W
		SmallDamage = 3,	//���_���[�W
		Magic = 4,			//���@
		Idol = 5,			//�����~�܂�
		Muscle = 6,			//�}�b�X��
		Blow = 7,			//����
		Breath = 8,			//����f��
		Die = 9,			//��
	};


	Enemy();
	~Enemy();
	void Load();									//������
	void Update(const Player& player);				//�X�V
	State UpdateAttackEnemy(const Player& player);  //
	void UpdateShadow();							//�e�̍X�V
	void UpdateAngle(const Player& player);			//�����̍X�V
	void DrawShadow();								//�e�̕`��
	void Draw();									//�e�̕\��

private:
	//�A�j���[�V�����Ɋւ��郁���o�ÓI�萔
	static constexpr float playAnimSpeed = 0.7f;		//�A�j���[�V������i�߂鑬�x
	static constexpr float AnimBlendSpeed = 0.1f;	// �A�j���[�V�����̃u�����h���ω����x
	static constexpr float	MoveSpeed = 0.250f;		// �ړ����x

	static constexpr float Scale = 0.04f;  //�傫��
	//Enemy���g�Ɋւ��郁���o�ϐ�
	int EnemyHandle;
	VECTOR position;
	VECTOR angleVector;

	//Enemy�[�̉e
	VECTOR shadowToppos;			//�e�̒��_
	VECTOR shadowBottompos;			//�e�̒��
	float ShadowRad;				//�e�̔��a

};

