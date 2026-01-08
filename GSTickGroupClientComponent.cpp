// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/TickGroup/GSTickGroupClientComponent.h"
#include "Gameplay/TickGroup/GSTickGroupSubsystem.h"


// Sets default values for this component's properties
UGSTickGroupClientComponent::UGSTickGroupClientComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGSTickGroupClientComponent::BeginPlay()
{
	Super::BeginPlay();

	if (UGSTickGroupSubsystem* sub = GetWorld()->GetSubsystem<UGSTickGroupSubsystem>())
	{
		if (IsValid(GetOwner()))
		{
			sub->addTickActor(GetOwner());
		}
	}
	
}


// Called every frame
void UGSTickGroupClientComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

bool UGSTickGroupClientComponent::hasOwnerMoving()
{
	double dist = FVector::DistSquared(_previous_location, GetOwner()->GetActorLocation());

	return dist > 0.0f;
}

