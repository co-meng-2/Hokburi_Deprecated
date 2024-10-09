// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/StorySystem/GameAbilitySystem/HBGameplayAbility.h"

#include "HBAbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "GameEffectContainer/HBTargetType.h"



TArray<FActiveGameplayEffectHandle> UHBGameplayAbility::ApplyEffectContainer(FGameplayTag ContainerTag,
	const FGameplayEventData& EventData, int32 OverrideLevel)
{
	FHBGameplayEffectContainerSpec Spec = MakeEffectContainerSpec(ContainerTag, EventData, OverrideLevel);
	return ApplyEffectContainerSpec(Spec);
}

FHBGameplayEffectContainerSpec UHBGameplayAbility::MakeEffectContainerSpec(FGameplayTag ContainerTag,
	const FGameplayEventData& EventData, int32 OverrideLevel)
{
	FHBGameplayEffectContainer* FoundContainer = EffectContainerMap.Find(ContainerTag);

	if (FoundContainer)
	{
		return MakeEffectContainerSpecFromContainer(*FoundContainer, EventData, OverrideLevel);
	}

	return FHBGameplayEffectContainerSpec();
}

FHBGameplayEffectContainerSpec UHBGameplayAbility::MakeEffectContainerSpecFromContainer(
	const FHBGameplayEffectContainer& Container, const FGameplayEventData& EventData, int32 OverrideLevel)
{
	FHBGameplayEffectContainerSpec ReturnSpec;
	AActor* OwningActor = GetOwningActorFromActorInfo();
	UHBAbilitySystemComponent* OwningASC = Cast<UHBAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OwningActor));

	if(OwningASC)
	{
		if(Container.TargetType.Get())
		{
			TArray<FHitResult> HitResults;
			TArray<AActor*> TargetActors;
			const UHBTargetType* TargetTypeCDO = Container.TargetType.GetDefaultObject();
			TargetTypeCDO->GetTargets(OwningActor, EventData, HitResults, TargetActors);
			ReturnSpec.AddTargets(HitResults, TargetActors);
		}

		if (OverrideLevel == -1)
			OverrideLevel = this->GetAbilityLevel();

		for(const TSubclassOf<UGameplayEffect>& EffectClass : Container.TargetGameplayEffectClasses)
		{
			ReturnSpec.TargetGameplayEffectSpecs.Add(MakeOutgoingGameplayEffectSpec(EffectClass, OverrideLevel));
		}
	}

	return ReturnSpec;
}

TArray<FActiveGameplayEffectHandle> UHBGameplayAbility::ApplyEffectContainerSpec(
	const FHBGameplayEffectContainerSpec& ContainerSpec)
{
	TArray<FActiveGameplayEffectHandle> AllEffects;

	for (const FGameplayEffectSpecHandle& SpecHandle : ContainerSpec.TargetGameplayEffectSpecs)
	{
		AllEffects.Append(K2_ApplyGameplayEffectSpecToTarget(SpecHandle, ContainerSpec.TargetDataHandle));
	}

	return AllEffects;
}

void UHBGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,   
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	auto ASC = Cast<UHBAbilitySystemComponent>(ActorInfo->AbilitySystemComponent);
	if(bRemoveOnEnd)
		ASC->SetRemoveAbilityOnEnd(Handle);

	// BP 부분
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UHBGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UHBGameplayAbility::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	auto ASC = Cast<UHBAbilitySystemComponent>(ActorInfo->AbilitySystemComponent);
	ASC->RemoveActiveGEFromAbilitySpec(Spec.Handle);
	// Instancing Policy에 따라서 달라져야 할듯.
	Super::OnRemoveAbility(ActorInfo, Spec);
}
