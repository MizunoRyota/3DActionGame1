#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Stage.h"

Stage::Stage()
    :position(VGet(0, 0, -20))
	, effectPosition ( VGet(0, 0, 0))
	,effectHandle(0)
    , StageHandle(-1)
	,time(0)
{
    //処理なし
}

Stage::~Stage()
{
	// エフェクトリソースを削除する。(Effekseer終了時に破棄されるので削除しなくてもいい)
	DeleteEffekseerEffect(effectHandle);
}

void Stage::Load()
{
    StageHandle = MV1LoadModel("data/model/stage/NewStage.mv1");
	// エフェクトリソースを読み込む。
	effectHandle = LoadEffekseerEffect("data/effekseer/EfkFile/GroundFire.efkefc",4.5f);
	
	SetScalePlayingEffekseer3DEffect(effectHandle, EffektScale, EffektScale,EffektScale);
    // 3Dモデルのスケール決定
    MV1SetScale(StageHandle, VGet(Scale, Scale, Scale));
    // ３ＤモデルのY軸の回転値を正面にセットする
    MV1SetRotationXYZ(StageHandle, VGet(0.0f, 180.0f * DX_PI_F / 180.0f, 0.0f));
    // ステーのモデルの座標を更新する
    MV1SetPosition(StageHandle, position);
}

void Stage::Update()
{
	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();

	// 定期的にエフェクトを再生する
	if (time % 60 == 0)
	{
		StopEffekseer3DEffect(playingEffectHandle);
		// エフェクトを再生する。
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);
	}

	// Effekseerにより再生中のエフェクトを更新する。
	UpdateEffekseer3D();

	// 時間を経過させる。
	time++;
}

void Stage::Draw()
{
    MV1DrawModel(StageHandle);
	// Effekseerにより再生中のエフェクトを描画する。
	DrawEffekseer3D();
}