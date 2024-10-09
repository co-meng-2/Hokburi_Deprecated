// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "HBTargetType.generated.h"

struct FGameplayEventData;

// ShowWorldContextPin을 왜 사용하는지 이유를 지금으로서는 모르겠음.
UCLASS(Blueprintable/*, meta = (ShowWorldContextPin)*/)
class HOKBURI_API UHBTargetType : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void GetTargets(AActor* Avatar, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const;
	virtual void GetTargets_Implementation(AActor* Avatar, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const;
};

UCLASS(NotBlueprintable)
class HOKBURI_API UHBTargetType_UseOwner : public UHBTargetType
{
	GENERATED_BODY()

public:
	/** Uses the passed in event data */
	virtual void GetTargets_Implementation(AActor* Avatar, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const override;
};

UCLASS(NotBlueprintable)
class HOKBURI_API UHBTargetType_UseEventData : public UHBTargetType
{
	GENERATED_BODY()

public:
	/** Uses the passed in event data */
	virtual void GetTargets_Implementation(AActor* Avatar, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const override;
};