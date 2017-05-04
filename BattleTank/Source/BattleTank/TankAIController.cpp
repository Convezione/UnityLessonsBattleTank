// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"
#include "Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	AITank = Cast<ATank>(GetPawn());
	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (AITank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController Begin play\nControlling: %s"), *(AITank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("AIController Begin play\nControlling: No Tank"));
	}
	if (PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("Player tank is: %s"), *(PlayerTank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Player tank is: No Tank"));
	}
}
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsTank();
	MoveToActor(PlayerTank,AcceptanceRadius);
}

void ATankAIController::AimTowardsTank() {
	if (PlayerTank) {
		AITank->AimAt(PlayerTank->GetActorLocation());
		AITank->Shoot();
		
	}
}
