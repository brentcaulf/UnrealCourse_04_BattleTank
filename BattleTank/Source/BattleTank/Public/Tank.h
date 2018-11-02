// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward Declarations
class UTankBarrel;
class UTankTurret;
class AProjectile;
class UTankTrack;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;
	
	// TODO Remove once firing is moved to aiming comp
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000.0;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3;

	UTankBarrel* Barrel = nullptr; // TODO Remove
	
	double LastFireTime = 0;
};
