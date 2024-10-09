// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/StorySystem/GameAbilitySystem/GameEffectContainer/HBTargetType.h"

#include "Abilities/GameplayAbilityTypes.h"

void UHBTargetType::GetTargets_Implementation(AActor* Avatar, FGameplayEventData EventData,
	TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const
{
}

void UHBTargetType_UseOwner::GetTargets_Implementation(AActor* Avatar, FGameplayEventData EventData,
                                                       TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const
{
	OutActors.Add(Avatar);
}

void UHBTargetType_UseEventData::GetTargets_Implementation(AActor* Avatar, FGameplayEventData EventData,
	TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const
{
	const FHitResult* FoundHitResult = EventData.ContextHandle.GetHitResult();
	if(FoundHitResult)
	{
		OutHitResults.Add(*FoundHitResult);
	}
	else if(EventData.Target)
	{
		OutActors.Add(const_cast<AActor*>(ToRawPtr(EventData.Target)));
	}
}
