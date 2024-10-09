// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetTypes.h"

#include "HBGameplayEffectContainer.generated.h"

class UGameplayEffect;
class UHBTargetType;

USTRUCT(BlueprintType)
struct FHBGameplayEffectContainer
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hokburi | EffectContainer")
	TSubclassOf<UHBTargetType> TargetType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hokburi | EffectContainer")
	TArray<TSubclassOf<UGameplayEffect>> TargetGameplayEffectClasses;
};

USTRUCT(BlueprintType)
struct FHBGameplayEffectContainerSpec
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hokburi | EffectContainer")
	FGameplayAbilityTargetDataHandle TargetDataHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hokburi | EffectContainer")
	TArray<FGameplayEffectSpecHandle> TargetGameplayEffectSpecs;

	bool HasValidEffects() const;
	bool HasValidTargets() const;

	void AddTargets(const TArray<FHitResult>& HitResults, const TArray<AActor*>& TargetActors);
};
