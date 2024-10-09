// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HBGameModeBase.generated.h"

class AHBPlayerCharacter;

namespace EEndPlayReason
{
	enum ExtendedType : int
	{
		custom_1 = 100,
		custom_2,
		custom_3,
		custom_4
	};
}

/**
 * 
 */
UCLASS()
class HOKBURI_API AHBGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void StartPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	// Deprecated -> Asset을 찾아 DataTable을 Load하는 형식
	void RegisterStoryTableToStoryManager();

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AHBPlayerCharacter> SpawnCharacterClass;

private:
	TArray<TWeakObjectPtr<APlayerController>> PlayerControllers;


};
