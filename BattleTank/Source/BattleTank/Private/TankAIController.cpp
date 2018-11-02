// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
// Depends on movement component via pathfinding system

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
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	// Get Controlled tank
	auto ControlledTank = GetPawn();

	// Aim at the player tank
	if (!ensure(PlayerTank && ControlledTank)) { return; }
	
	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);

	// Aim towards the player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	// TODO fix fire method	
	//ControlledTank->Fire(); // TODO limit firing rate
	
	
}


