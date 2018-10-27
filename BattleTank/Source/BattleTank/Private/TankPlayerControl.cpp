// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankPlayerControl.h"

void ATankPlayerControl::BeginPlay()
{
	Super::BeginPlay();

	GetControlledTank();
	UE_LOG(LogTemp, Warning, TEXT("%s is the player's controlled pawn"), *(GetControlledTank()->GetName()));
}

//Tick
void ATankPlayerControl::Tick(float DeltaTime)
{
	//Super
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}
	

ATank* ATankPlayerControl::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerControl::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector OutHitLocation; // Out parameter
	if (GetSightRayHitLocation(OutHitLocation)) // Has "side-effect", is going to line trace
	{
		//UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *OutHitLocation.ToString());
		// TODO Tell controlled tank to aim at this point
	}
}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerControl::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	
	// "De-project" the screen position of the crosshair to a world direction
	// Line-trace along that look direction, and see what we hit (up to max range)
	return true;
}
