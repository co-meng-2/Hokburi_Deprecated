// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "HBCalc_Damage.generated.h"

/**
 * 
 */
UCLASS()
class HOKBURI_API UHBCalc_Damage : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UHBCalc_Damage();
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

public:
	FGameplayEffectAttributeCaptureDefinition AttackPointDef;
};

UCLASS()
class HOKBURI_API UHBCalc_ApplyDamage : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UHBCalc_ApplyDamage();
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

public:
	FGameplayEffectAttributeCaptureDefinition HealthDef;
};
