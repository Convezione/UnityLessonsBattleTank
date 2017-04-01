// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"


void UTankTurret::Rotate(float realtiveSpeed) {

	realtiveSpeed = FMath::Clamp<float>(realtiveSpeed, -1, 1);
	//UE_LOG(LogTemp,Warning,TEXT("Rotating"))
	//Move Barrel the right amount provided a max rotation
	float RotationChange = realtiveSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0.0, RawNewRotation, 0.0));
}


