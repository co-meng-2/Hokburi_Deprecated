// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HBAnimInstanceBase.generated.h"

class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class HOKBURI_API UHBAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadWrite, Category = "Hokburi | References")
	ACharacter* Character;
	UPROPERTY(BlueprintReadWrite, Category = "Hokburi | References")
	UCharacterMovementComponent* CharacterMovementComp;

	UPROPERTY(BlueprintReadWrite, Category = "Hokburi | Data")
	float GroundSpeed;
	UPROPERTY(BlueprintReadWrite, Category = "Hokburi | Data")
	FVector Velocity;
	UPROPERTY(BlueprintReadWrite, Category = "Hokburi | Data")
	bool ShouldMove;
};
