// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "HBCharacterBase.generated.h"

class UHBCharacterWidgetComponent;
class UWidgetComponent;
class AHBPlayerControllerBase;
class UHBAbilitySystemComponent;
class UDecalComponent;
class UInputComponent;

UCLASS()
class HOKBURI_API AHBCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AHBCharacterBase(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// Components
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hokburi | Components")
	UHBAbilitySystemComponent* ASC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hokburi | Components")
	UHBCharacterWidgetComponent* CharacterWidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hokburi | Components")
	UDecalComponent* DecalComponent;

public:
	UFUNCTION(BlueprintCallable)
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};