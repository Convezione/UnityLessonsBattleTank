// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	auto aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(aimingComponent)) {
		FoundAimingComponent(aimingComponent);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Aiming Component not found"));
	}
	
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
	
}


void ATankPlayerController::AimTowardsCrosshair() {
	auto p = GetPawn();
	if (!p) { return; }
	auto aimingComponent = p->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(aimingComponent)) {
		return;
	}
	FVector hitLocation;
	if (GetSightRayHitLocation(OUT hitLocation)) {
		aimingComponent->AimAt(hitLocation);
	}
}

//True if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& hit) const {
	
	//Find Crosshair location
	int32 ViewportSizeX, ViewpostSizeY;
	GetViewportSize(OUT ViewportSizeX, OUT ViewpostSizeY);
	FVector2D crossHairLocation = FVector2D(ViewportSizeX*CrossHairXLocation, ViewpostSizeY*CrossHairYLocation);
	
	//"De-Project" screen position in 3d space
	if (GetLookDirection(crossHairLocation, OUT hit)) {

		//Line trace along that direction
		FHitResult hitResult;
		auto StartLocation = PlayerCameraManager->GetCameraLocation();
		auto EndLocation = StartLocation + hit*LineTraceRange;
		if (GetWorld()->LineTraceSingleByChannel(OUT hitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility,
			FCollisionQueryParams::DefaultQueryParam,
			FCollisionResponseParams::DefaultResponseParam)) {
			hit = FVector(hitResult.Location);
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation,OUT FVector &LookDirection) const {
	FVector cameraWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, cameraWorldLocation, LookDirection);

}
