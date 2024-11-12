#pragma once
class Stage
{
public:
	Stage();
	~Stage();

	void Load();	//初期化
	void Draw();	//描画

private:
	static constexpr float Scale = 0.004f;		//大きさ
	VECTOR position;	//ポジション.
	int StageHandle;	//3Dモデルハンドル


};

