// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/HBBlueprintFunctionLibrary.h"

#include "Blueprint/WidgetTree.h"
#include "Components/PanelWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Player/HBPlayerCharacter.h"
#include "Player/HBPlayerControllerBase.h"
#include "StorySystem/GameAbilitySystem/HBAbilitySystemComponent.h"
#include "StorySystem/GameAbilitySystem/HBAttributeSets.h"
#include "Widget/HBUserWidgetBase.h"


UUserWidget* UHBWidgetBFL::FindRootUserWidget(UWidget* Widget)
{
    UWidget* CurWidget = Widget;

    while (CurWidget)
    {
        CurWidget = FindUserWidget(CurWidget);
        UUserWidget* UserWidget = Cast<UUserWidget>(CurWidget);
        if (UserWidget && UserWidget->GetParent() == nullptr)
            return UserWidget;
    }

    return nullptr;
}

UUserWidget* UHBWidgetBFL::FindUserWidget(UWidget* Widget)
{
    UWidget* CurWidget = Widget;
    while (CurWidget)
    {
        UPanelWidget* ParentWidget = CurWidget->GetParent();
        if (ParentWidget == nullptr)
        {
            UWidgetTree* CurWidgetTree = Cast<UWidgetTree>(CurWidget->GetOuter());
            return Cast<UUserWidget>(CurWidgetTree->GetOuter());
        }
        CurWidget = ParentWidget;
    }
    return nullptr;
}

UActorComponent* UHBWidgetBFL::FindOwnerComponent(UWidget* Widget)
{
    auto RootUserWidget = FindRootUserWidget(Widget);
    return Cast<UHBUserWidgetBase>(RootUserWidget)->OwnerComponent.Get();
}

UHBAttributeSetBase* UHBGameAbilitySystemBFL::GetAttSet(AActor* ActorWithASC, const FGameplayAttribute& Attribute)
{
    // IAbilityInterface를 구현하는 Actor와 아닌 Actor를 처리해주어야 한다.
    UAbilitySystemComponent* ASC = nullptr;
    if (!ActorWithASC->Implements<UAbilitySystemInterface>())
    {
        ASC = ActorWithASC->GetComponentByClass<UHBAbilitySystemComponent>();
    }
    else
    {
        ASC = Cast<IAbilitySystemInterface>(ActorWithASC)->GetAbilitySystemComponent();
    }

    auto AttributeSet = Cast<UHBAttributeSetBase>(ASC->GetAttributeSet(Attribute.GetAttributeSetClass()));
    return const_cast<UHBAttributeSetBase*>(AttributeSet);
}

FOnAttributeChangedDelegate* UHBGameAbilitySystemBFL::GetAttChangeDelegate(AActor* ActorWithASC, const FGameplayAttribute& Attribute)
{
    auto AttSetClass = GetAttSet(ActorWithASC, Attribute);
    return AttSetClass->GetChangedDelegate(Attribute);
}