#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Pallet.h"
#include"Skydome.h"
#include"Stage.h"
#include"Input.h"
#include"Camera.h"
#include"Enemy.h"
#include"Player.h"
#include"HitChecker.h"
enum STATE
{
	STATE_INIT,
	STATE_TITLE,		// タイトル.
	STATE_READY,        //準備
	STATE_COUNTDOWN,	//ゲームが始まるまでのカウント
	STATE_GAME,			// ゲーム中.
	STATE_END,			//やられている状態
	STATE_GAMEOVER,		// ゲームオーバー.
};

/// <summary>
/// メイン関数
/// </summary>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;	// エラーが起きたら直ちに終了
	}

	// 画面モードのセット
	ChangeWindowMode(TRUE);
	SetGraphMode(800, 600, 16);

	SetDrawScreen(DX_SCREEN_BACK);	// 裏画面を描画対象にする
	SetUseZBufferFlag(TRUE);		// Ｚバッファを使用する
	SetWriteZBufferFlag(TRUE);		// Ｚバッファへの書き込みを行う
	SetUseBackCulling(TRUE);		// バックカリングを行う

	// 1秒間に処理するフレーム数を設定(60FPS)
	const int TARGET_FPS = 60;
	const int FRAME_TIME = 1000 / TARGET_FPS;  // 1フレームあたりの理想的な時間 (ミリ秒)

	// ********** フォントのロード **********
	LPCSTR font_path = "Data/Font/LightNovelPOPv2.otf"; // 読み込むフォントファイルのパス
	//// フォントの変更
	ChangeFont("ラノベPOP v2", DX_CHARSET_DEFAULT);

	// インスタンス生成
	Skydome* dome = new Skydome();
	Stage* stage = new Stage();
	Input* input = new Input();
	Camera* camera = new Camera();
    Enemy* enemy = new Enemy();
	Player* player = new Player();
	HitChecker* hitchecker = new HitChecker();

	// エスケープキーが押されるかウインドウが閉じられるまでループ
	LONGLONG frameTime = 0;

	int gameStatus = STATE_INIT;	//現在のゲーム中の状態
	bool debugPauseFlag = false;
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// フレーム開始時の時間を取得
		int startTime = GetNowCount();
		// ぼたんおしたら
		if (CheckHitKey(KEY_INPUT_P))
		{
			debugPauseFlag = true;
		}
		while (debugPauseFlag)
		{
			WaitTimer(2);
			// ぼたんおしたら
			if (CheckHitKey(KEY_INPUT_O))
			{
				debugPauseFlag = false;
			}
		}

		if (debugPauseFlag == false)
		{
			//全ての初期化
			if (gameStatus == STATE_INIT)
			{
				stage->Load();
				enemy->Load();
				player->Load();
				camera->Load();

				//ゲーム状態変化
				gameStatus = STATE_TITLE;
			}

			//タイトル画面
			if (gameStatus == STATE_TITLE)
			{

				ClearDrawScreen();

				//描画
				SetFontSize(40);
				DrawFormatString(0, 0, Pallet::AliceBlue.GetHandle(), "title");

				// ゲーム状態変化
				if (CheckHitKey(KEY_INPUT_RETURN))
				{

					gameStatus = STATE_READY;
				}

			}
			//チュートリアル画面
			if (gameStatus == STATE_READY)
			{

				//描画

				// ゲーム状態変化
				gameStatus = STATE_COUNTDOWN;
			}
			//ゲームが始まるまでのカウントダウン
			if (gameStatus == STATE_COUNTDOWN)
			{
				gameStatus = STATE_GAME;
			}
			//ゲーム中
			if (gameStatus == STATE_GAME)
			{

				//ゲームシーンの制御

				//パッドの制御
				input->Update();
				// プレイヤー制御
				enemy->Update(*player);
				player->Update(*input);
				// カメラの制御
				camera->Update(*player);
				// スカイドーム制御
				dome->SkydomeUpdate();

				//当たり判定制御
				hitchecker->Update(*player);

				//障害物制御


				//コイン制御


				// 画面を初期化する
				ClearDrawScreen();

				// 描画
				dome->SkydomeDraw();
				stage->Draw();
				enemy->Draw();
				player->Draw();
				hitchecker->circleDraw();

			}
			//ゲームオーバー演出
			if (gameStatus == STATE_END)
			{

				// 画面を初期化する
				ClearDrawScreen();

			}

			//ゲームリザルト
			if (gameStatus == STATE_GAMEOVER)
			{
				// 画面を初期化する
				ClearDrawScreen();
				//描画

				// ゲーム状態変化
				if (CheckHitKey(KEY_INPUT_SPACE))
				{
					ClearDrawScreen();
					WaitTimer(80);
					gameStatus = STATE_INIT;
				}
			}
		}

		// 裏画面の内容を表画面に反映させる
		ScreenFlip();

		// フレーム終了時の時間を取得
		int endTime = GetNowCount();

		// フレーム処理時間を計算
		int elapsedTime = endTime - startTime;

		// 処理が早く終わった場合、残り時間待機する
		if (elapsedTime < FRAME_TIME)
		{
			// 残り時間待機
			WaitTimer(FRAME_TIME - elapsedTime);
		}
	}

	// 後始末
	// ＤＸライブラリの後始末
	DxLib_End();

	// ソフトの終了
	return 0;
}