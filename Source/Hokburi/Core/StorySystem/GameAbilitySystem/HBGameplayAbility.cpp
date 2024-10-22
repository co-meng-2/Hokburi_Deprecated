// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/StorySystem/GameAbilitySystem/HBGameplayAbility.h"

#include "HBAbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "AbilityTask/HBAbilityTasks.h"
#include "GameEffectContainer/HBTargetType.h"

const FGameplayTagContainer* UHBGameplayAbility::GetCooldownTags() const
{
	return &CooldownTag;
}

void UHBGameplayAbility::ApplyCooldown(const FGameplayAbilitySpecHandle Handle,
                                       const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	UGameplayEffect* CoolDownGE = GetCooldownGameplayEffect();
	if(CoolDownGE)
	{
		auto GE_SpecHandle = MakeOutgoingGameplayEffectSpec(CoolDownGE->GetClass());
		GE_SpecHandle.Data.Get()->DynamicGrantedTags.AppendTags(CooldownTag);
		GE_SpecHandle.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("GE.Caller.Cooldown")), CooldownDuration);
		ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, GE_SpecHandle);
	}
}

void UHBGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,   
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                         const FGameplayEventData* TriggerEventData)
{
	auto ASC = Cast<UHBAbilitySystemComponent>(ActorInfo->AbilitySystemComponent);
	if (bRemoveOnEnd)
	{
		ASC->SetRemoveAbilityOnEnd(Handle);
	}

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

void UHBGameplayAbility::EndAbilityWrappedForEventData(FGameplayTag EventTag, FGameplayEventData EventData)
{
	K2_EndAbility();
}

void UHBGameplayAbility_PlayMontage::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                     const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                     const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	//UHBAbilityTask_PlayMontageAndWaitEvent* AT_PlayMontage = UHBAbilityTask_PlayMontageAndWaitEvent::CreatePlayMontage(this, Montage);
	//AT_PlayMontage->OnTaskFinsihDelegate.AddDynamic(this, &ThisClass::EndAbilityWrappedForEventData);
	//AT_PlayMontage->Activate();
}

//TArray<FActiveGameplayEffectHandle> UHBGameplayAbility::ApplyEffectContainer(FGameplayTag ContainerTag,
//	const FGameplayEventData& EventData, int32 OverrideLevel)
//{
//	FHBGameplayEffectContainerSpec Spec = MakeEffectContainerSpec(ContainerTag, EventData, OverrideLevel);
//	return ApplyEffectContainerSpec(Spec);
//}
//
//FHBGameplayEffectContainerSpec UHBGameplayAbility::MakeEffectContainerSpec(FGameplayTag ContainerTag,
//	const FGameplayEventData& EventData, int32 OverrideLevel)
//{
//	FHBGameplayEffectContainer* FoundContainer = EffectContainerMap.Find(ContainerTag);
//
//	if (FoundContainer)
//	{
//		return MakeEffectContainerSpecFromContainer(*FoundContainer, EventData, OverrideLevel);
//	}
//
//	return FHBGameplayEffectContainerSpec();
//}
//
//FHBGameplayEffectContainerSpec UHBGameplayAbility::MakeEffectContainerSpecFromContainer(
//	const FHBGameplayEffectContainer& Container, const FGameplayEventData& EventData, int32 OverrideLevel)
//{
//	FHBGameplayEffectContainerSpec ReturnSpec;
//	AActor* OwningActor = GetOwningActorFromActorInfo();
//	UHBAbilitySystemComponent* OwningASC = Cast<UHBAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OwningActor));
//
//	if (OwningASC)
//	{
//		if (Container.TargetType.Get())
//		{
//			TArray<FHitResult> HitResults;
//			TArray<AActor*> TargetActors;
//			const UHBTargetType* TargetTypeCDO = Container.TargetType.GetDefaultObject();
//			TargetTypeCDO->GetTargets(OwningActor, EventData, HitResults, TargetActors);
//			ReturnSpec.AddTargets(HitResults, TargetActors);
//		}
//
//		if (OverrideLevel == -1)
//			OverrideLevel = this->GetAbilityLevel();
//
//		for (const TSubclassOf<UGameplayEffect>& EffectClass : Container.TargetGameplayEffectClasses)
//		{
//			ReturnSpec.TargetGameplayEffectSpecs.Add(MakeOutgoingGameplayEffectSpec(EffectClass, OverrideLevel));
//		}
//	}
//
//	return ReturnSpec;
//}
//
//TArray<FActiveGameplayEffectHandle> UHBGameplayAbility::ApplyEffectContainerSpec(
//	const FHBGameplayEffectContainerSpec& ContainerSpec)
//{
//	TArray<FActiveGameplayEffectHandle> AllEffects;
//
//	for (const FGameplayEffectSpecHandle& SpecHandle : ContainerSpec.TargetGameplayEffectSpecs)
//	{
//		AllEffects.Append(K2_ApplyGameplayEffectSpecToTarget(SpecHandle, ContainerSpec.TargetDataHandle));
//	}
//
//	return AllEffects;
//}