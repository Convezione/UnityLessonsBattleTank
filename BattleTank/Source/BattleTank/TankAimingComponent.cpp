// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
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

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
void UTankAimingComponent::AimAt(FVector HitLocation,float launchSpeed)
{
	
	if (!barrel) return;
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
		UE_LOG(LogTemp, Warning, TEXT("Aim solution found at: %f"), GetWorld()->GetTimeSeconds());
		MoveBarrel(launchDirection.GetSafeNormal());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Aim solution not found at: %f"), GetWorld()->GetTimeSeconds());
	}


}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * toSet)
{
	barrel = toSet;
	return;
}
void UTankAimingComponent::SetTurretReference(UTankTurret * toSet)
{
	turret = toSet;
	return;
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	//Compute difference between rotation
	FRotator barrelRotator = barrel->GetForwardVector().Rotation();
	FRotator aimRotation = AimDirection.Rotation();
	FRotator deltaRotator = aimRotation - barrelRotator;

	barrel->Elevate(deltaRotator.Pitch); 
	turret->Rotate(deltaRotator.Yaw);
}
