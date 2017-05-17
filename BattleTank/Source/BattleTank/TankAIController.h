// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
class UTankAimingComponent;
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
private:
	APawn* AITank;
	UTankAimingComponent* aimingComponent;
	virtual void BeginPlay() override;
	APawn* PlayerTank;
	virtual void Tick(float DeltaTime) override;
	void AimTowardsTank();
protected:
	UPROPERTY(EditDefaultsOnly, Category ="Movement")
		float AcceptanceRadius = 8000;

};
