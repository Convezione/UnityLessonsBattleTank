// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

#define OUT
/**
 * 
 */

class ATank;
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

	UPROPERTY(EditDefaultsOnly)
		float CrossHairXLocation = 0.5;
	UPROPERTY(EditDefaultsOnly)
		float CrossHairYLocation = 0.33333333;
	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 100000;

};
