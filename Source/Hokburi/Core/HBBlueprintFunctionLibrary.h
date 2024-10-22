// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HBBlueprintFunctionLibrary.generated.h"

struct FGameplayAttribute;
class FOnAttributeChangedDelegate;
class UHBAttributeSetBase;
class UWidget;
/**
 * 
 */
UCLASS()
class HOKBURI_API UHBWidgetBFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static UUserWidget* FindRootUserWidget(UWidget* Widget);
	static UUserWidget* FindUserWidget(UWidget* Widget);
	static UActorComponent* FindOwnerComponent(UWidget* Widget);
};

UCLASS()
class HOKBURI_API UHBGameAbilitySystemBFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static FOnAttributeChangedDelegate* GetAttChangeDelegate(AActor* ActorWithASC, const FGameplayAttribute& Attribute);
	static UHBAttributeSetBase* GetAttSet(AActor* ActorWithASC, const FGameplayAttribute& Attribute);
	template<typename AttSetClass>
	static AttSetClass* GetAttSet(AActor* ActorWithASC, const FGameplayAttribute& Attribute)
	{
		return Cast<AttSetClass>(GetAttSet(ActorWithASC, Attribute));
	}
	
};

UCLASS()
class HOKBURI_API UHBUtilityBFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static bool IsRotationDifferenceSmall(const FRotator& RotationA, const FRotator& RotationB, float ThresholdDegrees);
};

