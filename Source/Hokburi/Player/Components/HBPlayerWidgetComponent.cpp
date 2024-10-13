// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Components/HBPlayerWidgetComponent.h"

#include "Blueprint/UserWidget.h"
#include "Player/HBPlayerControllerBase.h"
#include "Player/HBPlayerState.h"
#include "Player/Widget/HBPlayerWidget.h"


void UHBPlayerWidgetComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void UHBPlayerWidgetComponent::Init()	
{
	auto PlayerController = Cast<AHBPlayerControllerBase>(GetOwner());
	GameWidget = CreateWidget<UHBPlayerWidget, AHBPlayerControllerBase*>(PlayerController, GameWidget->GetClass());
	GameWidget->AddToViewport();
}


FOnStoryChangeDelegate* UHBPlayerWidgetComponent::GetStoryChangeDelegate()
{
	auto PlayerController = Cast<AHBPlayerControllerBase>(GetOwner());
	auto MainCharacter = Cast<AHBPlayerCharacter>(PlayerController->GetMainCharacter());

	return &MainCharacter->OnStoryChangeDelegate;
}

const TArray<UHBStory*>& UHBPlayerWidgetComponent::GetStoryArray()
{
	auto PlayerController = Cast<AHBPlayerControllerBase>(GetOwner());
	auto MainCharacter = Cast<AHBPlayerCharacter>(PlayerController->GetMainCharacter());

	return MainCharacter->OwningStories;
}
