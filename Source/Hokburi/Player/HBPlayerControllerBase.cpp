// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/HBPlayerControllerBase.h"

#include "EnhancedInputSubsystems.h"

AHBPlayerControllerBase::AHBPlayerControllerBase()
{
	bShowMouseCursor = true;
}

void AHBPlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();
	UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	EnhancedInputSubsystem->AddMappingContext(IMC, 0);
}
