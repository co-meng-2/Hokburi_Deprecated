// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameEffectContainer/HBGameplayEffectContainer.h"
#include "HBGameplayAbility.generated.h"


/**
 * 어떻게 시작 될 것인지에 대한 책임을 가진다.
 * 상속받은 클래스들은 Activate - End 까지의 상황에 대한 책임을 진다.
 */
UCLASS(Blueprintable)
class HOKBURI_API UHBGameplayAbility : public UGameplayAbility 
{
	GENERATED_BODY()

	// GEContainer
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hokburi | GameplayEffects")
	TMap<FGameplayTag, FHBGameplayEffectContainer> EffectContainerMap;
	
	UFUNCTION(BlueprintCallable, Category = "Hokburi | Ability")
	virtual TArray<FActiveGameplayEffectHandle> ApplyEffectContainerSpec(const FHBGameplayEffectContainerSpec& ContainerSpec);

	UFUNCTION(BlueprintCallable, Category = "Hokburi | Ability", meta = (AutoCreateRefTerm = "EventData"))
	virtual TArray<FActiveGameplayEffectHandle> ApplyEffectContainer(FGameplayTag ContainerTag, const FGameplayEventData& EventData, int32 OverrideLevel = -1);

	UFUNCTION(BlueprintCallable, Category = "Hokburi | Ability", meta = (AutoCreateRefTerm = "EventData"))
	virtual FHBGameplayEffectContainerSpec MakeEffectContainerSpecFromContainer(const FHBGameplayEffectContainer& Container, const FGameplayEventData& EventData, int32 OverrideLevel = -1);

	UFUNCTION(BlueprintCallable, Category = "Hokburi | Ability", meta = (AutoCreateRefTerm = "EventData"))
	virtual FHBGameplayEffectContainerSpec MakeEffectContainerSpec(FGameplayTag ContainerTag, const FGameplayEventData& EventData, int32 OverrideLevel = -1);

	// 
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hokburi | Policy")
	bool bUseInput = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hokburi | Policy")
	bool bRemoveOnEnd = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hokburi | Policy")
	bool bPermanent = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag PersistentTag; // 합동기 전용 유지되는 Tag

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	virtual void OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

public:
	UFUNCTION(BlueprintCallable)
	FGameplayAbilitySpecHandle GetHandle() { return GetCurrentAbilitySpecHandle(); };
};