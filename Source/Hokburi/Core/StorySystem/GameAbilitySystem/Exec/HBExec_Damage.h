// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "HBExec_Damage.generated.h"

/**
 * 
 */
UCLASS()
class HOKBURI_API UHBExec_Damage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UHBExec_Damage();
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
