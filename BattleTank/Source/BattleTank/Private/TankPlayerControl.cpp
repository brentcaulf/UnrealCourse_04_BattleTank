// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/TankPlayerControl.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

void ATankPlayerControl::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);
}

//Tick
void ATankPlayerControl::Tick(float DeltaTime)
{
	//Super
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}
	

void ATankPlayerControl::AimTowardsCrosshair()
{
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector OutHitLocation; // Out parameter
	if (GetSightRayHitLocation(OutHitLocation)) // Has "side-effect", is going to line trace
	{
		// Aim At
		AimingComponent->AimAt(OutHitLocation);
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
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-trace along that LookDirection, and see what we hit (up to max range)
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}
	if (OutHitLocation != FVector(0))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ATankPlayerControl::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // To be discarded
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		CameraWorldLocation, 
		LookDirection
	);
}

bool ATankPlayerControl::GetLookVectorHitLocation(FVector LookDirection, FVector & OutHitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult, 
		StartLocation, 
		EndLocation, 
		ECollisionChannel::ECC_Visibility)
		)
	{
		OutHitLocation = HitResult.Location;
		return true;
	}
	OutHitLocation = FVector(0);
	return false; // Line trace didn't succeed
}
