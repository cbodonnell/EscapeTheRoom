// Copyright Craig O'Donnell 2017

#include "EscapeTheRoom.h"
#include "OpenDoor.h"

#define OUT

// MARK: Constructor

// Sets default values for this component's properties (INITIALIZER)
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// MARK: Begin and Hotloop

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
    
    // Find AActor(s) owning OpenDoor component
    Owner = GetOwner();
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

    // Checks if actor that triggers OpenDoor() is overlapping the PressurePlate and then runs OpenDoor()
    if (GetMassOfActorsOnPlate() > PlateTriggerMass)
    {
        // Broadcasting the OnOpen event
        OnOpen.Broadcast();
    }
    
    // Checks if it is time to close the door
    else
    {
        OnClose.Broadcast();
    }
}


// MARK: Private Methods

// Gets mass of all actors in the trigger volume
float UOpenDoor::GetMassOfActorsOnPlate()
{
    float TotalMass = 0.f;
    
    TArray<AActor*> OverlappingActors;
    PressurePlate->GetOverlappingActors(OUT OverlappingActors);
    
    for (const auto* Actor: OverlappingActors) {
        TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
    }
    
    return TotalMass;
}
