// Copyright Craig O'Donnell 2017

#include "EscapeTheRoom.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));
	
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    
    // Gets first player in the world's ViewPoint
    // GetPlayerViewPoint() returns out values (modified parameters)
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
                                                               OUT PlayerViewPointLocation,
                                                               OUT PlayerViewPointRotation
                                                               );
    
    // Log Location and Rotation of ViewPoint
//    UE_LOG(LogTemp, Warning, TEXT("ViewPoint Location: %s, ViewPoint Rotation: %s"),
//           *PlayerViewPointLocation.ToString(),
//           *PlayerViewPointRotation.ToString()
//           );
    
    // b Vector for calculating grab vector
    FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
    
    // Draw grab vector (a+b)
    DrawDebugLine(
        GetWorld(),
        PlayerViewPointLocation, // a
        LineTraceEnd, // b
        FColor(255, 0, 0),
        false,
        0.f,
        0.f,
        20.f
    );
    
    
    
}

