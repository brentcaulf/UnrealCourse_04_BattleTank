// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	
	
	
}

//Tick
void ATankAIController::Tick(float DeltaTime)
{
	//Super
	Super::Tick(DeltaTime);
	// Get Player tank
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	// Get Controlled tank
	auto ControlledTank = Cast<ATank>(GetPawn());

	// Aim at the player tank
	if (PlayerTank)
	{
		// TODO Move towards the player

		// Aim towards the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		
		ControlledTank->Fire(); // TODO limit firing rate
	}
	
}


