#pragma once

class Player;
class EnemyAttackRangeChaecker;

class Enemy
{
public:

	enum class State :int
	{
		None = -1,			//なし
		Walk = 0,			//歩き
		Run = 1,			//走り
		BigDamage = 2,		//大ダメージ
		SmallDamage = 3,	//小ダメージ
		Magic = 4,			//魔法
		Idol = 5,			//立ち止まり
		Muscle = 6,			//マッスル
		Blow = 7,			//殴り
		Breath = 8,			//息を吐く
		Die = 9,			//死
	};
	enum class AnimKind : int
	{
		None = -1,			//なし
		Walk = 0,			//歩き
		Run = 1,			//走り
		BigDamage = 2,		//大ダメージ
		SmallDamage = 3,	//小ダメージ
		Magic = 4,			//魔法
		Idol = 5,			//立ち止まり
		Muscle = 6,			//マッスル
		Blow = 7,			//殴り
		Breath = 8,			//息を吐く
		Die = 9,			//死
	};

	Enemy();
	~Enemy();
	void Load();									//初期化
	void Update(const Player& player);				//更新
	State UpdateEnemyState();						//

	void UpdateShadow();							//影の更新
	void UpdateAngle(const Player& player);			//向きの更新
	void UpdateAnimationState(State prevState);		//
	void UpdateAnimation();							//
	void ChangeMotion(AnimKind  motionNum);			//モーション変更
	void DrawShadow();								//影の描画
	void Draw();									//影の表示
	// モデルハンドルの取得.
	const VECTOR& GetPos() const { return position; }
private:
	//アニメーションに関するメンバ静的定数
	static constexpr float playAnimSpeed = 0.7f;		//アニメーションを進める速度
	static constexpr float AnimBlendSpeed = 0.1f;	// アニメーションのブレンド率変化速度
	static constexpr float	MoveSpeed = 0.250f;		// 移動速度
	static constexpr float Scale = 0.04f;  //大きさ

	//Enemy自身に関するメンバ変数
	VECTOR position;
	VECTOR angleVector;
	int EnemyHandle;

	//Enemyの攻撃に関するメンバ変数
	bool isAttack;
	bool attackReady;

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

