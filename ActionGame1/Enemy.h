#pragma once

class Player;

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
	State UpdateAttackEnemy(const Player& player);  //
	void UpdateShadow();							//影の更新
	void UpdateAngle(const Player& player);			//向きの更新
	void DrawShadow();								//影の描画
	void Draw();									//影の表示

private:
	//アニメーションに関するメンバ静的定数
	static constexpr float playAnimSpeed = 0.7f;		//アニメーションを進める速度
	static constexpr float AnimBlendSpeed = 0.1f;	// アニメーションのブレンド率変化速度
	static constexpr float	MoveSpeed = 0.250f;		// 移動速度

	static constexpr float Scale = 0.04f;  //大きさ
	//Enemy自身に関するメンバ変数
	int EnemyHandle;
	VECTOR position;
	VECTOR angleVector;

	//Enemyーの影
	VECTOR shadowToppos;			//影の頂点
	VECTOR shadowBottompos;			//影の底辺
	float ShadowRad;				//影の半径

};

