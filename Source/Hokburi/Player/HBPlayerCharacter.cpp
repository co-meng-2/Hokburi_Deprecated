// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/HBPlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "Components/HBPlayerWidgetComponent.h"
#include "Core/StorySystem/HBStoryManager.h"
#include "Core/StorySystem/GameAbilitySystem/HBAbilitySystemComponent.h"
#include "Widget/HBPlayerWidget.h"

AHBPlayerCharacter::AHBPlayerCharacter()
{
	PlayerWidgetComponent = CreateDefaultSubobject<UHBPlayerWidgetComponent>(FName("PlayerWidgetComponent"));
}

void AHBPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AHBPlayerCharacter::OnStoryChange(EStoryMappingKey::Key EStoryMappingKey, FHBStoryTableRow& StoryInfo)
{
	OnStoryChangeDelegate.Broadcast(EStoryMappingKey, StoryInfo);
}

void AHBPlayerCharacter::ActivateStory(EStoryMappingKey::Key Key)
{
	for(const auto& GASpecHandle : OwningStories[Key]->GASpecHandles)
	{
		if(ASC->TryActivateAbility(GASpecHandle, false))
		{
		}
	}
}
