#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Camera.h"
#include"Player.h"
#include"Skydome.h"
enum STATE
{
	STATE_INIT,
	STATE_TITLE,		// �^�C�g��.
	STATE_READY,        //����
	STATE_COUNTDOWN,	//�Q�[�����n�܂�܂ł̃J�E���g
	STATE_GAME,			// �Q�[����.
	STATE_END,			//����Ă�����
	STATE_GAMEOVER,		// �Q�[���I�[�o�[.
};

/// <summary>
/// ���C���֐�
/// </summary>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return -1;	// �G���[���N�����璼���ɏI��
	}

	// ��ʃ��[�h�̃Z�b�g
	ChangeWindowMode(TRUE);
	SetGraphMode(1600, 900, 16);

	SetDrawScreen(DX_SCREEN_BACK);	// ����ʂ�`��Ώۂɂ���
	SetUseZBufferFlag(TRUE);		// �y�o�b�t�@���g�p����
	SetWriteZBufferFlag(TRUE);		// �y�o�b�t�@�ւ̏������݂��s��
	SetUseBackCulling(TRUE);		// �o�b�N�J�����O���s��

	// 1�b�Ԃɏ�������t���[������ݒ�(60FPS)
	const int TARGET_FPS = 60;
	const int FRAME_TIME = 1000 / TARGET_FPS;  // 1�t���[��������̗��z�I�Ȏ��� (�~���b)

	// ********** �t�H���g�̃��[�h **********
	LPCSTR font_path = "Data/Font/LightNovelPOPv2.otf"; // �ǂݍ��ރt�H���g�t�@�C���̃p�X
	//// �t�H���g�̕ύX
	ChangeFont("���m�xPOP v2", DX_CHARSET_DEFAULT);

	// �C���X�^���X����
	Player* player = new Player();
	Camera* camera = new Camera();
	Skydome* dome = new Skydome();
	// �G�X�P�[�v�L�[��������邩�E�C���h�E��������܂Ń��[�v
	LONGLONG frameTime = 0;

	int gameStatus = STATE_INIT;	//���݂̃Q�[�����̏��
	bool debugPauseFlag = false;
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		printfDx("%d\n", gameStatus);
		// �t���[���J�n���̎��Ԃ��擾
		int startTime = GetNowCount();
		// �ڂ��񂨂�����
		if (CheckHitKey(KEY_INPUT_P))
		{
			debugPauseFlag = true;
		}
		while (debugPauseFlag)
		{
			WaitTimer(2);
			// �ڂ��񂨂�����
			if (CheckHitKey(KEY_INPUT_O))
			{
				debugPauseFlag = false;
			}
		}

		if (debugPauseFlag == false)
		{
			//�S�Ă̏�����
			if (gameStatus == STATE_INIT)
			{
				player->Load();
				camera->Load();


				//�Q�[����ԕω�
				gameStatus = STATE_TITLE;
			}

			//�^�C�g�����
			if (gameStatus == STATE_TITLE)
			{

				ClearDrawScreen();

				//�`��


				// �Q�[����ԕω�
				if (CheckHitKey(KEY_INPUT_SPACE))
				{

					gameStatus = STATE_READY;
				}
			}
			//�`���[�g���A�����
			if (gameStatus == STATE_READY)
			{

				//�`��

				// �Q�[����ԕω�
				gameStatus = STATE_COUNTDOWN;
			}
			//�Q�[�����n�܂�܂ł̃J�E���g�_�E��
			if (gameStatus == STATE_COUNTDOWN)
			{
				gameStatus = STATE_GAME;
			}
			//�Q�[����
			if (gameStatus == STATE_GAME)
			{

				//�Q�[���V�[���̐���


				// �v���C���[����
				player->Update();
				// �J�����̐���
				camera->Update(*player);
				// �X�J�C�h�[������
				dome->SkydomeUpdate();

				//�X�e�[�W����


				//��Q������


				//�R�C������


				// ��ʂ�����������
				ClearDrawScreen();

				// �`��
				dome->SkydomeDraw();
				player->Draw();
				

			}
			//�Q�[���I�[�o�[���o
			if (gameStatus == STATE_END)
			{

				// ��ʂ�����������
				ClearDrawScreen();

			}

			//�Q�[�����U���g
			if (gameStatus == STATE_GAMEOVER)
			{

				// ��ʂ�����������
				ClearDrawScreen();
				//�`��

				// �Q�[����ԕω�
				if (CheckHitKey(KEY_INPUT_SPACE))
				{
					ClearDrawScreen();
					WaitTimer(80);
					gameStatus = STATE_INIT;
				}
			}
		}
		// ����ʂ̓��e��\��ʂɔ��f������
		ScreenFlip();

		// �t���[���I�����̎��Ԃ��擾
		int endTime = GetNowCount();

		// �t���[���������Ԃ��v�Z
		int elapsedTime = endTime - startTime;

		// �����������I������ꍇ�A�c�莞�ԑҋ@����
		if (elapsedTime < FRAME_TIME)
		{
			// �c�莞�ԑҋ@
			WaitTimer(FRAME_TIME - elapsedTime);
		}
	}

	// ��n��
	// �c�w���C�u�����̌�n��
	DxLib_End();

	// �\�t�g�̏I��
	return 0;
}