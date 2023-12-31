// ShootyBooty by @GazeePuk. All Rights Reversed


#include "Pickups/SBAmmoPickup.h"

#include "SBUtils.h"


bool ASBAmmoPickup::GivePickupTo(APawn* InPlayerPawn)
{
	const auto HealthComponent = USBUtils::GetHealthComponent(InPlayerPawn);
	if(!HealthComponent || HealthComponent->IsDead()) return false;

	const auto WeaponComponent = USBUtils::GetWeaponComponent(InPlayerPawn);
	if(!WeaponComponent) return false;
	
	return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}
