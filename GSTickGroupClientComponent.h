// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GSTickGroupClientComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGSOnChangeTickRate);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMESTARTER_API UGSTickGroupClientComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	FVector _previous_location = FVector::ZeroVector;

	// Sets default values for this component's properties
	UGSTickGroupClientComponent();

	bool hasOwnerMoving();

	UPROPERTY(BlueprintAssignable)
	FGSOnChangeTickRate _on_change_tick_rate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
