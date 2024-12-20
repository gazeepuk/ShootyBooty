// Developed by Ivan Piankouski
// GitHub / LinkedIn: gazeepuk

#pragma once

#include "CoreMinimal.h"
#include "SBWeaponComponent.h"
#include "SBAIWeaponComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTYBOOTY_API USBAIWeaponComponent : public USBWeaponComponent
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;
	virtual void EquipNextWeapon() override;
};
 