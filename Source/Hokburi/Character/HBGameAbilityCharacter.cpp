// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HBGameAbilityCharacter.h"

#include "Core/StorySystem/GameAbilitySystem/HBAbilitySystemComponent.h"

bool AHBGameAbilityCharacter::TryActivateAbility(const FName& AbilityNameKey)
{
	if(auto GASpec = GASpecHandleMap.Find(AbilityNameKey))
	{
		return ASC->TryActivateAbility(*GASpec, false);
	}
	return false;
}
