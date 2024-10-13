// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "HBButtons.generated.h"

/**
 * 
 */

UCLASS()
class HOKBURI_API UHBMovableButton : public UButton
{
	GENERATED_BODY()

public:
	UHBMovableButton();

	UFUNCTION()
	void OnPressEvent();
	void Move();
	UFUNCTION()
	void OnReleaseEvent();

	void BindPressedReleasedEvent();

	FTimerHandle Handle;
	FVector2D PrevMousePos;
};
