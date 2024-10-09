// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/HBSelectableInterface.h"
#include "HBCharacterBase.generated.h"

class AHBPlayerControllerBase;
class UHBAbilitySystemComponent;

UCLASS()
class HOKBURI_API AHBCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AHBCharacterBase();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UHBAbilitySystemComponent* GetAbilitySystemComponent() { return ASC; };

	// Components
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hokburi | Components")
	UHBAbilitySystemComponent* ASC;
};
