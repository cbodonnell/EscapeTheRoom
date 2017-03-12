// Copyright Craig O'Donnell 2017

#include "EscapeTheRoom.h"
#include "OpenDoor.h"


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
    
    // Sets actor that triggers OpenDoor() to the Pawn controlled by the First Player in the World.
    ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
    
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

    // Checks if actor that triggers OpenDoor() is overlapping the PressurePlate and then runs OpenDoor()
    if (PressurePlate->IsOverlappingActor(ActorThatOpens))
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
