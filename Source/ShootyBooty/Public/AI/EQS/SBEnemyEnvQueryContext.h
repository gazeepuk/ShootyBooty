// Developed by Ivan Piankouski
// GitHub / LinkedIn: gazeepuk

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "SBEnemyEnvQueryContext.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTYBOOTY_API USBEnemyEnvQueryContext : public UEnvQueryContext
{
	GENERATED_BODY()
public:
	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	FName EnemyActorKeyName = "EnemyActor";
};
