// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float realtiveSpeed) {

	realtiveSpeed = FMath::Clamp<float>(realtiveSpeed, -1, 1);

	//Move Barrel the right amount provided a max rotation
	float ElevationChange = realtiveSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	RawNewElevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(RawNewElevation, 0.0, 0.0));
}



