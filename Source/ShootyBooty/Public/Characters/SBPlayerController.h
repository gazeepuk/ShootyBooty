// ShootyBooty by @GazeePuk. All Rights Reversed

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SBPlayerController.generated.h"

class ADeathMatchPlayerState;
class UInputMappingContext;
class ASBGameHUD;
/**
 * 
 */
UCLASS()
class SHOOTYBOOTY_API ASBPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ASBPlayerController();
	void SetHUDMatchCountdown(float CountdownTime);
	void SetAnnouncementCountdown(float CountdownTime);
	void SetTopScoringPlayer(const TArray<ADeathMatchPlayerState*>& InTopScoringPlayerStates);
	
	//Synced with server world clock
	virtual float GetServerTime();
	//Sync with server clock
	virtual void ReceivedPlayer() override;

	void OnMatchStateSet(FName InMatchState);
	void OnTopScoringPlayersSet(const TArray<ADeathMatchPlayerState*>& InTopScoringPlayerStates);
protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	void SetHUDTime();

	//Requests the current server time, passing in the client's time when the request was sent 
	UFUNCTION(Server, Reliable)
	void Server_RequestServerTime(float TimeOfClientRequest);

	//Reports the current server time to the client in response to Server_requestServerTime
	UFUNCTION(Client, Reliable)
	void Client_ReportServerTime(float TimeOfClientRequest, float TimeServerReceivedClientRequest);

	// Difference between server and client time
	float ClientServerDelta = 0.f;
	UPROPERTY(EditAnywhere)
	float TimeSyncFrequency = 5.f;
	float TimeSyncRunningTime = 0.f;

	UFUNCTION(Server, Reliable)
	void Server_CheckMatchState();

	UFUNCTION(Client,Reliable)
	void Client_JoinMidgame(FName InMatchState, float InWarmupTime, float InCooldownTime, float InMatchTime, float InLevelStartingTime);

private:
	virtual void Tick(float DeltaSeconds) override;
	void CheckTimeSynced(float DeltaSeconds);

	TObjectPtr<ASBGameHUD> SBGameHUD;
	
	float MatchTime = 0.f;
	float WarmupTime = 0.f;
	float CooldownTime = 0.f;
	float LevelStartingTime = 0.f;
	uint32 CountdownInt = 0;

	UPROPERTY(ReplicatedUsing = OnRep_MatchState)
	FName MatchState;
	UFUNCTION()
	void OnRep_MatchState();

	UPROPERTY(ReplicatedUsing = OnRep_TopScoringPlayers)
	TArray<ADeathMatchPlayerState*> TopScoringPlayerStates;
	UFUNCTION()
	void OnRep_TopScoringPlayers();
	
	void HandleMatchHasStarted();
	void HandleCooldown();
};
