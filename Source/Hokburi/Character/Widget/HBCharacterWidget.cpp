// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Widget/HBCharacterWidget.h"

#include "AttributeSet.h"
#include "Character/Components/HBCharacterWidgetComponent.h"
#include "Components/WidgetComponent.h"
#include "Core/HBBlueprintFunctionLibrary.h"	
#include "Core/StorySystem/GameAbilitySystem/HBAttributeSets.h"
#include "Core/Widget/HBUserWidgetBase.h"
#include "Core/Widget/Widget/HBProgressBar.h"


void UHBHPBarUI::Init()
{
	Super::Init();
	auto Character = UHBWidgetBFL::FindOwnerComponent(this)->GetOwner();
	auto AttSetHealth = UHBGameAbilitySystemBFL::GetAttSet<UHBHealthAttributeSet>(Character, UHBHealthAttributeSet::GetMaxHealthAttribute());
	HPBar->Init(AttSetHealth->GetHealth(), AttSetHealth->GetMaxHealth());
}

void UHBHPBarUI::BindDelegate()
{
	Super::BindDelegate();
	auto HPDelegate = RequestAttChangeDelegate(UHBHealthAttributeSet::GetHealthAttribute());
	auto MaxHPDelegate = RequestAttChangeDelegate(UHBHealthAttributeSet::GetHealthAttribute());
	HPDelegate->AddDynamic(HPBar, &UHBProgressBar::UpdateCur);
	MaxHPDelegate->AddDynamic(HPBar, &UHBProgressBar::UpdateMax);
}

FOnAttributeChangedDelegate* UHBHPBarUI::RequestAttChangeDelegate(const FGameplayAttribute& Attribute)
{
	auto Character = UHBWidgetBFL::FindOwnerComponent(this)->GetOwner();
	return UHBGameAbilitySystemBFL::GetAttChangeDelegate(Character, Attribute);
}


