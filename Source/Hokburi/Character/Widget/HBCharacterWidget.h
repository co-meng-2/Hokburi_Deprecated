// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Core/Widget/HBUserWidgetBase.h"
#include "Core/Widget/Widget/HBProgressBar.h"
#include "HBCharacterWidget.generated.h"

class UHBProgressBar;
struct FGameplayAttribute;
class FOnAttributeChangedDelegate;
class UHBHPBarUI;
/**
 * 
 */

UCLASS()
class HOKBURI_API UHBCharacterWidget : public UHBUserWidgetBase
{
	GENERATED_BODY()

public:
	UPROPERTY( meta=(BindWidget) )
	UHBHPBarUI* HPBarUI;
};

UCLASS()
class UHBHPBarUI : public UHBUserWidgetBase
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void BindDelegate() override;

	UPROPERTY(meta = (BindWidget))
	UHBProgressBar* HPBar;

	FOnAttributeChangedDelegate* RequestAttChangeDelegate(const FGameplayAttribute& Attribute);
};
