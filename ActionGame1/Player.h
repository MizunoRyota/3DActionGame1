#pragma once

class Player
{
public:
	// 状態
	enum class State : int
	{
		Stand = 0,		// 立ち止まり
		Run = 1,		// 走り
		Jump = 2,		// ジャンプ
	};
	enum class AnimKind : int
	{
		None = -1,		// なし
		Unknown = 0,	// 不明
		Run = 1,		// 走り
		FirstAttack = 2,		// 立ち止まり
		LastAttack = 3,		// ジャンプ
		SecondAttack = 4,		// 落下中
	};
	Player();
	~Player();

	void Load();	//初期化
	void Update();  //更新
	void Draw();	//描画

	void UpdateShadow();	//プレイヤーの影
	void DrawShadow();

	// モデルハンドルの取得.
	const VECTOR& GetPos() const { return position; }

private:
	//プレイヤー自身に関するメンバ変数
	VECTOR	velocity;					// 移動力.
	VECTOR position;						// ポジション.
	VECTOR	Dir;						// 回転方向.
	int PlayerHandle;					// プレイヤーのモデルハンドル

	//アニメーションに関するメンバ変数
	static constexpr float playAnimSpeed=0.7f;		//アニメーションを進める速度
	static constexpr float AnimBlendSpeed = 0.1f;		// アニメーションのブレンド率変化速度
	
	State currentState;			//現在のアニメーションの状態
	float playTime;				//アニメーションの時間の合計
	int PlayAnim;				//現在のアニメーションアタッチ番号
	int AttachIndex;			//アニメーションを付与される変数
	float AnimTime;				//アニメーションを進める変数

	int prevPlayAnim;			//前のアニメーションアタッチ番号
	float prevPlayTime;			//前のアニメーションの総時間
	
	float animBlendRate;		//過去と現在のアニメーションのブレンド率
	//プレイヤーの影
	VECTOR shadowToppos;		//影の頂点
	VECTOR shadowBottompos;		//影の底辺
	float ShadowRad;			//影の半径

	void ChangeMotion(AnimKind  motionNum);	//モーション変更
	void UpdateAnimation();				//Playerのアニメーション更新
	void UpdateAnimationState(State prevState);	// アニメーションステートの更新
	// 静的定数.
	static const float Scale;		//大きさ

};