// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GSTickGroupSolver.generated.h"

class AGSPlayerCharacter;
class AGSTickGroupVolume;


UCLASS(Blueprintable, BlueprintType,Abstract)
class GAMESTARTER_API UGSTickGroupSolver : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveFloat* _tick_rate_curve;

	virtual void computePlayerPositionInTickGroupVolume(TArray<AGSTickGroupVolume*> tick_groupe_volume_, AGSPlayerCharacter* player_);
	virtual void updateTickGroupeVolumeTickRate(TArray<AGSTickGroupVolume*> tick_groupe_volume_, AGSPlayerCharacter* player_, int new_volume_id_);


	
};
