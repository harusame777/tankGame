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
	Vector3 newPosition = Vector3::Zero;

	const Vector3 modelForward = m_hostTankShellsPtr->GetForward();

	const Vector3 modelPosition = m_hostTankShellsPtr->GetPosition();

	newPosition = modelPosition + modelForward * TankShells_001_Constant::speed * g_gameTime->GetFrameDeltaTime();

	m_hostTankShellsPtr->SetPosition(newPosition);
}

//Õ“ËƒAƒNƒVƒ‡ƒ“
void TankShells_001_Normal::HitAction()
{

}

//íœˆ—
void TankShells_001_Normal::DeleteTankShellsAttributeAction()
{

}