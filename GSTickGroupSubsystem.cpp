// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/TickGroup/GSTickGroupSubsystem.h"
#include "Gameplay/TickGroup/GSTickGroupVolume.h"
#include "Gameplay/TickGroup/GSTickGroupSolver.h"
#include "Character/Player/GSPlayerCharacter.h"
#include "System/GSWorldSettings.h"

void UGSTickGroupSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
    Super::OnWorldBeginPlay(InWorld);

    UWorld* world = GetWorld();
    if (!world)
    {
        return;
    }

    AGSWorldSettings* settings = Cast<AGSWorldSettings>(world->GetWorldSettings());
    if (settings)
    {
        _tick_group_solver = NewObject< UGSTickGroupSolver>(this, settings->_tick_group_solver_instance);
        _tick_group_solver_instance = settings->_tick_group_solver_instance;
    }
}

void UGSTickGroupSubsystem::addTickGroupVolume(AGSTickGroupVolume* volume_)
{
    _tickgroup_volume.Add(volume_);
}

void UGSTickGroupSubsystem::addTickActor(AActor* actor_)
{
    _tick_actors.Add(actor_);
    _is_tickable = true;
}
 
void UGSTickGroupSubsystem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (_tick_actors.Num() > 0)
    {
        TArray<int> _index_to_remove;
        for (int i = 0; i < _tick_actors.Num(); i++)
        {
            for (AGSTickGroupVolume* vol : _tickgroup_volume)
            {
                if (vol->tryAddActorInVolume(_tick_actors[i]))
                {
                    //UE_LOG(LogTemp, Warning, TEXT("%s is inside box %d"), *_tick_actors[i]->GetName(), i);
                    _index_to_remove.Add(i);
                    continue;
                }
            }
        }
        
        for (int i = _index_to_remove.Num() - 1; i >= 0; i--)
        {
            _tick_actors.RemoveAt(_index_to_remove[i]);
        }
        //if (_tick_actors.Num() == 0)
        //{
        //    _is_tickable = false;
        //}
    }

    for (int i = 0; i < _tickgroup_volume.Num(); i++)
    {
        if (!_tickgroup_volume[i]->IsActorTickEnabled())
        {
            continue;
        }

        TArray<AActor*> to_move = _tickgroup_volume[i]->checkActorInVolumePosition();
        if (to_move.Num() == 0)
        {
            continue;
        }

        updataTickActorInNewVolume(to_move, i, i - 1);
        updataTickActorInNewVolume(to_move, i, i + 1);

    }
}

void UGSTickGroupSubsystem::updataTickActorInNewVolume(const TArray<AActor*>& to_move_, int32 current_id_, int32 new_ind_)
{
    int index_to_check = new_ind_;
    if (index_to_check < 0)
    {
        index_to_check = 0;
    }
    else if (index_to_check == _tickgroup_volume.Num())
    {
        index_to_check = _tickgroup_volume.Num() - 1;
    }

    for (AActor* a : to_move_)
    {
        if (_tickgroup_volume[index_to_check]->isActorIsInside(a))
        {
            _tickgroup_volume[current_id_]->removeActorInVolume(a);
            _tickgroup_volume[index_to_check]->addNewActorInVolume(a);
            break;
        }
    }
}



void UGSTickGroupSubsystem::computePlayerVolumePositionVolume(AGSPlayerCharacter* player_)
{
    if (_tick_group_solver)
    {
        _tick_group_solver->computePlayerPositionInTickGroupVolume(_tickgroup_volume, player_);
    }
}

TStatId UGSTickGroupSubsystem::GetStatId() const
{
    return TStatId();
}

bool UGSTickGroupSubsystem::IsTickable() const
{
    return _is_tickable;
}

bool UGSTickGroupSubsystem::IsTickableInEditor() const
{
    return false;
}

bool UGSTickGroupSubsystem::IsTickableWhenPaused() const
{
    return false;
}