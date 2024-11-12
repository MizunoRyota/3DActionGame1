#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Pallet.h"
#include"Player.h"
#include"Input.h"


Player::Player()
	:position(VGet(0.0f, 0.0f, 0.0f))
	, shadowBottompos(VGet(0.0f, 0.0f, 0.0f))
	, shadowToppos(VGet(0.0f, 0.0f, 0.0f))
	,PlayerHandle(-1)
	,currentState(State::Stand)
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
	ChangeMotion(AnimKind::Idol);
	
	// 再生時間の初期化
	playTime = 0.0f;
	
	// ３ＤモデルのY軸の回転値を９０度にセットする
	MV1SetRotationXYZ(PlayerHandle, VGet(0.0f, 180.0f * DX_PI_F / 180.0f, 0.0f));
}
/// <summary>
/// 更新
/// </summary>
void Player::Update(const Input& input)
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
	VECTOR moveVec;			// このフレームの移動ベクトル
	State prevState = currentState;

	currentState = UpdateMoveParameterWithPad(input, moveVec);

	// ぼたんおしたら
	if (CheckHitKey(KEY_INPUT_G))
	{
		//printfDx("%f\n", position.x);
		//printfDx("%f\n", position.y);
		//printfDx("%f\n", position.z);
		printfDx("%d",prevState);
		printfDx("%d\n", currentState);
	}
	// アニメーションステートの更新
	UpdateAnimationState(prevState);

	//影の更新
	UpdateShadow();

	//ポジションの更新
	Move(moveVec);

	//アニメーション処理
	UpdateAnimation();


}
/// <summary>
/// アニメーションの変更
/// </summary>
/// <param name="motionNum"></param>
void Player::ChangeMotion(AnimKind motionNum)
{
	// 入れ替えを行うので、１つ前のモーションがが有効だったらデタッチする
	if (prevPlayAnim != -1)
	{
		//アニメーションのデタッチ
		MV1DetachAnim(PlayerHandle, prevPlayAnim);
		prevPlayAnim = -1;
	}
	// 今まで再生中のモーションだったものの情報をPrevに移動する
	prevPlayAnim = PlayAnim;
	prevPlayTime = playTime;

	//新しいアタッチ番号を保存
	PlayAnim = MV1AttachAnim(PlayerHandle, static_cast<int>(motionNum));

	// 再生時間の初期化
	playTime = 0;

	// ブレンド率はPrevが有効ではない場合は１．０ｆ( 現在モーションが１００％の状態 )にする
	animBlendRate = prevPlayAnim == -1 ? 1.0f : 0.0f;

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

		// 変更した再生時間をモデルに反映させる
		MV1SetAttachAnimTime(PlayerHandle, PlayAnim, playTime);
		// アニメーション１のモデルに対する反映率をセット
		MV1SetAttachAnimBlendRate(PlayerHandle, PlayAnim, animBlendRate);
	}
	// 再生しているアニメーション２の処理
	if (prevPlayAnim != -1)
	{
		// アニメーションの総時間を取得
		animTotalTime = MV1GetAttachAnimTotalTime(PlayerHandle, prevPlayAnim);

		// 再生時間を進める
		prevPlayTime += playAnimSpeed;

		// 再生時間が総時間に到達していたら再生時間をループさせる
		if (prevPlayTime > animTotalTime)
		{
			prevPlayTime = static_cast<float>(fmod(prevPlayTime, animTotalTime));
		}

		// 変更した再生時間をモデルに反映させる
		MV1SetAttachAnimTime(PlayerHandle, prevPlayAnim, prevPlayTime);

		// アニメーション２のモデルに対する反映率をセット
		MV1SetAttachAnimBlendRate(PlayerHandle, prevPlayAnim, 1.0f - animBlendRate);
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


Player::State Player::UpdateMoveParameterWithPad(const Input& input, VECTOR& moveVec)
{
	State nextState = currentState;

	// このフレームでの移動ベクトルを初期化
	moveVec = VGet(0.0f, 0.0f, 0.0f);

	// 移動したかどうかのフラグを初期状態では「移動していない」を表すFALSEにする
	bool isMoveStick = false;

	// 方向ボタン「←」が入力されたらカメラの見ている方向から見て左方向に移動する
	if (input.GetNowFrameInput() & PAD_INPUT_LEFT)
	{
		// 移動ベクトルに「←」が入力された時の移動ベクトルを加算する
		moveVec = VAdd(moveVec, VGet(-1, 0, 0));

		// 移動したかどうかのフラグを「移動した」にする
		isMoveStick = true;
	}
	else if (input.GetNowFrameInput() & PAD_INPUT_RIGHT)
	{
		// 移動ベクトルに「←」が入力された時の移動ベクトルを加算する
		moveVec = VAdd(moveVec, VGet(1, 0, 0));

		// 移動したかどうかのフラグを「移動した」にする
		isMoveStick = true;
	}
	else if (input.GetNowFrameInput() & PAD_INPUT_UP)
	{
		// 移動ベクトルに「←」が入力された時の移動ベクトルを加算する
		moveVec = VAdd(moveVec, VGet(0, 0, 1));

		// 移動したかどうかのフラグを「移動した」にする
		isMoveStick = true;
	}
	else if (input.GetNowFrameInput() & PAD_INPUT_DOWN)
	{
		// 移動ベクトルに「←」が入力された時の移動ベクトルを加算する
		moveVec = VAdd(moveVec, VGet(0, 0, -1));

		// 移動したかどうかのフラグを「移動した」にする
		isMoveStick = true;
	}

	// 移動ボタンが押されたかどうかで処理を分岐
	if (isMoveStick)
	{
		// もし今まで「立ち止まり」状態だったら
		if (currentState == State::Stand)
		{
			// 状態を「走り」にする
			nextState = State::Run;
		}

		// 移動ベクトルを正規化したものをプレイヤーが向くべき方向として保存
		targetMoveDirection = VNorm(moveVec);

		// プレイヤーが向くべき方向ベクトルをプレイヤーのスピード倍したものを移動ベクトルとする
		moveVec = VScale(targetMoveDirection, MoveSpeed);

	}
	else
	{
		// このフレームで移動していなくて、且つ状態が「走り」だったら
		if (currentState == State::Run)
		{
			// 状態を「立ち止り」にする
			nextState = State::Stand;
		}
	}

	return nextState;

}

 void Player::UpdateAnimationState(State prevState)
 {
	 // 立ち止まりから走りに変わったら
	 if (prevState == State::Stand && currentState == State::Run)
	 {
		 // 走りアニメーションを再生する
		 ChangeMotion(AnimKind::Run);
	 }
	 // 走りから立ち止まりに変わったら
	 else if (prevState == State::Run && currentState == State::Stand)
	 {
		 // 立ち止りアニメーションを再生する
		 ChangeMotion(AnimKind::Idol);
	 }

 }

 void Player::Move( VECTOR& moveVec)
 {

	 position = VAdd(position, moveVec);

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