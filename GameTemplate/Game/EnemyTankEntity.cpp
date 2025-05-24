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
	m_stateMashine->InitilizeState<EnemyTankStateTrackingUpdate>();
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
		rotSpeed,
		m_tankTurret
	);

	//当たり判定作成
	m_collision = GameCollisionManager::GetCollisionManagerInstance()->CreateSphereCollision(
		m_position,
		m_rotation,
		30.0f,
		"EnemyCollision"
	);

	return true;
}

//アップデート関数
void EnemyTankEntity::Update()
{
	//属性固有処理
	m_enemyTankAttribute->UniqueProcessing();
	
	//ステートマシン更新
	m_stateMashine->Update();

	//履帯移動更新
	m_position = m_tankCrawkerMovingCom->CalcCrawkerMovingDataAndModelUpdate();
	//砲塔移動更新
	m_turretPosition = m_tankTurretMovingCom->CalcTurretMovingDataAndModelUpdate();

	//消去処理
	if (GameCollisionManager::GetCollisionManagerInstance()
		->IsAColisionHitsBColision(m_collision.get(), "shellsCollision") == true 
		&& m_isDeleteFlag == false)
	{
		//エンティティ内の削除フラグ
		m_isDeleteFlag = true;
		//属性ごとの削除処理
		m_enemyTankAttribute->DeleteProcessing();
		//マネージャーに削除フラグを送る
		EnemyTankManager::GetEnemyTankManagerInstance()->ActivateDeleteFlag(this);
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
	m_tankCrawkerTrack.Draw(rc);

	m_tankTurret.Draw(rc);
}

void EnemyTankEntity::DeleteGOEnemyTank()
{


	DeleteGO(this);
}