// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Components/HBPlayerWidgetComponent.h"

#include "Blueprint/UserWidget.h"
#include "Player/Widget/HBPlayerWidget.h"

void UHBPlayerWidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	// PlayerController로 옮겨줘야 하나 고민..
	Widget = CreateWidget<UHBPlayerWidget, UWorld*>(GetWorld(), Widget->GetClass());

	Widget->OwnerComponent = this;
	Widget->AddToViewport();
}

FOnAttributeChangedDelegate* UHBPlayerWidgetComponent::GetAttChangeDelegate(FGameplayAttribute Attribute)
{
	auto ASC = Cast<UHBAbilitySystemComponent>(GetOwner()->GetComponentByClass(UHBAbilitySystemComponent::StaticClass()));
	const UHBAttributeSetBase* AttSetClass = Cast<UHBAttributeSetBase>(ASC->GetAttributeSet(Attribute.GetAttributeSetClass()));
	return const_cast<UHBAttributeSetBase*>(AttSetClass)->GetChangedDelegate(Attribute);
}

FOnStoryChangeDelegate* UHBPlayerWidgetComponent::GetStoryChangeDelegate()
{
	return &Cast<AHBPlayerCharacter>(GetOwner())->OnStoryChangeDelegate;
}
