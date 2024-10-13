// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "HBCharacterWidgetComponent.generated.h"

struct FGameplayAttribute;
class FOnAttributeChangedDelegate;
/**
 * 
 */
UCLASS(BlueprintType, meta = (BlueprintSpawnableComponent))
class HOKBURI_API UHBCharacterWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
public:
	UHBCharacterWidgetComponent();
	virtual void InitWidget() override;
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FVector2D OriginalDrawSize;

public:
	FOnAttributeChangedDelegate* GetAttChangeDelegate(const FGameplayAttribute& Attribute);
};
