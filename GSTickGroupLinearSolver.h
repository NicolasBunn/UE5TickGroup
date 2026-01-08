// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/TickGroup/GSTickGroupSolver.h"
#include "GSTickGroupLinearSolver.generated.h"

UCLASS(Blueprintable, BlueprintType)
class GAMESTARTER_API UGSTickGroupLinearSolver : public UGSTickGroupSolver
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 _numb_volume_active = 0;

	void computePlayerPositionInTickGroupVolume(TArray<AGSTickGroupVolume*> tick_groupe_volume_, AGSPlayerCharacter* player_) override;
	void updateTickGroupeVolumeTickRate(TArray<AGSTickGroupVolume*> tick_groupe_volume_, AGSPlayerCharacter* player_, int new_volume_id_) override;


	
	
};
