// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"
UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = false;
	
}
void UTankTrack::BeginPlay() {
	Super::BeginPlay();
	FScriptDelegate hitDelegate;
	hitDelegate.BindUFunction(this, FName("OnHit"));
	OnComponentHit.Add(hitDelegate);
}



void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, 
						AActor* OtherActor, 
						UPrimitiveComponent* OtherComponent, 
						FVector NormalImpulse, 
						const FHitResult& Hit) 
{
	currentThrottle = 0.f;
	ApplyLateralFrictionCorrection();
}


void UTankTrack::ApplyLateralFrictionCorrection()
{
	//Calculate the sideways component of speed
	auto sidewaysSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	//Calculate acceleration to correct
	auto correctingAcceleration = -sidewaysSpeed / GetWorld()->GetDeltaSeconds() * GetRightVector();
	//Calculate sideways force
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	auto correctingForce = correctingAcceleration*tankRoot->GetMass() / 2;
	tankRoot->AddForce(correctingForce);
}
void UTankTrack::SetThrottle(float throttle) {
	currentThrottle = FMath::Clamp(currentThrottle+throttle,-1.0f,1.0f);
	DriveTrack();
}

void UTankTrack::DriveTrack() {
	auto ForceApplied = GetForwardVector()*currentThrottle*MaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}


