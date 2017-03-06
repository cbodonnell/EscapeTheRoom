// Copyright Craig O'Donnell 2017

#include "EscapeTheRoom.h"
#include "OpenDoor.h"


// Sets default values for this component's properties (INITIALIZER)
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// METHODS

void UOpenDoor::OpenDoor() {
    
    // Find the owning actor
    AActor* Owner = GetOwner();
    
    // Create a new rotation
    FRotator NewRotation = FRotator(0.0f, OpenAngle, 0.0f);
    
    // Set actor's rotation
    Owner->SetActorRotation(NewRotation);
}


// MAIN FUNCTIONS (functions that run at start of game and every frame)

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
    
    // Sets actor that triggers OpenDoor() to the Pawn controlled by the First Player in the World.
    ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
    
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	//Poll this every frame
    // Checks if actor that triggers OpenDoor() is overlapping the PressurePlate and then runs OpenDoor()
    if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {
        OpenDoor();
    }
}

