// Copyright Craig O'Donnell 2017

#include "EscapeTheRoom.h"
#include "Grabber.h"

#define OUT

// MARK: Constructor

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


// MARK: Begin and Hotloop

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
    GetPhysicsHandle();
    SetInputComponent();
        
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
 
    if (!PhysicsHandle) { return; }
    // Set location of grabbed object
    if (PhysicsHandle->GrabbedComponent)
    {
        PhysicsHandle->SetTargetLocation(GetEndOfReachVector());
    }
}


// MARK: Private Methods

// Get Physics Handle from owning actor(s) of Grabber
void UGrabber::GetPhysicsHandle()
{
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if (PhysicsHandle == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Please attach a Physics Handle component to %s."), *GetOwner()->GetName());
    }
}


// Get Input Component from owning actor(s) of Grabber
void UGrabber::SetInputComponent()
{
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if (InputComponent)
    {
        // Bind Grab input Pressed and Released to functions
        InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
        InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("No InputComponent on %s."), *GetOwner()->GetName());
    }
}


// Grab method
void UGrabber::Grab()
{
    // Line trace and see if we reach actors with physics body collision channel set
    auto HitResult = GetFirstPhysicsBodyInReach(); // gets first physics body hit
    auto ComponentToGrab = HitResult.GetComponent(); // this gets mesh hit
    auto ActorHit = HitResult.GetActor(); // this gets the actor hit
    
    // If hit, attach physics handle
    if (ActorHit)
    {
        if (!PhysicsHandle) { return; }
        PhysicsHandle->GrabComponent(
                                     ComponentToGrab, // what to grab
                                     NAME_None, // if skeletal
                                     ComponentToGrab->GetOwner()->GetActorLocation(), // where to grab
                                     true // allow rotation
                                     );
    }
}


// Release method
void UGrabber::Release()
{
    if (!PhysicsHandle) { return; }
    // Release physics handle
    PhysicsHandle->ReleaseComponent();
}


// Get the first Physics Body that is in the Reach
const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
    // Line-trace (ray-cast) out to reach distance
    FHitResult HitResult;
    // Setup query parameters
    FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
    GetWorld()->LineTraceSingleByObjectType(
                                            OUT HitResult,
                                            GetStartOfReachVector(),
                                            GetEndOfReachVector(),
                                            FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
                                            TraceParameters
                                            );
    
    return HitResult;
}


// Gets the START of the Reach vector
FVector UGrabber::GetStartOfReachVector()
{
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    
    // Gets first player in the world's ViewPoint
    // GetPlayerViewPoint() returns out values (modified parameters)
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
                                                               OUT PlayerViewPointLocation,
                                                               OUT PlayerViewPointRotation
                                                               );
    
    return PlayerViewPointLocation;
}


// Gets the END of the Reach vector
FVector UGrabber::GetEndOfReachVector()
{
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    
    // Gets first player in the world's ViewPoint
    // GetPlayerViewPoint() returns out values (modified parameters)
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
                                                               OUT PlayerViewPointLocation,
                                                               OUT PlayerViewPointRotation
                                                               );
    
    // b Vector for calculating grab vector
    FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
    
    //    // Draw grab vector (a+b)
    //    DrawDebugLine(
    //        GetWorld(),
    //        PlayerViewPointLocation, // a
    //        LineTraceEnd, // b
    //        FColor(255, 0, 0),
    //        false,
    //        0.f,
    //        0.f,
    //        20.f
    //    );

    return LineTraceEnd;
}

