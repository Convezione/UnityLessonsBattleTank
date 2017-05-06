// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* lToSet, UTankTrack* rToSet) {
	if (!ensure(lToSet) || !ensure(rToSet)) {
		return;
	}
	rightTrack = rToSet;
	leftTrack = lToSet;
}
void UTankMovementComponent::IntendMoveForward(float Throw) {
	if (!ensure(rightTrack && leftTrack)) {
		return;
	}
	rightTrack->SetThrottle(Throw);
	leftTrack->SetThrottle(Throw);
}
void UTankMovementComponent::IntendTurnRight(float Throw) {
	if(!ensure(rightTrack && leftTrack))
	rightTrack->SetThrottle(-Throw);
	leftTrack->SetThrottle(Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
	//UE_LOG(LogTemp, Warning, TEXT("Requested Movement from %s to position %s"), *(GetOwner()->GetName()),*(MoveVelocity.ToString()));
	auto TankForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto MovementDirection = MoveVelocity.GetSafeNormal();
	
	auto ForwardTrow = FVector::DotProduct(TankForwardDirection, MovementDirection);
	IntendMoveForward(ForwardTrow);
	
	auto RightThrow = FVector::CrossProduct(TankForwardDirection, MovementDirection).Z;
	IntendTurnRight(RightThrow);
}
