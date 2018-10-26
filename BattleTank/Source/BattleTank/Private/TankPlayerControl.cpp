// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankPlayerControl.h"

void ATankPlayerControl::BeginPlay()
{
	Super::BeginPlay();

	GetControlledTank();
	UE_LOG(LogTemp, Warning, TEXT("%s is the player's controlled pawn"), *(GetControlledTank()->GetName()));
}

ATank* ATankPlayerControl::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


