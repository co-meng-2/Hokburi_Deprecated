// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/SphereComponent.h"
#include "HBAttackCollisionComponent.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class HOKBURI_API UHBAttackCollisionComponent : public USphereComponent
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, Category="Hokburi")
	FCollisionProfileName CollisionProfileName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hokburi")
	FGameplayTag EventTag;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
