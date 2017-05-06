// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	lastFireTime = FPlatformTime::Seconds();
	// ...
	
}

void UTankAimingComponent::Initialise(UTankBarrel* bToSet, UTankTurret* tToSet) { 
	barrel = bToSet;
	turret = tToSet;
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if ((FPlatformTime::Seconds() - lastFireTime) > reloadTimeSeconds) {
		status = EFiringStatus::Reloading;
	}
}
void UTankAimingComponent::AimAt(FVector HitLocation)
{
	
	if (!ensure(barrel)) return;
	FVector launchDirection;

	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		OUT launchDirection,
		barrel->GetSocketLocation(FName("Barrel End")),
		HitLocation,
		launchSpeed,
		false,
		100.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams::DefaultResponseParam,
		TArray<AActor*>(),
		false
		)
		) 
	{
		//UE_LOG(LogTemp, Warning, TEXT("Aim solution found at: %f"), GetWorld()->GetTimeSeconds());
		MoveBarrel(launchDirection.GetSafeNormal());
	}
	else {
		//UE_LOG(LogTemp, Warning, TEXT("Aim solution not found at: %f"), GetWorld()->GetTimeSeconds());
	}


}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	if (!ensure(barrel && turret)) { return; }
	//Compute difference between rotation
	FRotator barrelRotator = barrel->GetForwardVector().Rotation();
	FRotator aimRotation = AimDirection.Rotation();
	FRotator deltaRotator = aimRotation - barrelRotator;

	barrel->Elevate(deltaRotator.Pitch); 
	turret->Rotate(deltaRotator.Yaw);
}

void UTankAimingComponent::Shoot() {
	//UE_LOG(LogTemp, Warning, TEXT("Tank: %s firing."), *(this->GetName()));
	if (!ensure(barrel)) { return; }
	if (status != EFiringStatus::Reloading) {
		auto projectile = GetWorld()->SpawnActor<AProjectile>(projectileBlueprint,
			barrel->GetSocketLocation(FName("Barrel End")),
			barrel->GetSocketRotation(FName("Barrel End")),
			FActorSpawnParameters::FActorSpawnParameters());
		projectile->LaunchProjectile(launchSpeed);
		lastFireTime = FPlatformTime::Seconds();
	}
}
