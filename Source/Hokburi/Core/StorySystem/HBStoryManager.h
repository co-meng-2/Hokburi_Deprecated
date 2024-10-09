// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameAbilitySystem/HBGameplayAbility.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "HBStoryManager.generated.h"
/**
 * 
 */

class AHBPlayerCharacter;
namespace EStoryMappingKey
{
	enum Key : uint8;
}

struct FGameplayAbilitySpecHandle;

USTRUCT(BlueprintType)
struct FHBStoryTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hokburi")
	FName StoryName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hokburi")
	bool bUse = true;;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hokburi")
	FString StoryContent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hokburi")
	TArray<TSubclassOf<UHBGameplayAbility>> OwningAbilityClasses;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hokburi")
	UTexture2D* StoryImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hokburi")
	int32 Level;
};

UCLASS(BlueprintType)
class HOKBURI_API UHBStory : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	FHBStoryTableRow& GetStoryInfo() { return *StoryInfo;};
	void SetStoryInfo(FHBStoryTableRow* NewStoryInfo) { StoryInfo = NewStoryInfo; };

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hokburi")
	uint8 Level;

	// 미만으로 사용
	uint32 InputSpecEndIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FGameplayAbilitySpecHandle> GASpecHandles;

public:
	void Clear();

private:
	FHBStoryTableRow* StoryInfo;
};


UCLASS()
class HOKBURI_API UHBStoryManager : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	static UHBStoryManager* GetInstance(UObject* WorldContextObject);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hokburi | DataTable")
	uint8 MaxStoryLevel = 6;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Hokburi | DataTable")
	UDataTable* StoryTable;
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hokburi | DataTable")

	// LV -> StoryButtonNames
	TArray<TMap<FName, FHBStoryTableRow*>>	StoryMap;
	TArray<TArray<FHBStoryTableRow*>>		StoryArray;

	void InitStoryTable();
	void MakeStoryMapAndArrayFromStoryTable();
	TArray<FHBStoryTableRow*> GetSelectedRandomStory(int SelectNum, int StoryLevel);
	void ClearStory(AHBPlayerCharacter* Character, EStoryMappingKey::Key EStoryMappingKey, UAbilitySystemComponent* ASC);
	UHBStory* MakeNewStoryFromStoryInfo(FHBStoryTableRow* StoryInfo);
	void GiveStory(AHBPlayerCharacter* Character, FHBStoryTableRow* StoryInfo, EStoryMappingKey::Key EStoryMappingKey);

};