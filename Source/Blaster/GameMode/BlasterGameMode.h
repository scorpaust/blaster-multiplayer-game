// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BlasterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BLASTER_API ABlasterGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:

	ABlasterGameMode();

	virtual void Tick(float DeltaTime) override;

	virtual void PlayerEliminated(class ABlasterCharacter* EliminatedCharacter, class ABlasterPlayerController* VictimController, class ABlasterPlayerController* AttackerController);

	virtual void RequestRespawn(class ACharacter* EliminatedCharacter, class AController* EliminatedController);

	UPROPERTY(EditDefaultsOnly)
	float WarmUpTime = 10.f;

	float LevelStartingTime = 0.f;

protected:

	virtual void BeginPlay() override;

	virtual void OnMatchStateSet() override;

private:

	float CountDownTime = 0.f;
};
