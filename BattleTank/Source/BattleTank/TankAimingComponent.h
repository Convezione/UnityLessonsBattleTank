// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

#define OUT
class UTankBarrel;	//Forward declaration
class UTankTurret;
class AProjectile;

UENUM()
enum class EFiringStatus : uint8 {
	Locked,
	Aiming,
	Reloading
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialise(UTankBarrel* bToSet, UTankTurret* tToSet);
	EFiringStatus getFiringStatus() const;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
		EFiringStatus status = EFiringStatus::Reloading;


	UTankBarrel* barrel = nullptr;
	UTankTurret* turret = nullptr;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void AimAt(FVector);
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float launchSpeed = 100000;	
	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Shoot();
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		TSubclassOf<AProjectile> projectileBlueprint;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		double reloadTimeSeconds = 3;
	double lastFireTime = 0;
	void MoveBarrel(FVector AimDirection);
	bool IsBarrelMoving();
	FVector aimVector;
};
