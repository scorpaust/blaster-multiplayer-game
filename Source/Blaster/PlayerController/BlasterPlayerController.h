// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BlasterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BLASTER_API ABlasterPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void SetHUDHealth(float Health, float MaxHealth);

	void SetHUDShield(float Shield, float MaxShield);

	void SetHUDScore(float Score);

	void SetHUDDefeats(int32 Defeats);

	void SetHUDWeaponAmmo(int32 Ammo);

	void SetHUDWeaponTexture(UTexture2D* WeaponTexture);

	void SetHUDCarriedAmmo(int32 Ammo);

	void SetHUDMatchCountDown(float CountDownTime);

	void SetHUDAnnouncementCountDown(float CountDownTime);

	void SetHUDGrenades(int32 Grenades);

	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaTime) override;

	// Synced with server world clock
	virtual float GetServerTime();

	// Sync with server clock as soon as possible
	virtual void ReceivedPlayer() override;

	void OnMatchStateSet(FName State);

	void HandleMatchHasStarted();

	void HandleCooldown();

protected:

	virtual void BeginPlay() override;

	void SetHUDTime();

	void PollInit();

	/**
	* Sync time between client and server
	*/

	// Requests the current server time passing in the client's time when the request was sent
	UFUNCTION(Server, Reliable)
	void ServerRequestServerTime(float TimeOfClientRequest);

	// Reports the current server time to the client in response to ServerRequestServerTime
	UFUNCTION(Client, Reliable)
	void ClientReportServerTime(float TimeOfClientRequest, float TimeServerReceivedClientRequest);

	// Difference between client and server time
	float ClientServerDelta = 0.f;

	UPROPERTY(EditAnywhere, Category = Time)
	float TimeSyncFrequency = 5.f;

	float TimeSyncRunningTime = 0.f;

	void CheckTimeSync(float DeltaTime);

	UFUNCTION(Server, Reliable)
	void ServerCheckMatchState();

	UFUNCTION(Client, Reliable)
	void ClientJoinMidGame(FName StateOfMatch, float WarmUp, float Match, float Cooldown, float StartingTime);

private:

	UPROPERTY()
	class ABlasterHUD* BlasterHUD;

	UPROPERTY()
	class ABlasterGameMode* BlasterGameMode;

	float LevelStartingTime = 0.f;

	float MatchTime = 0.f;

	float WarmUpTime = 0.f;

	float CooldownTime = 0.f;

	uint32 CountDownInt = 0;

	UPROPERTY(ReplicatedUsing=OnRep_MatchState)
	FName MatchState;

	UFUNCTION()
	void OnRep_MatchState();

	UPROPERTY()
	class UCharacterOverlay* CharacterOverlay;

	float HUDHealth;

	bool bInitializeHealth = false;

	float HUDMaxHealth;

	float HUDShield;

	bool bInitializeShield = false;

	float HUDMaxShield;

	float HUDScore;

	bool bInitializeScore = false;

	int32 HUDDefeats;

	bool bInitializeDefeats = false;

	int32 HUDGrenades;

	bool bInitializeGrenades = false;
};
