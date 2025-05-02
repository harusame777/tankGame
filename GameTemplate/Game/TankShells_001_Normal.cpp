#include "stdafx.h"
#include "TankShells_001_Normal.h"

#include "TankShellsAttributeRegistry.h"


//‰Šú‰»ŠÖ”“o˜^ˆ—
bool TankShells_001_Normal::m_attributeRegistered = [] {
	TankShellsAttributeRegistry::registerFactory(EnTankShellsAttribute::en_normal, []() {
		return std::make_unique<TankShells_001_Normal>();
		});
	return true;
}();

//‰Šú‰»
void TankShells_001_Normal::InitData()
{

}

//ŒvZ
void TankShells_001_Normal::MoveCalc()
{
	
}

//Õ“ËƒAƒNƒVƒ‡ƒ“
void TankShells_001_Normal::HitAction()
{

}