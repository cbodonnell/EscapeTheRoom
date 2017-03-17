// Copyright Craig O'Donnell 2017

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenRequest);

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
    
    // Creates an OnOpenRequest event to be broadcast to the blueprint
    UPROPERTY(BlueprintAssignable)
    FOnOpenRequest OnOpenRequest;

private:
    // Get mass of Actors on Plate in kg
    float GetMassOfActorsOnPlate();
    
    // Open door method
    void OpenDoor();
    
    // Close door method
    void CloseDoor();
    
    // Editable ATriggerVolume
    UPROPERTY(EditAnywhere)
    ATriggerVolume* PressurePlate = nullptr;
    
    // Editable PlateTriggerMass
    UPROPERTY(EditAnywhere)
    float PlateTriggerMass = 5.f;
    
    // Read only property of the door's opening angle
    UPROPERTY(EditAnywhere)
    float OpenAngle = -60.0f;
    
    // Time that last door was opened
    float LastDoorOpenTime;
    
    // Editable property of time that door waits before closing
    UPROPERTY(EditAnywhere)
    float DoorCloseTime = 1.f;
    
    // AActor that owns the component OpenDoor
    AActor* Owner = nullptr;
	
};
