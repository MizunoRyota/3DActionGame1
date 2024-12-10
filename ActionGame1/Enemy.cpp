#include"DxLib.h"
#include"EffekseerForDXLib.h"

#include"Pallet.h"
#include"Player.h"
#include"Enemy.h"
#include"HitChecker.h"
#include"EnemyAttackRangeChecker.h"

Enemy::Enemy()
    :position(VGet(0.0f,0.0f,10.0f))
    ,angleVector(VGet(0,0,0))
    , shadowBottompos(VGet(0.0f, 0.0f, 0.0f))
    , shadowToppos(VGet(0.0f, 0.0f, 0.0f))
	, currentState(State::Idol)
	, animBlendRate(0.0f)
	, prevPlayAnim(-1)
    , ShadowRad(1.7f)
	,tireTimer(0)
	, prevPlayTime(0)
	,isAttack(false)
	,isShortAttack(false)
	,isMiddleAttack(false)
	,isLongAttack(false)
	,tire(false)
	, playTime(0)
{
    //処理なし
}

Enemy::~Enemy()
{
    MV1DeleteModel(EnemyHandle);
}

void Enemy::Load()
{
    // モデルの読み込み
    EnemyHandle = MV1LoadModel("data/model/Enemy/Enemy.mv1");



    // 3Dモデルのスケール決定
    MV1SetScale(EnemyHandle, VGet(Scale, Scale, Scale));
    // プレイヤーのモデルの座標を更新する
    MV1SetPosition(EnemyHandle, position);
}

void Enemy::InitializeAttack()
{
	isAttack = false;
	isShortAttack = false;
	isMiddleAttack = false;
	isLongAttack = false;
}

void Enemy::ChangeTire()
{
	if (isAttack==true)
	{
		tire = true;
	}
	else
	{
		tire = false;
	}
}

void Enemy::TireTimer()
{
	if (tire == true)
	{
		// 初回の呼び出し時に開始時刻を設定
		if (tireTimer == 0)
		{
			tireTimer = GetNowCount();  // ミリ秒単位で現在時刻を取得
		}

		// 経過時間が3000ミリ秒(3秒)以上経過したらフラグを切り替える
		if (GetNowCount() - tireTimer >= 3000)
		{
			tire = false;
			tireTimer = 0;
		}
	}
}

void Enemy::Update(const Player& player, const EnemyAttackRangeChecker& attackRange)
{
    //今の状態を前の状態に変更
	State prevState = currentState;

	//疲れている状態の制限時間更新処理
	TireTimer();
	
	if (CheckHitKey(KEY_INPUT_R))
	{
		clsDx();
		printfDx("xpos%f\n", position.x);
		printfDx("ypos%f\n", position.y);
		printfDx("zpos%f\n", position.z);
		printfDx("currentState%d\n", currentState);
		printfDx("prevState%d\n", prevState);
		printfDx("PlayAnim%d\n", PlayAnim);
		printfDx("isAttack%d\n", isAttack);
		printfDx("isShortAttack%d\n", isShortAttack);
		printfDx("isMiddleAttack%d\n", isMiddleAttack);
		printfDx("isLongAttack%d\n", isLongAttack);

	}
	//現在のアニメーションの状態更新処理
	currentState=UpdateEnemyState(attackRange);
	//アニメーションの変更
	UpdateAnimationState(prevState);


    //プレイヤーの方向をムク
    UpdateAngle(player);
    //Enemyの影の更新
    UpdateShadow();

	//アニメーション更新
	UpdateAnimation();
}

void Enemy::UpdateAngle(const Player& player)
{
	if (!isAttack)
	{
		float Angle;
		// ３Ｄモデル２から３Ｄモデル１に向かうベクトルを算出
		angleVector = VSub(player.GetPos(), position);

		// atan2 を使用して角度を取得
		Angle = atan2(angleVector.x, angleVector.z);

		// atan2 で取得した角度に３Ｄモデルを正面に向かせるための補正値( DX_PI_F )を
		// 足した値を３Ｄモデルの Y軸回転値として設定
		MV1SetRotationXYZ(EnemyHandle, VGet(0.0f, Angle + DX_PI_F, 0.0f));
	}
}

Enemy::State Enemy::UpdateEnemyState(const EnemyAttackRangeChecker& attackRange)
{

	State nextState = currentState;
	//狭い範囲内にいるかつ攻撃中でないかつ疲れていない
	if (attackRange.GetisLongWithin()&&!isAttack && !tire)
	{
		// もし今まで「立ち止まり」状態だったら
		if (currentState == State::Idol)
		{
			// 状態を「走り」にする
			nextState = State::Missile;
		}
	}
	//少し遠い範囲内にいるかつ攻撃中でないかつ疲れていない
	if (attackRange.GetisMiddleWithin() && !isAttack && !tire)
	{
		// もし今まで「立ち止まり」状態だったら
		if (currentState == State::Idol)
		{
			// 状態を「走り」にする
			nextState = State::Muscle;
		}
	}
	//遠い範囲内にいるかつ攻撃中でないかつ疲れていない

	if (attackRange.GetisShortWithin() && !isAttack && !tire)
	{
		// もし今まで「立ち止まり」状態だったら
		if (currentState == State::Idol)
		{
			// 状態を「走り」にする
			nextState = State::Blow;
		}
	}
	//攻撃中の時に待機状態にする
	if (isAttack)
	{
			nextState = State::Idol;
	}
	// 疲れているアニメーションかつ状態フラグが疲れていない時待機状態にする
	if (currentState == State::TireIdol&&!tire)
	{
		// 状態を「待機」にする
		nextState = State::Idol;
	}
	//状態フラグが疲れているとき状態をtireIdolにする
	if (tire)
	{
		nextState = State::TireIdol;
	}

	return nextState;

}

void Enemy::ChangeMotion(AnimKind motionNum)
{
	// 入れ替えを行うので、１つ前のモーションがが有効だったらデタッチする
	if (prevPlayAnim != -1)
	{
		//アニメーションのデタッチ
		MV1DetachAnim(EnemyHandle, prevPlayAnim);
		prevPlayAnim = -1;
	}
	// 今まで再生中のモーションだったものの情報をPrevに移動する
	prevPlayAnim = PlayAnim;
	prevPlayTime = playTime;

	//新しいアタッチ番号を保存
	PlayAnim = MV1AttachAnim(EnemyHandle, static_cast<int>(motionNum));

	// 再生時間の初期化
	playTime = 0;

	// ブレンド率はPrevが有効ではない場合は１．０ｆ( 現在モーションが１００％の状態 )にする
	animBlendRate = prevPlayAnim == -1 ? 1.0f : 0.0f;

}

void Enemy::UpdateAnimation()
{

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
			animTotalTime = MV1GetAttachAnimTotalTime(EnemyHandle, PlayAnim);

			//アニメーションを進める
			playTime += playAnimSpeed;

			// 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
			if (playTime >= animTotalTime)
			{
				ChangeTire();
				InitializeAttack();
				playTime = static_cast<float>(fmod(playTime, animTotalTime));
			}

			// 変更した再生時間をモデルに反映させる
			MV1SetAttachAnimTime(EnemyHandle, PlayAnim, playTime);
			// アニメーション１のモデルに対する反映率をセット
			MV1SetAttachAnimBlendRate(EnemyHandle, PlayAnim, animBlendRate);
		}
		// 再生しているアニメーション２の処理
		if (prevPlayAnim != -1)
		{
			// アニメーションの総時間を取得
			animTotalTime = MV1GetAttachAnimTotalTime(EnemyHandle, prevPlayAnim);

			// 再生時間を進める
			prevPlayTime += playAnimSpeed;

			// 再生時間が総時間に到達していたら再生時間をループさせる
			if (prevPlayTime > animTotalTime)
			{
				prevPlayTime = static_cast<float>(fmod(prevPlayTime, animTotalTime));
			}

			// 変更した再生時間をモデルに反映させる
			MV1SetAttachAnimTime(EnemyHandle, prevPlayAnim, prevPlayTime);

			// アニメーション２のモデルに対する反映率をセット
			MV1SetAttachAnimBlendRate(EnemyHandle, prevPlayAnim, 1.0f - animBlendRate);
		}
	}
}

/// <summary>
/// アニメーションの更新処理
/// </summary>
void Enemy::UpdateAnimationState(State prevState)
{
	if (prevState == State::Idol && currentState == State::Missile)
	{
		isAttack = true;
		isLongAttack = true;
		ChangeMotion(AnimKind::Missile);
	}
	if (prevState == State::Idol && currentState == State::Muscle)
	{
		isAttack = true;
		isMiddleAttack = true;
		ChangeMotion(AnimKind::Muscle);
	}
	if (prevState == State::Idol && currentState==State::Blow)
	{
		isAttack = true;
		isShortAttack = true;
		ChangeMotion(AnimKind::Blow);
	}
	// 立ち止まりから走りに変わったら
	if (prevState == State::Idol && currentState == State::Run)
	{
		// 走りアニメーションを再生する
		ChangeMotion(AnimKind::Run);
	}
	// 走りから立ち止まりに変わったら
	if (prevState == State::Run && currentState == State::Idol)
	{
		// 立ち止りアニメーションを再生する
		ChangeMotion(AnimKind::Idol);
	}

	if (prevState == State::Idol&&currentState==State::TireIdol)
	{
		ChangeMotion(AnimKind::TireIdol);
	}
}

void Enemy::UpdateShadow()
{
    shadowToppos = VGet(position.x, -0.1f, position.z);
    shadowBottompos = VGet(position.x, position.y, position.z);
}

void Enemy::DrawShadow()
{
    DrawCone3D(shadowToppos, shadowBottompos, ShadowRad, 8, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), TRUE);
}

void Enemy::Draw()
{

    DrawShadow();
    MV1DrawModel(EnemyHandle);
}