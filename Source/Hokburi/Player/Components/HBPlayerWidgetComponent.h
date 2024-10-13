// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/StorySystem/GameAbilitySystem/HBAttributeSets.h"
#include "Components/ActorComponent.h"
#include "HBPlayerWidgetComponent.generated.h"


class UHBStory;
class FOnStoryChangeDelegate;
class AHBPlayerControllerBase;
class UHBPlayerWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HOKBURI_API UHBPlayerWidgetComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	void Init();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UHBPlayerWidget* GameWidget;

	FOnStoryChangeDelegate* GetStoryChangeDelegate();
	const TArray<UHBStory*>& GetStoryArray();
};
