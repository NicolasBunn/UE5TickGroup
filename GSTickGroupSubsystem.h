// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GSTickGroupSubsystem.generated.h"


class AGSTickGroupVolume;
class AGSPlayerCharacter;
class UGSTickGroupSolver;

UCLASS()
class GAMESTARTER_API UGSTickGroupSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:


	UPROPERTY()
	TArray<AGSTickGroupVolume*> _tickgroup_volume;

	UPROPERTY()
	TArray<AActor*> _tick_actors;

	UPROPERTY()
	UGSTickGroupSolver* _tick_group_solver;

	UPROPERTY()
	TSubclassOf<UGSTickGroupSolver> _tick_group_solver_instance;

	bool _is_tickable = false;

	bool _use_linear_tick_group = true;
	bool _use_grid_tick_group = false;

	void OnWorldBeginPlay(UWorld& InWorld) override;
	virtual TStatId GetStatId() const override;
	virtual bool IsTickable() const override;
	virtual bool IsTickableInEditor() const override;
	virtual bool IsTickableWhenPaused() const override;
	//virtual void Deinitialize() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void addTickGroupVolume(AGSTickGroupVolume* volume_);
	void addTickActor(AActor* actor_);
	void computePlayerVolumePositionVolume(AGSPlayerCharacter* player_);
	void updataTickActorInNewVolume(const TArray<AActor*>& to_move_, int32 current_id_, int32 new_ind_);


};
