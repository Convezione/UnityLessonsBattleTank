// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

#define OUT
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	ATank* getControlledTank() const;
	
	virtual void BeginPlay() override;

	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& hit) const;	//True if hits landscape
	bool GetLookDirection(FVector2D ScreenLocation, OUT FVector &LookDirection) const;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		float CrossHairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
		float CrossHairYLocation = 0.33333333;
	UPROPERTY(EditAnywhere)
		float LineTraceRange = 100000;
};
