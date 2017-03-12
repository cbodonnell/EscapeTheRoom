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
        OpenDoor();
        LastDoorOpenTime = GetWorld()->GetTimeSeconds();
    }
    
    // Checks if it is time to close the door
    if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime >= DoorCloseTime)
    {
        CloseDoor();
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
        UE_LOG(LogTemp, Warning,
               TEXT("%s is on the Pressure Plate."), *Actor->GetName());
    }
    
    return TotalMass;
}


// Opens the door object
void UOpenDoor::OpenDoor()
{
    
    // Create a new FRotator
    FRotator NewRotation = FRotator(0.0f, OpenAngle, 0.0f);
    
    // Set actor's rotation
    Owner->SetActorRotation(NewRotation);
}


// Closes the door object
void UOpenDoor::CloseDoor()
{
    
    // Create a new FRotator
    FRotator NewRotation = FRotator(0.0f, 0.0f, 0.0f);
    
    // Set actor's rotation
    Owner->SetActorRotation(NewRotation);
}
