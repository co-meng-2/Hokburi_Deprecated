// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/StorySystem/GameAbilitySystem/HBAttributeSets.h"
#include "Player/HBPlayerCharacter.h"
#include "Core/StorySystem/GameAbilitySystem/HBAbilitySystemComponent.h"
#include "Core/Widget/HBUserWidgetBase.h"
#include "Core/Widget/ContentWidget/HBButtons.h"
#include "HBPlayerWidget.generated.h"

class UHBProgressBar;
class UHBStoryChoicePopUpUI;
class UHBStatusUI;
class UHBStoryButtonUI;
class UHBUserWidgetBase;
class UVerticalBox;
struct FHBStoryTableRow;
class UHBPlayerWidgetComponent;
class UProgressBar;
class UButton;
class UTextBlock;
/**
 * 
 */

UCLASS()
class HOKBURI_API UHBPlayerWidget : public UHBUserWidgetBase
{
	GENERATED_BODY()

	// Story UI
public:
	UPROPERTY(meta=(BindWidget))
	UHBStoryButtonUI* StoryButtonUI;

	// Attribute UI
public:
	UPROPERTY(meta = (BindWidget))
	UHBStatusUI* StatusUI;

	// Popup UI
public:
	UPROPERTY(meta = (BindWidget))
	UHBStoryChoicePopUpUI* StoryChoicePopUpUI;
};

UCLASS()
class UHBStatusUI : public UHBUserWidgetBase
{
	GENERATED_BODY()

public:
	virtual void BindDelegate() override;
	virtual void Init() override;

public:
	UPROPERTY(meta = (BindWidget))
	UHBProgressBar* HPBar;
	UPROPERTY(meta = (BindWidget))
	UHBProgressBar* MPBar;

	FOnAttributeChangedDelegate* RequestAttChangeDelegate(const FGameplayAttribute& Attribute);
	void BindHPBarDelegate();
};

UCLASS()
class HOKBURI_API UHBStoryButton : public UButton
{
	GENERATED_BODY()

public:
	EStoryMappingKey::Key EStoryMappingKey;
	int StoryLevel;
	FString StoryContent;

	UFUNCTION()
	void UpdatePopUp();
};

UCLASS()
class UHBStoryButtonUI : public UHBUserWidgetBase
{
	GENERATED_BODY()

public:

	virtual void PreInit() override;
	virtual void Init() override;
	virtual void BindDelegate() override;
	

public:
	UPROPERTY(meta = (BindWidget))
	UHBStoryButton* Button_StoryE;
	UPROPERTY(meta = (BindWidget))
	UHBStoryButton* Button_StoryR;
	UPROPERTY(meta = (BindWidget))
	UHBStoryButton* Button_StoryD;
	UPROPERTY(meta = (BindWidget))
	UHBStoryButton* Button_StoryF;
	UPROPERTY(meta = (BindWidget))
	UHBStoryButton* Button_StoryC;
	UPROPERTY(meta = (BindWidget))
	UHBStoryButton* Button_StoryV;

	TMap<EStoryMappingKey::Key, UHBStoryButton*> ButtonMap;
	void InitButtonMap();

	void BindOnClickedDelegate();

	const TArray<UHBStory*>& RequestStoryArray();
	FOnStoryChangeDelegate* RequestStoryChangeDelegate();
	void BindStoryChangeDelegate();
	UFUNCTION()
	void UpdateButton(EStoryMappingKey::Key EStoryMappingKey, FHBStoryTableRow& StoryInfo);
};

UCLASS()
class UHBStoryChoicePopUpUIButton : public UButton
{
	GENERATED_BODY()

public:
	UHBStoryChoicePopUpUIButton();

public:
	int ButtonIdx;

	UFUNCTION()
	void GiveStory();
};

UCLASS()
class HOKBURI_API UHBStoryChoicePopUpUI : public UHBMovableUserWidget
{
	GENERATED_BODY()
public:
	virtual void PreInit() override;

public:
	UPROPERTY()
	TArray<UHBStoryChoicePopUpUIButton*> StoryChoiceButtons;
	TArray<UTextBlock*> StoryButtonNames;
	TArray<TArray<FHBStoryTableRow*>> CachedChoices;

	UPROPERTY(EditDefaultsOnly)
	uint8 ButtonCount = 3;

	UPROPERTY(EditDefaultsOnly)
	FVector2D MarginHV = {5.f, 5.f};

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* ButtonContainer;

	void CreateChoiceButtons();
	void UpdateChoiceButtons(int StoryLevel, EStoryMappingKey::Key EStoryMappingKey);

	EStoryMappingKey::Key CachedStoryContext;
};





