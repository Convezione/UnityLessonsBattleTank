// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"
#include "Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	AITank = Cast<ATank>(GetPawn());
	if (AITank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController Begin play\nControlling: %s"), *(AITank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("AIController Begin play\nControlling: No Tank"));
	}
	if (PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("Player Tank: %s"), *(PlayerTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Player Tank Existing in the world"));
	}
}
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsTank();
}

void ATankAIController::AimTowardsTank() {
	if (PlayerTank) {
		AITank->AimAt(PlayerTank->GetActorLocation());
		AITank->Shoot();
		
	}
}
