// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/HBPlayerState.h"

#include "Components/HBPlayerWidgetComponent.h"
#include "Core/StorySystem/GameAbilitySystem/HBAbilitySystemComponent.h"

AHBPlayerState::AHBPlayerState()
{
	ASC = CreateDefaultSubobject<UHBAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}

UAbilitySystemComponent* AHBPlayerState::GetAbilitySystemComponent() const
{
	return Cast<UHBAbilitySystemComponent>(ASC);
}
