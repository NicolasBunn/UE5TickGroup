// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/BoxComponent.h>
#include <Components/SphereComponent.h>
#include "GSTickGroupVolume.generated.h"

UCLASS()
class GAMESTARTER_API AGSTickGroupVolume : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY();
	TArray<AActor*> _actors_in_volume;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true", UseComponentPicker, AllowedClasses = "PrimitiveComponent"))
	TArray<FComponentReference> _tick_group_cmp_ref;

	//UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	//TArray<TObjectPtr<UPrimitiveComponent> > _tick_group_primitive_components;

	UPROPERTY();
	TObjectPtr<USphereComponent> _sphere_component;

	UPROPERTY();
	TObjectPtr<UBoxComponent> _box_component;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float _tick_rate = 0.0f;

	bool _tick_groupe_volume_is_ticking = false;


	// Sets default values for this actor's properties
	AGSTickGroupVolume();

	bool tryAddActorInVolume(AActor* actor_);

	bool isActorIsInside(AActor* actor_);
	void setActorTickRate(float tick_rate_);
	void addNewActorInVolume(AActor* actor_);
	TArray<AActor*> checkActorInVolumePosition();
	void removeActorInVolume(AActor* actor_);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
