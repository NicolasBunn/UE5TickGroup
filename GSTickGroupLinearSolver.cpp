// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/TickGroup/GSTickGroupLinearSolver.h"
#include "Gameplay/TickGroup/GSTickGroupVolume.h"
#include "Character/Player/GSPlayerCharacter.h"

void UGSTickGroupLinearSolver::computePlayerPositionInTickGroupVolume(TArray<AGSTickGroupVolume*> tick_groupe_volume_, AGSPlayerCharacter* player_)
{
    if (player_->_tick_group_volume_id == -1)
    {
        for (int i = 0; i < tick_groupe_volume_.Num(); i++)
        {
            if (tick_groupe_volume_[i]->isActorIsInside(player_))
            {
                updateTickGroupeVolumeTickRate(tick_groupe_volume_,player_, i);
            }
        }
    }

    if (tick_groupe_volume_[player_->_tick_group_volume_id]->isActorIsInside(player_))
    {
        return;
    }

    int tick_group_volume_id = player_->_tick_group_volume_id - 1;
    for (int i = 0; i < _numb_volume_active; i++)
    {
        if (tick_group_volume_id == tick_groupe_volume_.Num())
        {
            break;
        }

        if (tick_group_volume_id == player_->_tick_group_volume_id || tick_group_volume_id < 0)
        {
            tick_group_volume_id++;
            continue;
        }
        if (tick_groupe_volume_[tick_group_volume_id]->isActorIsInside(player_))
        {
            updateTickGroupeVolumeTickRate(tick_groupe_volume_,player_, tick_group_volume_id);
        }
        tick_group_volume_id++;
    }
}

void UGSTickGroupLinearSolver::updateTickGroupeVolumeTickRate(TArray<AGSTickGroupVolume*> tick_groupe_volume_, AGSPlayerCharacter* player_, int new_volume_id_)
{
    if (new_volume_id_ == -1)
    {
        return;
    }

    int update_tick_group_volume_index = player_->_tick_group_volume_id - 1;
    for (int i = 0; i < _numb_volume_active; i++)
    {
        if (update_tick_group_volume_index == tick_groupe_volume_.Num())
        {
            break;
        }

        if (update_tick_group_volume_index < 0)
        {
            update_tick_group_volume_index++;
            continue;
        }
        tick_groupe_volume_[update_tick_group_volume_index]->setActorTickRate(-1);

        update_tick_group_volume_index++;
    }

    player_->_tick_group_volume_id = new_volume_id_;
    update_tick_group_volume_index = player_->_tick_group_volume_id - 1;
    int32 curve_index = 0;
    for (int32 i = 0; i < _numb_volume_active; i++)
    {
        if (update_tick_group_volume_index == tick_groupe_volume_.Num())
        {
            break;
        }
        if (update_tick_group_volume_index < 0)
        {
            update_tick_group_volume_index++;
            continue;
        }

        if (_tick_rate_curve)
        {
            tick_groupe_volume_[update_tick_group_volume_index]->setActorTickRate(_tick_rate_curve->GetFloatValue(update_tick_group_volume_index - player_->_tick_group_volume_id));
        }

        update_tick_group_volume_index++;
    }
}

