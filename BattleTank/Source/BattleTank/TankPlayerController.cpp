// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	auto tank = getControlledTank();
	if (tank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin play\nControlling: %s"),*(tank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("PlayerController Begin play\nControlling: No Tank"));
	}
}

ATank* ATankPlayerController::getControlledTank() const {
	return Cast<ATank>(GetPawn());
}

