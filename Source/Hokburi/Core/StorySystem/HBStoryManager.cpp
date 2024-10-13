// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/StorySystem/HBStoryManager.h"

#include "GameAbilitySystem/HBAbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/HBPlayerCharacter.h"


void UHBStory::Clear()
{
	GASpecHandles.Empty();
	SetStoryInfo(nullptr);
}

UHBStoryManager* UHBStoryManager::GetInstance(UObject* WorldContextObject)
{
	return WorldContextObject->GetWorld()->GetSubsystem<UHBStoryManager>();
}

void UHBStoryManager::InitStoryTable()
{
	static const FString DataTablePath = TEXT("DataTable'/Game/Hokburi/Core/StorySystem/StoryDataTable/DT_StoryDataTable.DT_StoryDataTable'");
	StoryTable =LoadObject<UDataTable>(GetOuter(), *DataTablePath);
}

void UHBStoryManager::MakeStoryMapAndArrayFromStoryTable()
{
	TArray<FHBStoryTableRow*> StoryRows;
	StoryTable->GetAllRows<FHBStoryTableRow>(TEXT(""), StoryRows);
	TArray<FName> RowNames = StoryTable->GetRowNames();
	StoryMap.SetNum(MaxStoryLevel);
	StoryArray.SetNum(MaxStoryLevel);
	for(int idx = 0; idx < StoryRows.Num(); ++idx)
	{
		int Level = StoryRows[idx]->Level;
		StoryMap[Level].Add(RowNames[idx], StoryRows[idx]);
		StoryArray[Level].Add(StoryRows[idx]);
	}
}

TArray<FHBStoryTableRow*> UHBStoryManager::GetSelectedRandomStory(int SelectNum, int StoryLevel)
{
	TArray<FHBStoryTableRow*> Ret;

	// Reservoir Algorithm 사용
	TArray<int> Reservoir;
	FRandomStream RandomStream(FDateTime::Now().ToUnixTimestamp());

	for(int i = 0; i < SelectNum; ++i)
	{
		Reservoir.Add(i);
	}

	int StoryMapSize = StoryMap[StoryLevel].Num();
	for(int i = SelectNum; i< StoryMapSize; ++i)
	{
		int j = RandomStream.RandRange(0, i);
		if(j < SelectNum)
		{
			Reservoir[j] = i;
		}
	}

	for(auto idx : Reservoir)
	{
		Ret.Add(StoryArray[StoryLevel][idx]);
		UE_LOG(LogTemp, Warning, TEXT("%i"), idx);
	}

	return Ret;
}

void UHBStoryManager::ClearStory(AHBPlayerCharacter* Character, EStoryMappingKey::Key EStoryMappingKey, UAbilitySystemComponent* ASC)
{
	ASC = Character->GetAbilitySystemComponent();

	// 기존에 가지고 있던 Story와 관련된 것들 지워줌
	if (UHBStory* Story = Character->OwningStories[EStoryMappingKey])
	{
		for (const auto& SpecHandle : Story->GASpecHandles)
		{
			// ClearAbility -> OnRemoveAbility로 이어짐 -> 여기서 관련된 것들 삭제
			ASC->ClearAbility(SpecHandle);
		}
		Story->Clear();
	}
}

UHBStory* UHBStoryManager::MakeNewStoryFromStoryInfo(FHBStoryTableRow* StoryInfo)
{
	UHBStory* NewStory = NewObject<UHBStory>(GetTransientPackage(), UHBStory::StaticClass());
	NewStory->Level = StoryInfo->Level;
	NewStory->SetStoryInfo(StoryInfo);
	return NewStory;
}

void UHBStoryManager::GiveStory(AHBPlayerCharacter* Character, FHBStoryTableRow* StoryInfo, EStoryMappingKey::Key EStoryMappingKey)
{
	UAbilitySystemComponent* ASC = Character->GetAbilitySystemComponent();

	// 이전의 Story 정보들 정리
	ClearStory(Character, EStoryMappingKey, ASC);

	// 새로운 스토리 생성 및 초기화
	UHBStory* NewStory = MakeNewStoryFromStoryInfo(StoryInfo);

	// Story가 가져야 할 GameAbilitySpecHandle 옵션에 따른 작업
	TArray<FGameplayAbilitySpecHandle> InputHandles;
	TArray<FGameplayAbilitySpecHandle> NotInputHandles;
	for(const auto GAClass : StoryInfo->OwningAbilityClasses)
	{
		EStoryMappingKey::Key ValidMappingKey = EStoryMappingKey;
		if (GAClass->GetDefaultObject<UHBGameplayAbility>()->bUseInput == false)
			ValidMappingKey = EStoryMappingKey::END;

		FGameplayAbilitySpecHandle SpecHandle = ASC->GiveAbility(FGameplayAbilitySpec(GAClass, 0, static_cast<int32>(ValidMappingKey), Character));

		if (GAClass->GetDefaultObject<UHBGameplayAbility>()->bPermanent == false)
		{
			if (ValidMappingKey == EStoryMappingKey::END)
			{
				NotInputHandles.Add(SpecHandle);
			}
			else
			{
				InputHandles.Add(SpecHandle);
			}
		}
	}

	for(auto Handle : InputHandles)
	{
		NewStory->GASpecHandles.Add(Handle);
	}
	NewStory->InputSpecEndIndex = InputHandles.Num();

	for (auto Handle : NotInputHandles)
	{
		NewStory->GASpecHandles.Add(Handle);
	}

	for(int i = NewStory->InputSpecEndIndex; i < NewStory->GASpecHandles.Num(); ++i)
	{
		Character->GetAbilitySystemComponent()->TryActivateAbility(NewStory->GASpecHandles[i]);
	}

	Character->OwningStories[EStoryMappingKey] = NewStory;
	// Delegate 
	Character->OnStoryChange(EStoryMappingKey, *StoryInfo);
}
