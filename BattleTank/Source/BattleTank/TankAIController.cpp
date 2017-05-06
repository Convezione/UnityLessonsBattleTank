// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"
#include "TankAimingComponent.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	AITank = GetPawn();
	aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	PlayerTank =GetWorld()->GetFirstPlayerController()->GetPawn();
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
		aimingComponent->AimAt(PlayerTank->GetActorLocation());
		aimingComponent->Shoot();
	}
}
