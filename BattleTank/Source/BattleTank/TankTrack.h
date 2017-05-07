// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void SetThrottle(float throttle);
	void DriveTrack();
	//Half of max force per track in Newton
	UPROPERTY(EditDefaultsOnly)
		float MaxDrivingForce = 125000.0f;
	virtual void BeginPlay() override;
	
	
	void ApplyLateralFrictionCorrection();
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

private:
	UTankTrack();
	void ApplyLateralFrictionCorrection(float DeltaTime);
	float currentThrottle = 0.0f;
};
