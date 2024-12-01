#pragma once

class Player;
class Enemy;

class HitChecker 
{
public:
	HitChecker();
	virtual~HitChecker();
	 virtual void Update(const Player& playerPos,const Enemy& enemypos) ;		// �X�V
	 virtual bool CheckHit(const Player& playerPos, const Enemy& enemypos);		//�����蔻��`�F�b�N
	virtual void DrawCircle();													//�����蔻��̋��`��
protected:
	static constexpr  float PlayerHight=0.8f;		//�v���C���[�̍���
	bool isHit;

	//�v���C���[�̓����蔻��ϐ�
	VECTOR playerCircle;				//�v���C���[�̓����蔻��̃|�W�V����
	float playerRadius;					//�v���C���[�̓����蔻��̔��a

	//Enemy�̓����蔻��
	VECTOR enemyCircle;					//Enemy�̓����蔻��̃|�W�V����
	float enemyRadius;					//Enemy�̓����蔻��̔��a

	VECTOR keepDistance;				//������ێ�����ϐ�
	float Distance;						//����
	float Length;						//�v���C���[�̉~��Enemy�̉~�̔��a�̍��v

};

