#include "stdafx.h"
#include "EnemyTankEntity.h"

#include "EnemyTankStateMachine.h"
#include "StateMachineBase.h"
#include "TankCrawkerMovingComponent.h"
#include "TankTurretMovingComponent.h"
#include "GameCollisionManager.h"
#include "EnemyTankManager.h"
#include "GamePlayer.h"

#include "EnemyTankAttributeBase.h"
#include "EnemyTankStateTrackingUpdate.h"
#include "EnemyTankStateAttackMoveUpdate.h"
#include "EnemyTankStateUniqueUpdate.h"

//コンストラクタ
EnemyTankEntity::EnemyTankEntity()
{

}

//スタート関数
bool EnemyTankEntity::Start()
{
	//属性初期化
	m_enemyTankAttribute->InitEnemyTankAttributeData(m_player,this);

	//履帯モデル設定
	m_tankCrawkerTrack.Init(
		"Assets/modelData/tankModel/tankModelV1_crawlerTrack.tkm",
		nullptr,
		0,
		enModelUpAxisZ,
		ModelRender::en_usuallyShader
	);

	//砲塔モデル設定
	m_tankTurret.Init(
		"Assets/modelData/tankModel/tankModelV1_turret.tkm",
		nullptr,
		0,
		enModelUpAxisZ,
		ModelRender::en_usuallyShader
	);

	//ステートマシン生成
	m_stateMashine = new EnemyTankStateMachine;
	//ステートマシン登録
	m_stateMashine->SetHostEnemyTank(this);

	m_stateMashine->RegisterState<EnemyTankStateTrackingUpdate>
		(this,m_enemyTankAttribute.get());
	m_stateMashine->RegisterState<EnemyTankStateAttackMoveUpdate>
		(this,m_enemyTankAttribute.get());
	m_stateMashine->RegisterState<EnemyTankStateUniqueUpdate>
		(this, m_enemyTankAttribute.get());
	m_stateMashine->InitilizeState<EnemyTankStateTrackingUpdate>();
	//設定したステートの初期化プログラムを実行
	m_stateMashine->InitState();
	//履帯コンポーネント生成
	m_tankCrawkerMovingCom = new TankCrawkerMovingComponent;
	//砲塔コンポーネント生成
	m_tankTurretMovingCom = new TankTurretMovingComponent;

	characterController.Init(5.0f, 5.0f, m_position);

	//履帯コンポーネント設定
	m_tankCrawkerMovingCom->InitTankCrawkerMoveingData(
		m_moveForward,
		m_forward,
		m_enemyTankAttribute->m_maxTankSpeed,
		characterController,
		rotSpeed,
		m_tankCrawkerTrack
	);

	//砲塔コンポーネント設定
	m_tankTurretMovingCom->InitTankTurretMovingData(
		m_targetForward,
		m_position,
		m_forward,
		m_moveForward,
		rotSpeed,
		m_tankTurret
	);

	//当たり判定作成
	m_collision = GameCollisionManager::GetCollisionManagerInstance()
		->CreateSphereCollision(
		m_position,
		m_rotation,
		30.0f,
		"EnemyTankCollision"
	);

	return true;
}

//アップデート関数
void EnemyTankEntity::Update()
{
	//削除フラグが経っている状態では処理はしない
	if (m_isDeleteFlag == true)
	{
		//属性ごとの削除処理が終了した際に本体を削除する
		if (m_enemyTankAttribute->DeleteProcessing())
		{
			EnemyTankManager::GetEnemyTankManagerInstance()
				->ActivateDeleteFlag(this);
		}

		return;
	}

	//ステートマシン更新
	m_stateMashine->Update();

	m_position = m_tankCrawkerMovingCom->CalcCrawkerMovingDataAndModelUpdate();

	//砲撃処理
	if (m_fireFlag)
	{
		m_enemyTankAttribute->FireProcessing();
	}

	//砲塔移動更新
	m_turretPosition = m_tankTurretMovingCom->CalcTurretMovingDataAndModelUpdate();

	//消去処理
	if (GameCollisionManager::GetCollisionManagerInstance()
		->IsAColisionHitsBColision(m_collision.get(),"GamePlayerAttack") == true
		&& m_isDeleteFlag == false)
	{
		//エンティティ内の削除フラグ
		m_isDeleteFlag = true;
	}
	
	//モデル更新
	m_tankCrawkerTrack.Update();
	m_tankTurret.Update();

	//当たり判定位置更新
	Vector3 colPos = m_position;
	colPos.y += 35.0f;
	m_collision->SetPosition(colPos);
	m_collision->Update();
}

//レンダリング関数
void EnemyTankEntity::Render(RenderContext& rc)
{
	//描画フラグがtrueの時のみ描画
	if (m_drawFlag == false)
	{
		return;
	}

	m_tankCrawkerTrack.Draw(rc);

	m_tankTurret.Draw(rc);
}

void EnemyTankEntity::DeleteGOEnemyTank()
{
	DeleteGO(this);
}

void EnemyTankEntity::SetCollisionEnable(bool isEnable)
{
	GameCollisionManager::GetCollisionManagerInstance()
		->SetCollisionEnable(m_collision.get(), isEnable);
}