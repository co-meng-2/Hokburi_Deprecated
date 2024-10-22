// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "HBTeamSystem.generated.h"

// This class does not need to be modified.

UCLASS(meta=(BlueprintSpawnableComponent))
class UHBTeamComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess))
	FGameplayTag TeamTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess))
	FGameplayTag PlayerTag;

public:
	const FGameplayTag& GetTeamTag() { return TeamTag; };
	const FGameplayTag& GetPlayerTag() { return PlayerTag; };

	bool IsTeam(const FGameplayTag& Tag) { return Tag == TeamTag; }
	bool HasSamePlayerTag(const FGameplayTag& Tag) { return Tag == PlayerTag; }
};
