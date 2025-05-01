#include "stdafx.h"
#include "Cannonball_001_Normal.h"

#include "CannonballAttributeRegistry.h"


//‰Šú‰»ŠÖ”“o˜^ˆ—
bool Cannonball_001_Normal::m_attributeRegistered = [] {
	CannonballAttributeRegistry::registerFactory(EnCannonballAttribute::en_normal, []() {
		return std::make_unique<Cannonball_001_Normal>();
		});
	return true;
}();

//‰Šú‰»
void Cannonball_001_Normal::InitData()
{

}

//ŒvZ
void Cannonball_001_Normal::MoveCalc()
{
	
}

//Õ“ËƒAƒNƒVƒ‡ƒ“
void Cannonball_001_Normal::HitAction()
{

}