#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"math.h"
#include"Pallet.h"
#include"Player.h"
#include"Input.h"

Player::Player()
	:position(VGet(0.0f, 0.0f, 0.0f))
	, shadowBottompos(VGet(0.0f, 0.0f, 0.0f))
	, shadowToppos(VGet(0.0f, 0.0f, 0.0f))
	, returnRange(30.0f)
	, PlayerHandle(-1)
	, angle(0.0f)

	,isAttack(false)
	,isFirstAttack(false)
	,isSecondAttack(false)
	,isThirdAttack(false)
	, currentState(State::Stand)
	//, currentAttack(AttackAnimKind::UnKown)
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
	MV1SetRotationXYZ(PlayerHandle, VGet(0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f));
}
/// <summary>
/// 更新
/// </summary>
void Player::Update(const Input& input)
{

	// パッド入力によって移動パラメータを設定する
	VECTOR moveVec;			// このフレームの移動ベクトル
	State prevState = currentState;
	//AttackAnimKind atttackAnim=currentAttack;
	// ゲーム状態変化

     	currentState = UpdateMoveParameterWithPad(input, moveVec);

	// ぼたんおしたら
	if (CheckHitKey(KEY_INPUT_G))
	{
		clsDx();
		printfDx("xpos%f\n", position.x);
		printfDx("ypos%f\n", position.y);
		printfDx("zpos%f\n", position.z);
		printfDx("currentState%d\n", currentState);
		printfDx("prevState%d\n",prevState);
		printfDx("PlayAnim%d\n", PlayAnim);
		printfDx("currentAttack%d\n", currentAttack);
		printfDx("isAttack%d\n", isAttack);
	}
	// アニメーションステートの更新
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
 		UpdateAttack();
		UpdateAttackState(prevState);
		//currentAttack=UpdateAnimationAttack(atttackAnim);	//プレイヤーの行動アニメーションの更新
	}
	else
	{
		UpdateAnimationState(prevState);
	}

	LimitRange();

	//プレイヤーが向く角度の更新
	UpdateAngle();

	//ポジションの更新
	Move(moveVec);

	//影の更新
	UpdateShadow();

	//アニメーション処理
	UpdateAnimation();
}

void Player::LimitRange()
{
	////中心からプレイヤーの距離を測る

	float r = VSize(VSub(position, VGet(0, 0, 0)));

	////一定の距離に達したらそれ以上いけないようにする

	if (r >= returnRange || r <= -returnRange)

	{

		//中心座標からプレイヤー座標の距離

		VECTOR distance = VSub(VGet(0, 0, 0), position);

		//正規化

		distance = VNorm(distance);

		//戻す量を計算、加算する

		VECTOR returnPosition = VScale(distance, (r - returnRange));

		position = VAdd(position, returnPosition);

	}
}

void Player::UpdateAttack()
{
	if (!isFirstAttack)
	{
		currentState = State::FirstAttack;
	}
	else if (!isSecondAttack)
	{
		currentState = State::SecondAttack;
	}
	else if(isFirstAttack&& isSecondAttack)
	{
		currentState = State::LastAttack;
	}

}

//void Player::ChangeAttackMotion(AttackAnimKind prevAnimKind)
//{
//	// 入れ替えを行うので、１つ前のモーションがが有効だったらデタッチする
//	if (prevPlayAnim != -1)
//	{
//		isAttack = false;
//		//アニメーションのデタッチ
//		MV1DetachAnim(PlayerHandle, prevPlayAnim);
//		prevPlayAnim = -1;
//	}
//	// 今まで再生中のモーションだったものの情報をPrevに移動する
//	prevPlayAnim = PlayAnim;
//	prevPlayTime = playTime;
//
//	//新しいアタッチ番号を保存
//	PlayAnim = MV1AttachAnim(PlayerHandle, static_cast<int>(prevAnimKind));
//
//	// 再生時間の初期化
//	playTime = 0;
//
//	// ブレンド率はPrevが有効ではない場合は１．０ｆ( 現在モーションが１００％の状態 )にする
//	animBlendRate = prevPlayAnim == -1 ? 1.0f : 0.0f;
//}

//Player::AttackAnimKind Player::UpdateAnimationAttack(AttackAnimKind prevAnimKind)
//{	 
//	AttackAnimKind nextAttack=prevAnimKind;
//
//	// 立ち止まりから攻撃に変わったら
//	if (prevAnimKind == AttackAnimKind::UnKown && currentState == State::Stand&&!isAttack)
//	{
//		// 初撃アニメーションを再生する
//		ChangeAttackMotion(AttackAnimKind::FirstAttack);
//		nextAttack = AttackAnimKind::FirstAttack;
//		isAttack = true;
//	}
//	if (prevAnimKind == AttackAnimKind::FirstAttack && currentState == State::Stand&&!isAttack)
//	{
//		// 2撃目アニメーションを再生する
//		ChangeAttackMotion(AttackAnimKind::SecondAttack);
//		nextAttack = AttackAnimKind::SecondAttack;
//		isAttack = true;
//
//	}
//	if (prevAnimKind == AttackAnimKind::SecondAttack && currentState == State::Stand&&!isAttack)
//	{
//		// 3撃目アニメーションを再生する
//		ChangeAttackMotion(AttackAnimKind::LastAttack);
//		nextAttack = AttackAnimKind::UnKown;
//		isAttack = true;
//	}
//
//	return nextAttack;
//
//}

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
			isAttack=false;
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

		//
		isAttack = false;
		isFirstAttack = false;
		isSecondAttack = false;
	}
	else if (input.GetNowFrameInput() & PAD_INPUT_RIGHT)
	{
		// 移動ベクトルに「←」が入力された時の移動ベクトルを加算する
		moveVec = VAdd(moveVec, VGet(1, 0, 0));

		// 移動したかどうかのフラグを「移動した」にする
		isMoveStick = true;

		//
		isAttack = false;
		isFirstAttack = false;
		isSecondAttack = false;
	}
	if (input.GetNowFrameInput() & PAD_INPUT_UP)
	{
		// 移動ベクトルに「←」が入力された時の移動ベクトルを加算する
		moveVec = VAdd(moveVec, VGet(0, 0, 1));

		// 移動したかどうかのフラグを「移動した」にする
		isMoveStick = true;

		isAttack = false;
		isFirstAttack = false;
		isSecondAttack = false;

	}
	else if (input.GetNowFrameInput() & PAD_INPUT_DOWN)
	{
		// 移動ベクトルに「←」が入力された時の移動ベクトルを加算する
		moveVec = VAdd(moveVec, VGet(0, 0, -1));

		// 移動したかどうかのフラグを「移動した」にする
		isMoveStick = true;


		isAttack = false;
		isFirstAttack = false;
		isSecondAttack = false;
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
 		else if (currentState == State::FirstAttack|| currentState == State::SecondAttack|| currentState == State::LastAttack && !isAttack)
		{
			// 状態を「立ち止り」にする
			nextState = State::Stand;
		}
	}

	return nextState;

}

/// <summary>
/// 角度の更新処理
/// </summary>
void Player::UpdateAngle()
{
	// プレイヤーの移動方向にモデルの方向を近づける
	float targetAngle;			// 目標角度
	float difference;			// 目標角度と現在の角度との差

	// 目標の方向ベクトルから角度値を算出する
	targetAngle = static_cast<float>(atan2(targetMoveDirection.x, targetMoveDirection.z));

	// 目標の角度と現在の角度との差を割り出す
	// 最初は単純に引き算
	difference = targetAngle - angle;

	// ある方向からある方向の差が１８０度以上になることは無いので
	// 差の値が１８０度以上になっていたら修正する
	if (difference < -DX_PI_F)
	{
		difference += DX_TWO_PI_F;
	}
	else if (difference > DX_PI_F)
	{
		difference -= DX_TWO_PI_F;
	}

	// 角度の差が０に近づける
	if (difference > 0.0f)
	{
		// 差がプラスの場合は引く
		difference -= AngleSpeed;
		if (difference < 0.0f)
		{
			difference = 0.0f;
		}
	}
	else
	{
		// 差がマイナスの場合は足す
		difference += AngleSpeed;
		if (difference > 0.0f)
		{
			difference = 0.0f;
		}
	}

	// モデルの角度を更新
	angle = targetAngle - difference;
	MV1SetRotationXYZ(PlayerHandle, VGet(0.0f, angle + DX_PI_F, 0.0f));
}


/// <summary>
/// アニメーションの更新処理
/// </summary>
void Player::UpdateAnimationState(State prevState)
{
	// 立ち止まりから走りに変わったら
	if (prevState == State::Stand && currentState == State::Run)
	{
		// 走りアニメーションを再生する
		ChangeMotion(AnimKind::Run);
	}
	// 走りから立ち止まりに変わったら
	if (prevState == State::Run && currentState == State::Stand)
	{
		// 立ち止りアニメーションを再生する
		ChangeMotion(AnimKind::Idol);
	}
	else if (currentState == State::FirstAttack || currentState == State::SecondAttack || currentState == State::LastAttack && currentState == State::Stand && !isAttack)
	{
		// 立ち止りアニメーションを再生する
		ChangeMotion(AnimKind::Idol);
	}
}

 void Player::UpdateAttackState(State prevState)
 {
	 // 立ち止まりから走りに変わったら
	 if (prevState == State::Stand && currentState == State::FirstAttack&&!isFirstAttack&&!isAttack)
	 {
		 // 走りアニメーションを再生する
  		 ChangeMotion(AnimKind::FirstAttack);
		 isFirstAttack = true;
		 isAttack = true;
	 }
	 else if (prevState == State::Stand && currentState == State::SecondAttack && !isSecondAttack&&isFirstAttack && !isAttack)
	 {
		 // 走りアニメーションを再生する
		 ChangeMotion(AnimKind::SecondAttack);
		 isSecondAttack = true;
		 isAttack = true;
	 }
	 else if (prevState == State::Stand && currentState == State::LastAttack && isFirstAttack&&isSecondAttack && !isAttack)
	 {
		 // 走りアニメーションを再生する
		 ChangeMotion(AnimKind::LastAttack);
		 isFirstAttack = false;
		 isSecondAttack = false;
		 isAttack = true;
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
