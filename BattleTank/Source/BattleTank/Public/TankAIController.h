// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	// How close can the AI tank get to the player
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float AcceptanceRadius = 15000;

private:
	void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// Gets called when the TankAIController gets possessed
	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnPossessedTankDeath();

};
