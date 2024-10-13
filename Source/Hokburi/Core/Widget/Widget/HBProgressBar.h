// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ProgressBar.h"
#include "HBProgressBar.generated.h"

/**
 * 
 */
UCLASS()
class HOKBURI_API UHBProgressBar : public UProgressBar
{
	GENERATED_BODY()
public:
	float Cur;
	float Max;

	void Init(float NewCur, float NewMax);

	UFUNCTION()
	void UpdateCur(float NewCur);
	UFUNCTION()
	void UpdateMax(float NewMax);
};
