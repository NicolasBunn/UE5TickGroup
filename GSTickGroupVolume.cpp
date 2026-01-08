// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/TickGroup/GSTickGroupVolume.h"
#include "Gameplay/TickGroup/GSTickGroupSubsystem.h"
#include "Gameplay/TickGroup/GSTickGroupClientComponent.h"


// Sets default values
AGSTickGroupVolume::AGSTickGroupVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGSTickGroupVolume::BeginPlay()
{
	Super::BeginPlay();
	for (FComponentReference& cmp_ref : _tick_group_cmp_ref)
	{
		UPrimitiveComponent* primitive = Cast<UPrimitiveComponent>(cmp_ref.GetComponent(this));

		if (IsValid(primitive))
		{
			_box_component = Cast<UBoxComponent>(primitive);
			_sphere_component = Cast<USphereComponent>(primitive);
		}
	}
}

// Called every frame
void AGSTickGroupVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGSTickGroupVolume::tryAddActorInVolume(AActor* actor_)
{
	if (isActorIsInside(actor_))
	{
		_actors_in_volume.Add(actor_);
		if (_tick_groupe_volume_is_ticking)
		{
			actor_->SetActorTickEnabled(true);
			actor_->SetActorTickInterval(_tick_rate);
		}
		UGSTickGroupClientComponent* tick_client = actor_->FindComponentByClass<UGSTickGroupClientComponent>();
		if (IsValid(tick_client))
		{
			tick_client->_on_change_tick_rate.Broadcast();
		}
		return true;
	}

	return false;
}

bool AGSTickGroupVolume::isActorIsInside(AActor* actor_)
{
	if (!IsValid(actor_))
	{
		return false;
	}

	FVector actor_loc = actor_->GetActorLocation();
	if (IsValid(_box_component))
	{
		FTransform box_transform = _box_component->GetComponentTransform();
		FVector local_point = box_transform.InverseTransformPosition(actor_loc);

		FVector extend = _box_component->GetScaledBoxExtent();

		return FMath::Abs(local_point.X) <= extend.X
			&& FMath::Abs(local_point.Y) <= extend.Y
			&& FMath::Abs(local_point.Z) <= extend.Z;
	}

	return false;
}


void AGSTickGroupVolume::setActorTickRate(float tick_rate_)
{
	if (tick_rate_ == -1)
	{
		for (AActor* a : _actors_in_volume)
		{
			a->SetActorTickEnabled(false);
			UGSTickGroupClientComponent* tick_client = a->FindComponentByClass<UGSTickGroupClientComponent>();
			if (IsValid(tick_client))
			{
				tick_client->_on_change_tick_rate.Broadcast();
			}
		}
		_tick_groupe_volume_is_ticking = false;
		_tick_rate = -1.0f;
		return;
	}

	_tick_rate = tick_rate_;
	_tick_groupe_volume_is_ticking = true;
	for (AActor* a : _actors_in_volume)
	{
		a->SetActorTickEnabled(true);
		UGSTickGroupClientComponent* tick_client = a->FindComponentByClass<UGSTickGroupClientComponent>();
		a->SetActorTickInterval(_tick_rate);
		if (IsValid(tick_client))
		{
			tick_client->_on_change_tick_rate.Broadcast();
		}
	}
}

TArray<AActor*> AGSTickGroupVolume::checkActorInVolumePosition()
{
	TArray<AActor*> actor_to_move;
	for (AActor* a : _actors_in_volume)
	{
		UGSTickGroupClientComponent* client_comp = a->FindComponentByClass<UGSTickGroupClientComponent>();
		if (!IsValid(client_comp))
		{
			continue;
		}

		if (!client_comp->hasOwnerMoving())
		{
			continue;
		}

		if (isActorIsInside(a))
		{
			continue;
		}

		actor_to_move.Add(a);
	}
	return actor_to_move;
}

void  AGSTickGroupVolume::addNewActorInVolume(AActor* actor_)
{
	actor_->SetActorTickInterval(false);
	actor_->SetActorTickInterval(_tick_rate);
	actor_->SetActorTickEnabled(_tick_groupe_volume_is_ticking);
	UGSTickGroupClientComponent* tick_client = actor_->FindComponentByClass<UGSTickGroupClientComponent>();
	if (IsValid(tick_client))
	{
		tick_client->_on_change_tick_rate.Broadcast();
	}
	_actors_in_volume.Add(actor_);
}

void AGSTickGroupVolume::removeActorInVolume(AActor* actor_)
{
	//UE_LOG(LogTemp, Warning, TEXT("Remove actor %s of %s"), *actor_->GetName(), *GetName());
	actor_->SetActorTickInterval(false);
	UGSTickGroupClientComponent* tick_client = actor_->FindComponentByClass<UGSTickGroupClientComponent>();
	if (IsValid(tick_client))
	{
		tick_client->_on_change_tick_rate.Broadcast();
	}
	_actors_in_volume.Remove(actor_);
}