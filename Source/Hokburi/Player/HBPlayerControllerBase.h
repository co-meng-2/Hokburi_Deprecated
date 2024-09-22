// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HBPlayerControllerBase.generated.h"

class UInputMappingContext;
/**
 * 
 */
UCLASS()
class HOKBURI_API AHBPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	AHBPlayerControllerBase();
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Hokburi | Input")
	UInputMappingContext* IMC;
};
