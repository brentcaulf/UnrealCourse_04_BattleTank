// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h" // So we can implement OnDeath

// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// TODO Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	// This is how the lecturer did it but I think it works better to call directly from the pawn
	//if (!ensure(GetPawn())) { return; }
	//GetPawn()->DetachFromControllerPendingDestroy();
	GetPawn()->Destroy(); // TODO destroy AI controller also?
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
	if (!(PlayerTank && ControlledTank)) { return; }
	
	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);

	// Aim towards the player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	if (AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire(); // TODO limit firing rate
	}	
}




