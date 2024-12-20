#pragma once

class EnemyAttackRangeChecker;
class Player;

class Enemy
{
public:

	enum class State :int
	{
		None = -1,			//なし
		Return = 0,			//反復
		Charge = 1,			//タックル準備
		JumpAttack = 2,		//ジャンプアタック
		spinAttack = 3,		//回転攻撃
		Walk = 4,			//歩き
		Run = 5,			//走り
		Idol = 6,			//待機
		Muscle = 7,			//マッスル
		TireIdol = 8,		//つかれている
		Smalldmege = 9,		//小ダメージ
		BigDamage = 10,		//大ダメージ
		Missile = 11,		//ミサイル発射
		Blow = 12,			//殴る
		Die = 13,			//死
	};
	enum class AnimKind : int
	{
		None = -1,			//なし
		Return = 0,			//反復
		Charge = 1,			//タックル準備
		JumpAttack = 2,		//ジャンプアタック
		spinAttack = 3,		//回転攻撃
		Walk = 4,			//歩き
		Run = 5,			//走り
		Idol = 6,			//待機
		Muscle = 7,			//マッスル
		TireIdol = 8,		//つかれている
		Smalldmege = 9,		//小ダメージ
		BigDamage = 10,		//大ダメージ
		Missile = 11,		//ミサイル発射
		Blow = 12,			//殴る
		Die = 13,			//死
	};

	Enemy();
	~Enemy();
	void Load();									//初期化
	void InitializeAttack();
	void ChangeTire();
	void LimitRange();
	void TireTimer();
	void Update(const Player& player,const EnemyAttackRangeChecker& attackRange);				//更新
	State UpdateEnemyState(const EnemyAttackRangeChecker& attackRange);						//
	void UpdateShadow();							//影の更新
	void UpdateAngle(const Player& player);			//向きの更新
	void UpdateAnimationState(State prevState);		//
	void UpdateAnimation();							//
	void RushAttack(const Player& player, const EnemyAttackRangeChecker& attackRange);

	void UpdateAttack(const Player& player);
	void ChangeMotion(AnimKind  motionNum);			//モーション変更
	void DrawShadow();								//影の描画
	void Draw();									//影の表示
	// モデルハンドルの取得.
	const VECTOR& GetPos() const { return position; }
	const bool& GetisAttack() const { return isAttack; }

private:
	//アニメーションに関するメンバ静的定数
	static constexpr float playAnimSpeed = 0.7f;		//アニメーションを進める速度
	static constexpr float AnimBlendSpeed = 0.1f;	// アニメーションのブレンド率変化速度
	static constexpr float	MoveSpeed = 0.30f;		// 移動速度
	static constexpr float Scale = 0.04f;  //大きさ
	static constexpr float	AngleSpeed = 0.6f;		// 角度変化速度

	//Enemy自身に関するメンバ変数
	VECTOR position;					//
	VECTOR angleVector;					//
	float returnRange;					//最大移動距離
	bool limitRange;
	float angle;						//
	int EnemyHandle;					//
	int hp;								//
	//Enemyの攻撃に関するメンバ変数
	VECTOR targetMoveDirection;			// モデルが向くべき方向のベクトル
	bool isAttack;						//
	bool isShortAttack;					//
	bool isMiddleAttack;				//
	bool isLongAttack;					//
	bool tire;							//
	bool attackReady;					//	
	bool isChasing;						//
	float tireTimer;					//
	//アニメーションに関するメンバ変数
	State currentState;				//現在のアニメーションの状態
	float playTime;					//アニメーションの時間の合計
	int PlayAnim;					//現在のアニメーションアタッチ番号
	int AttachIndex;				//アニメーションを付与される変数
	float AnimTime;					//アニメーションを進める変数

	int prevPlayAnim;				//前のアニメーションアタッチ番号
	float prevPlayTime;				//前のアニメーションの時間の合計
	float animBlendRate;			//過去と現在のアニメーションのブレンド率

	//Enemyーの影
	VECTOR shadowToppos;			//影の頂点
	VECTOR shadowBottompos;			//影の底辺
	float ShadowRad;				//影の半径

};