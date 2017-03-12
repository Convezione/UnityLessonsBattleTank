// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto tank = getAITank();
	if (tank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController Begin play\nControlling: %s"), *(tank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("AIController Begin play\nControlling: No Tank"));
	}
	tank = getPlayerTank();
	if (tank) {
		UE_LOG(LogTemp, Warning, TEXT("Player Tank: %s"), *(tank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Player Tank Existing in the world"));
	}
}
ATank * ATankAIController::getPlayerTank()
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
ATank * ATankAIController::getAITank() const
{
	return Cast<ATank>(GetPawn());
}
