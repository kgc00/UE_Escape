// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Engine/TriggerVolume.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOMTUTORIAL_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
	
	

private:
	UPROPERTY(VisibleAnywhere)
	float OpenAngle = 90.0f;

	UPROPERTY(VisibleAnywhere)
		float CloseAngle = 0.0f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate;

	AActor* Owner;
		
		AActor* ActorThatOpensDoor;

		UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 1.0f;

		float LastDoorOpenTime;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();

	void CloseDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
