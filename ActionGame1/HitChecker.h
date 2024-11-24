#pragma once

class Player;

class HitChecker
{
public:
	HitChecker();
	~HitChecker();
	void Update(const Player& playerPos);

	void circleDraw();								//�����蔻��̋��`��
private:
	//�v���C���[�̓����蔻��ϐ�
	VECTOR playerCircle;							//�v���C���[�̓����蔻��̃|�W�V����
	float playerRadius;								//�v���C���[�̓����蔻��̔��a
	static constexpr  float PlayerHight=0.8f;
	//�v���C���[�̍U���̓����蔻��
	VECTOR playerAttackCircle;						//�v���C���[�̓����蔻��̃|�W�V����
	float playerAttackRadius;						//�v���C���[�̓����蔻��̔��a
	static constexpr float AttackFront = 0.8f;

};

