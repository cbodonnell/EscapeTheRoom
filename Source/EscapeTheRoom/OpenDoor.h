// Copyright Craig O'Donnell 2017

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


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

private:
    void OpenDoor();
    
    // Read only property of the door's opening angle
    UPROPERTY(VisibleAnywhere)
    float OpenAngle = -60.0f;
    
    // Editable ATriggerVolume
    UPROPERTY(EditAnywhere)
    ATriggerVolume* PressurePlate;
    
    // Read only actor that triggers OpenDoor()
    UPROPERTY(VisibleAnywhere)
    AActor* ActorThatOpens; // Pawn inherits this class
	
};
