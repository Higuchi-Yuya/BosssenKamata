#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "affine.h"
#include "Input.h"
#include "DebugText.h"
#include <cassert>

class BossPhase_2
{
public:// サブクラス
	enum class Motion {
		standby,
		beam,
		boomerang,
		rush,
		reflector,
	};

public:// メンバ関数
	// 初期化関数
	void Initialize();

	// 更新処理
	void Update(Vector3 playerPos);

	// 描画処理
	void Draw(ViewProjection viewprojection);

private:
	void beamUpdate(Vector3 playerPos);

	void boomerangUpdate();

	void rushUpdate(Vector3 playerPos);

	// 行列の転送と更新
	void TransferMat();

	float Lerp(const float& startPos, const float& endPos, const float& timeRate);

	double easing_Out(double start, double end, double time, double max_time);


	float DegreeToRad(float num)
	{
		return num / 180 * MathUtility::PI;
	}

	float RadToDegree(float num)
	{
		return num / MathUtility::PI * 180;
	}

	// ビーム関連のリセット
	void beamReset();

	void TurnBodyToPlayer(Vector3 playerPos);

	void TurnBeamToPlayer();

	//ブーメラン関連のセット
	void  boomerangSet(Vector3 playerPos);

private:// メンバ変数
	//ワールド変換データ
	WorldTransform worldTransform_[19];

	// キューブ用のスケールの変数
	float kyubuScale = 3.0f;
	float kyubuLengh = 2.0f;

	// 親の回転要素
	Vector3 oyaRota;
	Matrix4 oyaRotation;

	// デバッグテキスト
	DebugText* debugText_ = nullptr;

	// インプット
	Input* input_ = nullptr;

	//モデル
	Model* model_ = nullptr;

	// ビーム用の変数
	#pragma region ビーム用の変数
	// ビームのワールドデータ
	WorldTransform beamWorldTransform_;
	// ビームのモデル
	Model* beamModel_ = nullptr;

	bool beamFlag = false;
	bool beamSetFlag = false;
	bool beamOBJSetFlag = false;
	int beamTimer = 0;
	int beamtoPTimer = 0;

	// 半分の時間
	int maxTimer = 6 * 60;
	// ビーム開始の時間
	int maxStartTimer = 3 * 60;
	// ビーム収束開始の時間
	int maxEndTimer = 6 * 60;
	// ポジション更新する間隔
	int beamUpdatePosIntaval = 0.3 * 60;
	// 収束時間
	int convergenceTimer = 0;
	int maxConvergenceT = 6 * 60;
	
	Vector3 oldPlayerPos;
	Vector3 oldPlayerPos2;
	Vector3 oldVelocity;
	Vector3 beamToPlayerVel;
	Vector3 beamToPlayerVelUp;
	Vector3 beamLength;
	float beamSpeed = 1.0f;
	#pragma endregion

#pragma region 移動用変数

	float angle = 90;

	float radius = 50;

#pragma endregion

#pragma region ブーメラン用変数

	// 消すときのフラグ
	bool AnnihilationFlag[27];

	//上のブーメラン用ワールドトランスフォーム
	WorldTransform upBoomerangWorldTransform[5];

	float upAngle = 0;

	Vector3 upVector;

	bool isUpActive = false;

	bool isUpAttack = false;

	bool isUpDirectionRight=false;

	//下のブーメランようワールドトランスフォーム
	WorldTransform downBoomerangWorldTransform[5];

	float downAngle = 0;

	Vector3 downVector;

	bool isDownActive = false;

	bool isDownAttack = false;

	bool isDownDirectionRight=false;

#pragma endregion

#pragma region 突進用変数
	// 突進開始用のフラグ
	bool rushFlag = false;
	// 下げるときのポジションY
	float downPosY = 2.0f;
	// 元の高さを記録する変数
	float originPosY = 0.0f;

	// 突進時のボスとプレイヤーのベクトル
	Vector3 rushToPlayer;

	// 押し戻し判定があるかどうかチェックするフラグ
	bool rushFinsh = false;

#pragma endregion

};

