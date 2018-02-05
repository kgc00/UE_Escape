// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Gameframework/Actor.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();	

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle) {
		UE_LOG(LogTemp, Warning, TEXT("PhysicsHandle found! Name: %s"), *PhysicsHandle->GetName());
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("PhysicsHandle not found on %s!"), *GetOwner()->GetName());
	}

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("InputComponent found! Name: %s"), *InputComponent->GetName());
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("PhysicsHandle not found on %s!"), *GetOwner()->GetName());
	}

}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Error, TEXT("Grab function called!"));
}

void UGrabber::Release() {
	UE_LOG(LogTemp, Error, TEXT("Release function called!"));
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewLocation, OUT PlayerRotation);
	//UE_LOG(LogTemp, Warning, TEXT("Logging view! Location: %s, Position: %s"), *PlayerViewLocation.ToString(), *PlayerRotation.ToString())

	FVector LineTraceEnd = PlayerViewLocation + PlayerRotation.Vector() * Reach;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	//DrawDebugLine(GetWorld(), PlayerViewLocation, LineTraceEnd, FColor(255, 0, 0), false, 0.f, 0.f, 10.f);

	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(OUT Hit, PlayerViewLocation, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams);
	AActor* ActorGrabbed = Hit.GetActor();
	if (ActorGrabbed)	{
	//UE_LOG(LogTemp, Warning, TEXT("Logging Actor Hit By Grabber! Name: %s"), *ActorGrabbed->GetName());
	}
}

