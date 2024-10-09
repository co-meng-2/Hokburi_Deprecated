// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "Character/HBCharacterBase.h"
#include "HBGameAbilityCharacter.generated.h"

/**
 * 
 */
UCLASS()
class HOKBURI_API AHBGameAbilityCharacter : public AHBCharacterBase
{
	GENERATED_BODY()

public:
	TMap<FName, FGameplayAbilitySpecHandle> GASpecHandleMap;

	bool TryActivateAbility(const FName& AbiltiyNameKey);
};
