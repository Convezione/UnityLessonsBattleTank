// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankAimingComponent;
class UTankTurret;
class AProjectile;
UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UTankAimingComponent* TankAimingComponent = nullptr;
	UTankBarrel* localBarrel;
public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelReference(UTankBarrel* toSet);
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretReference(UTankTurret* toSet);
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		TSubclassOf<AProjectile> projectileBlueprint;
	UPROPERTY(EditDefaultsOnly,Category = Firing)
		float launchSpeed = 100000;		// TODO find sensible default (this is 10 m/s)
	UFUNCTION(BlueprintCallable, Category = Firing)
		void Shoot();
private:
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		double reloadTimeSeconds = 3;
	double lastFireTime = 0;
};
