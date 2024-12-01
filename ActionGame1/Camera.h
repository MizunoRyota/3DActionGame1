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
	void ShakeCamera(float intensity, float duration,const Player& player);
	void GameEnd(const VECTOR& planepos);//ゲームオーバー画面準備

	// ポジションのgetter/setter.
	const VECTOR& GetPosition() const { return position; }

	const VECTOR& GetTarget()	const { return targetposition; }
private:
	float Zoom;				//z軸のカメラポジション
	float Hight;			//y軸のカメラポジション
	float TargetHight;		//ターゲットの見る高さ
	// 揺れの強さと持続時間
	static constexpr float shakeIntensity=5.0f;
	static constexpr float shakeDuration = 2.0f;
	float shakeTime;
	bool isDamage;
	VECTOR Offset;
	VECTOR OriginalOffset;
	VECTOR	position;			// ポジション.
	VECTOR targetposition;		//　カメラが注視するポジション
};