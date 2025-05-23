#include "stdafx.h"
#include "EnemyTank_001_Normal.h"

#include "EnemyTankAttributeRegistry.h"
#include "EnemyTankAttribute.h"
#include "TankShellsAttribute.h"

//‰Šú‰»ŠÖ”“o˜^ˆ—
bool EnemyTank_001_Normal::m_attributeRegistered = [] {
	EnemyTankAttributeRegistry::EnemyTankRegisterFactory(EnEnemyTankAttribute::en_tankNormal, []() {
		return std::make_unique<EnemyTank_001_Normal>();
		});
	return true;
}();

//‘®«‰Šú‰»ŠÖ”
void EnemyTank_001_Normal::InitEnemyTankAttributeData()
{
	m_maxTankSpeed = 50.0f;

	m_shellsUsed = EnTankShellsAttribute::en_normal;
}

//ŒÅ—Lˆ—
void EnemyTank_001_Normal::EnemyTankUniqueProcessing()
{

}

//íœˆ—
void EnemyTank_001_Normal::EnemyTankDeleteProcessing()
{

}