// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"


void UTankTrack::SetThrottle(float throttle) {
	UE_LOG(LogTemp, Warning, TEXT("%s throttle %f"), *(this->GetName()),throttle);
	auto ForceApplied = GetForwardVector()*throttle*MaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
void UTankTrack::SetAcceleration(float amount) {
	auto ForceApplied = GetForwardVector()*amount*MaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
