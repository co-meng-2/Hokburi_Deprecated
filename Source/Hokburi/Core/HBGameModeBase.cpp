// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/HBGameModeBase.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "Character/Components/HBCharacterWidgetComponent.h"
#include "Engine/World.h"
#include "Player/HBPlayerCameraPawn.h"
#include "Player/HBPlayerCharacter.h"
#include "Player/HBPlayerControllerBase.h"
#include "Player/HBPlayerState.h"
#include "Player/Components/HBPlayerWidgetComponent.h"
#include "StorySystem/HBStoryManager.h"
#include "StorySystem/GameAbilitySystem/HBAbilitySystemComponent.h"

void AHBGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	PlayerControllers.Add(NewPlayer);
}

void AHBGameModeBase::StartPlay()
{
	// RegisterStoryTableToStoryManager();
	UHBStoryManager* StoryManager = UHBStoryManager::GetInstance(this);
	StoryManager->InitStoryTable();
	StoryManager->MakeStoryMapAndArrayFromStoryTable();

	// 1. 내 플레이어 컨트롤러 찾음.
	for(auto PlayerController : PlayerControllers)
	{
		auto HBPlayerController = Cast<AHBPlayerControllerBase>(PlayerController);

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		// SpawnParams.Instigator

		APawn* CameraPawn = Cast<AHBPlayerControllerBase>(PlayerController)->GetPawn();
		AHBPlayerCharacter* Character = GetWorld()->SpawnActor<AHBPlayerCharacter>(SpawnCharacterClass, CameraPawn->GetActorLocation(), CameraPawn->GetActorRotation(), SpawnParams);
		Character->OwningStories.SetNum(EStoryMappingKey::END);
		Character->PlayerController = HBPlayerController;
		auto PlayerState = HBPlayerController->GetPlayerState<AHBPlayerState>();
		Character->ASC_MainCharacter = PlayerState->ASC;
		PlayerState->ASC->InitAbilityActorInfo(PlayerState, Character);

		for(int CurKey = EStoryMappingKey::E_Start; CurKey < EStoryMappingKey::END; CurKey++)
		{
			auto DefaultStory = StoryManager->StoryMap[0].begin()->Value;
			StoryManager->GiveStory(Character, DefaultStory, static_cast<EStoryMappingKey::Key>(CurKey));
		}
	}

	// BeginPlay 담당
	Super::StartPlay();
}

void AHBGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AHBGameModeBase::RegisterStoryTableToStoryManager()
{
	// StoryManager Array 초기화
	//UHBStoryManager* StoryManager = UHBStoryManager::GetInstance(this);
	//TArray<UDataTable*>& DTArray = StoryManager->StoryTables;
	//DTArray.SetNum(StoryManager->MaxStoryLevel + 1);
	//
	//FString AssetPath = TEXT("/Game/Hokburi/Core/StorySystem/StoryDataTable");

	//// 2. AssetRegistryModule을 초기화.
	//FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	//IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

	//// 필터를 설정하여 특정 폴더의 파일만 가져옴
	//FARFilter Filter;
	//Filter.PackagePaths.Add(*AssetPath);
	//Filter.bRecursivePaths = false;

	//TArray<FAssetData> AssetList;
	//AssetRegistry.GetAssets(Filter, AssetList);
	//
	//for (const FAssetData& AssetData : AssetList)
	//{
	//	// Asset 이름 가져오기
	//	FString AssetName = AssetData.AssetName.ToString();

	//	int Level = AssetName[AssetName.Len() - 1] - '0';
	//	if (AssetData.AssetClassPath == UDataTable::StaticClass()->GetClassPathName())
	//	{
	//		DTArray[Level] = Cast<UDataTable>(AssetData.GetAsset());
	//	}
	//}
	//UHBStoryManager::GetInstance(this)->DefaultStory = DTArray[0]->FindRow<FHBStoryTableRow>(FName("Default"), TEXT(""));
}
