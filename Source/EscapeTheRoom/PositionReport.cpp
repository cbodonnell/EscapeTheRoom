// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeTheRoom.h"
#include "PositionReport.h"


// MARK: Constructor

// Sets default values for this component's properties (constructor)
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


// MARK: Begin and Hotloop

// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay(); // inherits from parent classes

    // Prints the name and location of those objects with the PositionReport component
    FString ObjectName = GetOwner()->GetName();
    FString ObjectPos = GetOwner()->GetTransform().GetLocation().ToString();
    UE_LOG(LogTemp, Warning, TEXT("%s is at %s."), *ObjectName, *ObjectPos); // macro to log messages to console
	
}


// Called every frame
void UPositionReport::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

