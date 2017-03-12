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


// MARK: Begin Play
// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
    GetPhysicsHandle();
    SetInputComponent();
        
}


// MARK: Every Frame
// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
    
}


// MARK: Methods
// Get Physics Handle from owning actor(s) of Grabber
void UGrabber::GetPhysicsHandle() {
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if (PhysicsHandle) {
        
    }
    else {
        UE_LOG(LogTemp, Error, TEXT("Please attach a Physics Handle component to %s."), *GetOwner()->GetName());
    }
}

// Get Input Component from owning actor(s) of Grabber
void UGrabber::SetInputComponent() {
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if (InputComponent) {
        UE_LOG(LogTemp, Warning, TEXT("InputComponent on %s."), *GetOwner()->GetName());
        
        // Bind Grab input Pressed and Released to functions
        InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
        InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
    }
    else {
        UE_LOG(LogTemp, Error, TEXT("No InputComponent on %s."), *GetOwner()->GetName());
    }
}

// Get the first Physics Body that is in the Reach
const FHitResult UGrabber::GetFirstPhysicsBodyInReach() {
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
    
    // Setup query parameters
    FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
    
    // Line-trace (ray-cast) out to reach distance
    FHitResult Hit;
    GetWorld()->LineTraceSingleByObjectType(
                                            OUT Hit, PlayerViewPointLocation,
                                            LineTraceEnd,
                                            FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
                                            TraceParameters
                                            );
    
    // See what we hit
    AActor* ActorHit = Hit.GetActor();
    if (ActorHit) {
        UE_LOG(LogTemp, Warning, TEXT("Collided with: %s"), *(ActorHit->GetName()));
    }
    
    return FHitResult();
}

// Grab method
void UGrabber::Grab() {
    UE_LOG(LogTemp, Warning, TEXT("Grab pressed!"));
    
    // Line trace and see if we reach actors with physics body collision channel set
    GetFirstPhysicsBodyInReach();
    
    // If hit, attach physics handle
}

// Release method
void UGrabber::Release() {
    UE_LOG(LogTemp, Warning, TEXT("Released!"));
    
    // Release physics handle
}

