// Copyright Craig O'Donnell 2017

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDoorRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPETHEROOM_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties (this runs the Initializer/Constructor function)
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
    
    // Creates an OnOpen and OnClose events to be broadcast to the blueprint
    UPROPERTY(BlueprintAssignable)
    FOnDoorRequest OnOpen;
    
    UPROPERTY(BlueprintAssignable)
    FOnDoorRequest OnClose;

private:
    // Get mass of Actors on Plate in kg
    float GetMassOfActorsOnPlate();
    
    // Editable ATriggerVolume
    UPROPERTY(EditAnywhere)
    ATriggerVolume* PressurePlate = nullptr;
    
    // Editable PlateTriggerMass
    UPROPERTY(EditAnywhere)
    float PlateTriggerMass = 5.f;
    
//    // Time that last door was opened
//    float LastDoorOpenTime;
//    
//    // Editable property of time that door waits before closing
//    UPROPERTY(EditAnywhere)
//    float DoorCloseTime = 1.f;
    
    // AActor that owns the component OpenDoor
    AActor* Owner = nullptr;
	
};
