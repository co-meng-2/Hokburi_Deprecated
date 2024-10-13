// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "HBPlayerState.generated.h"

class UHBPlayerWidgetComponent;
class UHBAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class HOKBURI_API AHBPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AHBPlayerState();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hokburi | Component")
	UHBAbilitySystemComponent* ASC;

	UFUNCTION(BlueprintCallable)
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
