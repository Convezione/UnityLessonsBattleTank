// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"
#include "Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	AITank = Cast<ATank>(GetPawn());
	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ensure(AITank);
	ensure(PlayerTank);
}
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsTank();
	MoveToActor(PlayerTank,AcceptanceRadius);
}

void ATankAIController::AimTowardsTank() {
	if (ensure(PlayerTank)) {
		AITank->AimAt(PlayerTank->GetActorLocation());
		AITank->Shoot();
		
	}
}
