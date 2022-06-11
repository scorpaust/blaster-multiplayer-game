// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileRocket.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"


AProjectileRocket::AProjectileRocket()
{
	RocketMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RocketMesh"));

	RocketMesh->SetupAttachment(RootComponent);

	RocketMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AProjectileRocket::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	APawn* FiringPawn = GetInstigator();

	if (FiringPawn)
	{
		AController* FiringController = FiringPawn->GetController();

		if (FiringController)
		{
			UGameplayStatics::ApplyRadialDamageWithFalloff(
				this, // World context object
				Damage, // Base damage
				10.f, // Minimal damage
				GetActorLocation(), // Origin of the damage
				200.f, // Damage Inner Radius
				500.f, // Damage Outer Radius
				1.f, // Damage Falloff
				UDamageType::StaticClass(), // Damage Type Class
				TArray<AActor*>(), // Ignore Actors
				this, // Damage Causer
				FiringController // Instigator Controller
			);
		}
	}

	Super::OnHit(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);
}