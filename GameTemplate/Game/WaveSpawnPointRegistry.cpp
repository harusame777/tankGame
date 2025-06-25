#include "stdafx.h"
#include "WaveSpawnPointRegistry.h"

//スポーンポイントレジストリを初期化
void WaveSpawnPointRegistry::InitWaveSpawnPointRegistry()
{
	LevelRender waveSpawnPointLevel;

	waveSpawnPointLevel.Init(
	"Assets/levelData/spawnPointLevel/spawnPointLevelV1.tkl",
	[&](LevelObjectData_Render& objData)
	{
		//スポーンポイント取得
		if (objData.ForwardMatchName(L"SpawnPoint") == true)
		{
			m_spawnPointPosList.push_back(objData.m_position);

			return true;
		}
		return true;
	});


}

