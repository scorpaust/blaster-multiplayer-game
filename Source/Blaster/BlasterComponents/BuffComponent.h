#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuffComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLASTER_API UBuffComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UBuffComponent();

	friend class ABlasterCharacter;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Heal(float HealAmount, float HealingTime);

	void BuffSpeed(float BuffBaseSpeed, float BuffCrouchSpeed, float BuffTime);

	void SetInitialSpeeds(float BaseSpeed, float CrouchSpeed);

	void SetInitialJumpVelocity(float Velocity);

	void BuffJump(float BuffJumpVelocity, float BuffTime);

protected:

	virtual void BeginPlay() override;

	void HealRampUp(float DeltaTime);

private:

	UPROPERTY()
	class ABlasterCharacter* Character;

	/**
	* Heal Buff
	*/

	bool bHealing = false;
	
	float HealingRate = 0.f;

	float AmountToHeal = 0.f;

	/**
	* Speed Buff
	*/

	float InitialBaseSpeed;

	float InitialCrouchSpeed;

	FTimerHandle SpeedBuffTimer;

	void ResetSpeeds();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastSpeedBuff(float BaseSpeed, float CrouchSpeed);

	/**
	* Jump Buff
	*/

	FTimerHandle JumpBuffTimer;

	void ResetJump();

	float InitialJumpVelocity;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastJumpBuff(float JumpVelocity);

public:	

	
};
