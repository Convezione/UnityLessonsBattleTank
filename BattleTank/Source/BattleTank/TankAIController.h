// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
class ATank;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
private:
	ATank* AITank;
	virtual void BeginPlay() override;
	ATank* PlayerTank;
	virtual void Tick(float DeltaTime) override;
	void AimTowardsTank();
	UPROPERTY(EditDefaultsOnly, Category = Movement)
		float AcceptanceRadius = 3000;

};
