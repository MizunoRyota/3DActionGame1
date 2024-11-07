#pragma once

class Player;

/// <summary>
/// カメラ
/// </summary>
class Camera
{
public:
	Camera();			// コンストラクタ.
	~Camera();			// デストラクタ.
	void Load();		//初期化
	void GameTitle(const VECTOR& mappos);//ゲームタイトル
	void ReadyUpdate(const VECTOR& playerpos);//チュートリアル画面
	void Update(const Player& playerpos);	// 更新.
	void GameEnd(const VECTOR& planepos);//ゲームオーバー画面準備

	// ポジションのgetter/setter.
	const VECTOR& GetPosition() const { return position; }

	const VECTOR& GetTarget()	const { return targetposition; }
private:
	float Zoom;				//z軸のカメラポジション
	float Hight;			//y軸のカメラポジション
	float TargetHight;		//ターゲットの見る高さ
	VECTOR	position;			// ポジション.
	VECTOR targetposition;		//　カメラが注視するポジション
};