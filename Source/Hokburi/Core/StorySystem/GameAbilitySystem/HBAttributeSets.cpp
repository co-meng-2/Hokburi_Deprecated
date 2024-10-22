// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/StorySystem/GameAbilitySystem/HBAttributeSets.h"


void UHBAttributeSetBase::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	UE_LOG(LogTemp, Warning, TEXT("PostAttChange : Old %f  New %f"), OldValue, NewValue);

	if (AttributeChangedDelegateMap.Find(Attribute))
	{
		AttributeChangedDelegateMap.Find(Attribute)->Broadcast(NewValue);
	}
}
