// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "HBGameplayEffect.generated.h"

/**
 * 
 */
UCLASS()
class HOKBURI_API UHBGameplayEffect : public UGameplayEffect
{
	GENERATED_BODY()

public:
	UPROPERTY()
	bool bIsPermanent = false;
};
