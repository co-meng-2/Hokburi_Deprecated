// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/StorySystem/GameAbilitySystem/HBAbilitySystemComponent.h"

#include "Blueprint/UserWidget.h"
#include "Player/Widget/HBPlayerWidget.h"


void UHBAbilitySystemComponent::InitializeComponent()
{
	Super::InitializeComponent();

	if (GetWorld())
	{
		RegisterAttributes();
		if (GE_InitAttribute == nullptr) return;

		auto InitAttSpecHandle = MakeOutgoingSpec(GE_InitAttribute, 0, MakeEffectContext());
		ApplyGameplayEffectSpecToSelf(*InitAttSpecHandle.Data.Get());
	}
}

void UHBAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UHBAbilitySystemComponent::RegisterAttributes()
{
	for (const TSubclassOf<UAttributeSet>& AttSetClass : OwningAttributeClasses)
	{
		UAttributeSet* NewAttributeSet = NewObject<UAttributeSet>(this, AttSetClass);
		AddAttributeSetSubobject(NewAttributeSet);
	}
}

void UHBAbilitySystemComponent::RemoveActiveGEFromAbilitySpec(const FGameplayAbilitySpecHandle GASpecHandle)
{
	if(FAbilityRelated* Related = GARelatedMap.Find(GASpecHandle))
	{
		for(auto ActiveGEHandle : Related->RelatedActiveGEHandles)
		{
			RemoveActiveGameplayEffect(ActiveGEHandle);
		}

		for(auto Actor : Related->RelatedActors)
		{
			Actor->Destroy();
		}

		GARelatedMap.Remove(GASpecHandle);
	}
}

void UHBAbilitySystemComponent::RegisterGARelatedMap(FGameplayAbilitySpecHandle GASpecHandle, AActor* RelatedActor, FActiveGameplayEffectHandle ActiveGEHandle)
{
	FAbilityRelated& Related = GARelatedMap.FindOrAdd(GASpecHandle);
	if(RelatedActor)
		Related.RelatedActors.Add(RelatedActor);
	if(ActiveGEHandle.IsValid())
		Related.RelatedActiveGEHandles.Add(ActiveGEHandle);
}
