// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Character/HBGameAbilityCharacter.h"
#include "HBPlayerCharacter.generated.h"

struct FHBStoryTableRow;
class UHBPlayerWidgetComponent;
class UInputAction;
class UHBStory;
/**
 * 
 */

UENUM(BlueprintType)
namespace EStoryMappingKey
{
	enum Key : uint8
	{
		E_Start = 0,
		R,
		D,
		F,
		C,
		V,
		END
	};
}

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStoryChangeDelegate, EStoryMappingKey::Key, EStoryMappingKey, FHBStoryTableRow&, StoryInfo);

UCLASS()
class HOKBURI_API AHBPlayerCharacter : public AHBGameAbilityCharacter
{
	GENERATED_BODY()

public:
	AHBPlayerCharacter(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;

	// Story
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hokburi | Story")
	TArray<UHBStory*> OwningStories;
	FGameplayTagContainer CollectedTag; // 합동기 전용 유지되는 Tag 모음

	UPROPERTY(BlueprintAssignable)
	FOnStoryChangeDelegate OnStoryChangeDelegate;
	void OnStoryChange(EStoryMappingKey::Key EStoryMappingKey, FHBStoryTableRow& StoryInfo);

	// Input
public:
	void ActivateStory(EStoryMappingKey::Key Key);

	// PlayerController
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hokburi | PlayerController")
	AHBPlayerControllerBase* PlayerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hokburi | Component")
	TWeakObjectPtr<UHBAbilitySystemComponent> ASC_MainCharacter;

	// Ability
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
