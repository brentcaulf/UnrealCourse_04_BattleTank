// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return; }

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;

}


void UTankMovementComponent::IntendMoveForward(float Throw)
{	
	//UE_LOG(LogTemp, Warning, TEXT("Intend move forward throw: %f"), Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	// TODO prevent double-speed due to dual control use
}

void UTankMovementComponent::IntendMoveRight(float Throw)
{
	
	if (Throw > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Intend move left: %f"), Throw);
		LeftTrack->SetThrottle(Throw);
	}
	if (Throw < 0)
	{ 
		UE_LOG(LogTemp, Warning, TEXT("Intend move right: %f"), Throw);
		RightTrack->SetThrottle(Throw);
	}
}


