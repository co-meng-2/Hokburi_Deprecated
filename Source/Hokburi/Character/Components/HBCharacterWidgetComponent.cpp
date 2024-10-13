// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Components/HBCharacterWidgetComponent.h"

#include "Core/Widget/HBUserWidgetBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/HBPlayerCameraPawn.h"

UHBCharacterWidgetComponent::UHBCharacterWidgetComponent()
{
	// bTickInEditor = false;
}

void UHBCharacterWidgetComponent::InitWidget()
{
	Super::InitWidget();

	if (auto UserWidget = Cast<UHBUserWidgetBase>(GetWidget()))
	{
		UserWidget->OwnerComponent = this;
	}
}

void UHBCharacterWidgetComponent::BeginPlay()
{
	Super::BeginPlay();
	OriginalDrawSize = DrawSize;

	auto PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	auto Camera = Cast<AHBPlayerCameraPawn>(PlayerController->GetPawn());
	AddTickPrerequisiteActor(Camera);
}

void UHBCharacterWidgetComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(auto PlayerController = UGameplayStatics::GetPlayerController(this, 0))
	{
		auto Camera = Cast<AHBPlayerCameraPawn>(PlayerController->GetPawn());
		SetDrawSize(OriginalDrawSize * Camera->MinTargetArmLength / Camera->CameraBoom->TargetArmLength);
	}
}
