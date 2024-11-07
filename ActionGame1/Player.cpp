#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Pallet.h"
#include"Player.h"

const float Player::Scale = 0.006f;		// スケール

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
	// 処理なし
}

Player::~Player()
{
	// 処理なし
}

void Player::Load()
{
	// モデルの読み込み
	PlayerHandle = MV1LoadModel("data/model/Player/Player.mv1");

	//値の初期化
	position = VGet(0.0f, 0.0f, 0.0f);

	// アニメーションのブレンド率を初期化
	animBlendRate = 1.0f;

	// 3Dモデルのスケール決定
	MV1SetScale(PlayerHandle, VGet(Scale, Scale, Scale));
	
	//モーションの変更
	ChangeMotion(AnimKind::SecondAttack);
	
	// 再生時間の初期化
	playTime = 0.0f;
	
	// 3Dモデルのスケール決定
	MV1SetScale(PlayerHandle, VGet(Scale, Scale, Scale));
	
	// ３ＤモデルのY軸の回転値を９０度にセットする
	MV1SetRotationXYZ(PlayerHandle, VGet(0.0f, 180.0f * DX_PI_F / 180.0f, 0.0f));
}

/// <summary>
/// アニメーションの変更
/// </summary>
/// <param name="motionNum"></param>
void Player::ChangeMotion(AnimKind motionNum)
{

	MV1DetachAnim(PlayerHandle, AttachIndex);
	// 再生時間の初期化
	playTime = 0;
	// 再生時間をセットする
	MV1SetAttachAnimTime(PlayerHandle, AttachIndex, playTime);

	this->PlayAnim = static_cast<int>(motionNum);

	// ３Ｄモデルの０番目のアニメーションをアタッチする
	AttachIndex = MV1AttachAnim(PlayerHandle, this->PlayAnim, -1, FALSE);
	// アタッチしたアニメーションの総再生時間を取得する
	playTime = MV1GetAttachAnimTotalTime(PlayerHandle, AttachIndex);
}


/// <summary>
/// アニメーションの更新処理
/// </summary>
void Player::UpdateAnimation()
{
	// 再生しているアニメーションの総時間
	float animTotalTime;

	// ブレンド率が１以下の場合は１に近づける
	if (animBlendRate < 1.0f)
	{
		animBlendRate += AnimBlendSpeed;
		if (animBlendRate > 1.0f)
		{
			animBlendRate = 1.0f;
		}
	}

	//再生しているアニメーションの処理１
	if (PlayAnim != -1)
	{
		// アニメーションの総時間を取得
		animTotalTime= MV1GetAttachAnimTotalTime(PlayerHandle, PlayAnim);

		//アニメーションを進める
		playTime += playAnimSpeed;

		// 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
		if (playTime >= animTotalTime)
		{
			playTime = static_cast<float>(fmod(playTime, animTotalTime));
		}



	}



}

/// <summary>
/// 影の更新処理
/// </summary>
void Player::UpdateShadow()
{
	shadowToppos = VGet(position.x, -0.1, position.z);
	shadowBottompos = VGet(position.x, position.y, position.z);
}
/// <summary>
/// 更新
/// </summary>
void Player::Update()
{

	// ゲーム状態変化
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		//モーションの変更
		ChangeMotion(AnimKind::LastAttack);
	}
	if (CheckHitKey(KEY_INPUT_W))
	{
		//モーションの変更
		ChangeMotion(AnimKind::FirstAttack);
	}	
	if (CheckHitKey(KEY_INPUT_R))
	{
		//モーションの変更
		ChangeMotion(AnimKind::SecondAttack);
	}
	// パッド入力によって移動パラメータを設定する
	VECTOR MoveVec;			// このフレームの移動ベクトル
	State prevState = currentState;


	//アニメーション処理
	UpdateAnimation();

	//影の更新
	UpdateShadow();

	// プレイヤーのモデルの座標を更新する
	MV1SetPosition(PlayerHandle, position);
}

/// <summary>
/// 影の描画
/// </summary>
void Player::DrawShadow()
{
	DrawCone3D(shadowToppos, shadowBottompos, ShadowRad, 8, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), TRUE);
}

/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{
	//描画
	DrawShadow();
	MV1DrawModel(PlayerHandle);
}