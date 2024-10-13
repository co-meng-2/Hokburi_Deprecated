// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Widget/HBPlayerWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Core/HBBlueprintFunctionLibrary.h"
#include "Core/StorySystem/HBStoryManager.h"
#include "Core/Widget/Widget/HBProgressBar.h"
#include "GameFramework/PlayerState.h"
#include "Player/HBPlayerCharacter.h"
#include "Player/HBPlayerControllerBase.h"
#include "Player/Components/HBPlayerWidgetComponent.h"

void UHBStatusUI::BindDelegate()
{
	Super::BindDelegate();
	BindHPBarDelegate();
}

void UHBStatusUI::BindHPBarDelegate()
{
	auto DelegateHP = RequestAttChangeDelegate(UHBHealthAttributeSet::GetHealthAttribute());
	DelegateHP->AddDynamic(HPBar, &UHBProgressBar::UpdateCur);

	auto DelegateMaxHP = RequestAttChangeDelegate(UHBHealthAttributeSet::GetMaxHealthAttribute());
	DelegateMaxHP->AddDynamic(HPBar, &UHBProgressBar::UpdateMax);
}

void UHBStatusUI::Init()
{
	Super::Init();
	auto AttSetHealth = UHBGameAbilitySystemBFL::GetAttSet<UHBHealthAttributeSet>(GetOwningPlayerState(), UHBHealthAttributeSet::GetMaxHealthAttribute());
	HPBar->Init(AttSetHealth->GetHealth(), AttSetHealth->GetMaxHealth());
}


FOnAttributeChangedDelegate* UHBStatusUI::RequestAttChangeDelegate(const FGameplayAttribute& Attribute)
{
	auto PlayerState = GetOwningPlayerState();
	return UHBGameAbilitySystemBFL::GetAttChangeDelegate(PlayerState, Attribute);
}

void UHBStoryButtonUI::PreInit()
{
	Super::PreInit();
	InitButtonMap();
}

void UHBStoryButtonUI::Init()
{
	Super::Init();
	auto PlayerWidgetComponent = GetOwningPlayer()->GetComponentByClass<UHBPlayerWidgetComponent>();
	const TArray<UHBStory*>& StoryArray = PlayerWidgetComponent->GetStoryArray();
	for(int i = 0; i < StoryArray.Num(); ++i)
	{
		EStoryMappingKey::Key Key = static_cast<EStoryMappingKey::Key>(i);
		UpdateButton(Key, StoryArray[i]->GetStoryInfo());
	}
}

void UHBStoryButtonUI::BindDelegate()
{
	Super::BindDelegate();
	BindStoryChangeDelegate();
	BindOnClickedDelegate();
}

void UHBStoryButtonUI::InitButtonMap()
{
	ButtonMap.Add(EStoryMappingKey::E_Start, Button_StoryE);
	Button_StoryE->EStoryMappingKey = EStoryMappingKey::E_Start;
	ButtonMap.Add(EStoryMappingKey::R, Button_StoryR);
	Button_StoryR->EStoryMappingKey = EStoryMappingKey::R;
	ButtonMap.Add(EStoryMappingKey::D, Button_StoryD);
	Button_StoryD->EStoryMappingKey = EStoryMappingKey::D;
	ButtonMap.Add(EStoryMappingKey::F, Button_StoryF);
	Button_StoryF->EStoryMappingKey = EStoryMappingKey::F;
	ButtonMap.Add(EStoryMappingKey::C, Button_StoryC);
	Button_StoryC->EStoryMappingKey = EStoryMappingKey::C;
	ButtonMap.Add(EStoryMappingKey::V, Button_StoryV);
	Button_StoryV->EStoryMappingKey = EStoryMappingKey::V;
}

FOnStoryChangeDelegate* UHBStoryButtonUI::RequestStoryChangeDelegate()
{
	auto PlayerController = GetOwningPlayer();
	auto PlayerWidgetComponent = PlayerController->GetComponentByClass<UHBPlayerWidgetComponent>();
	return PlayerWidgetComponent->GetStoryChangeDelegate();
}

void UHBStoryButtonUI::BindStoryChangeDelegate()
{
	RequestStoryChangeDelegate()->AddDynamic(this, &ThisClass::UpdateButton);
}

void UHBStoryButtonUI::UpdateButton(EStoryMappingKey::Key EStoryMappingKey, FHBStoryTableRow& StoryInfo)
{
	UHBStoryButton* Button = *ButtonMap.Find(EStoryMappingKey);

	UTexture2D* Image = StoryInfo.StoryImage;

	FButtonStyle ButtonStyle;
	FSlateBrush NewBrush;
	NewBrush.SetResourceObject(Image);
	NewBrush.ImageSize = Button->GetStyle().Normal.ImageSize;

	ButtonStyle.Normal = NewBrush;
	ButtonStyle.Hovered = NewBrush;
	ButtonStyle.Pressed = NewBrush;

	// 신호 전달
	Button->SetStyle(ButtonStyle);

	Button->StoryLevel = StoryInfo.Level;
	Button->StoryContent = StoryInfo.StoryContent;
	Button->SetToolTipText(FText::FromString(StoryInfo.StoryContent));
}

UHBStoryChoicePopUpUIButton::UHBStoryChoicePopUpUIButton()
{
	InitIsFocusable(false);
}

void UHBStoryButtonUI::BindOnClickedDelegate()
{

	for (auto& [Key, Button] : ButtonMap)
	{
		Button->OnClicked.AddDynamic(Button, &UHBStoryButton::UpdatePopUp);
	}
}

const TArray<UHBStory*>& UHBStoryButtonUI::RequestStoryArray()
{
	return Cast<UHBPlayerWidgetComponent>(UHBWidgetBFL::FindOwnerComponent(this))->GetStoryArray();
}

void UHBStoryButton::UpdatePopUp()
{
	UHBStoryChoicePopUpUI* StoryChoicePopUpUI = Cast<UHBStoryChoicePopUpUI>(UHBWidgetBFL::FindRootUserWidget(this)->WidgetTree->FindWidget(FName("StoryChoicePopUpUI")));
	// 1. Popup Update
	StoryChoicePopUpUI->UpdateChoiceButtons(StoryLevel, EStoryMappingKey);

	// 2. Show Popup
	StoryChoicePopUpUI->SetVisibility(ESlateVisibility::Visible);
	//FInputModeUIOnly InputMode;
	//InputMode.SetWidgetToFocus(StoryChoicePopUpUI->TakeWidget()); // SetFocus();
	//UGameplayStatics::GetPlayerController(this, 0)->SetInputMode(InputMode);
}

void UHBStoryChoicePopUpUI::PreInit()
{
	Super::PreInit();
	CreateChoiceButtons();
	CachedChoices.SetNum(6);
	SetVisibility(ESlateVisibility::Collapsed);
	CachedStoryContext = EStoryMappingKey::END;
}

void UHBStoryChoicePopUpUI::CreateChoiceButtons()
{
	if (!ButtonContainer) return;

	StoryChoiceButtons.SetNum(ButtonCount);
	StoryButtonNames.SetNum(ButtonCount);

	for (uint8 i = 0; i < ButtonCount; ++i)
	{
		StoryChoiceButtons[i] = NewObject<UHBStoryChoicePopUpUIButton>(this);
		StoryChoiceButtons[i]->ButtonIdx = i;

		StoryButtonNames[i] = NewObject<UTextBlock>(this);
		StoryChoiceButtons[i]->AddChild(StoryButtonNames[i]);

		UVerticalBoxSlot* BoxSlot = ButtonContainer->AddChildToVerticalBox(StoryChoiceButtons[i]);

		FSlateChildSize SlateChildSize;
		SlateChildSize.SizeRule = ESlateSizeRule::Fill;
		SlateChildSize.Value = 1.f;
		BoxSlot->SetSize(SlateChildSize);
		BoxSlot->SetPadding(FMargin(MarginHV));
		BoxSlot->SetHorizontalAlignment(HAlign_Fill);
		BoxSlot->SetVerticalAlignment(VAlign_Fill);
	}
}

void UHBStoryChoicePopUpUI::UpdateChoiceButtons(int StoryLevel, EStoryMappingKey::Key EStoryMappingKey)
{
	CachedStoryContext = EStoryMappingKey;

	if (CachedChoices[EStoryMappingKey].IsEmpty())
	{
		auto StoryManager = UHBStoryManager::GetInstance(this);
		TArray<FHBStoryTableRow*> StoryInfos = StoryManager->GetSelectedRandomStory(ButtonCount, StoryLevel + 1);

		// 이미 Choice가 갱신된 상태인지 확인
		for (auto StoryInfo : StoryInfos)
		{
			CachedChoices[EStoryMappingKey].Add(StoryInfo);
		}
	}

	for(int i = 0; i < StoryChoiceButtons.Num(); ++i)
	{
		StoryChoiceButtons[i]->OnClicked.Clear();
		StoryChoiceButtons[i]->OnClicked.AddDynamic(StoryChoiceButtons[i], &UHBStoryChoicePopUpUIButton::GiveStory);
		StoryButtonNames[i]->SetText(FText::FromName(CachedChoices[EStoryMappingKey][i]->StoryName));
	}
}

void UHBStoryChoicePopUpUIButton::GiveStory()
{
	UHBStoryChoicePopUpUI* PopUpUI = Cast<UHBStoryChoicePopUpUI>(UHBWidgetBFL::FindUserWidget(this));
	EStoryMappingKey::Key EStoryMappingKey = PopUpUI->CachedStoryContext;
	auto StoryManager = UHBStoryManager::GetInstance(this);

	// @HB-Todo : Character는 바뀔일 없으니 Cache 해놓기
	UHBPlayerWidget* PlayerWidget = Cast<UHBPlayerWidget>(UHBWidgetBFL::FindRootUserWidget(this));
	auto PlayerController = PlayerWidget->GetOwningPlayer<AHBPlayerControllerBase>();
	StoryManager->GiveStory(PlayerController->GetMainCharacter(), PopUpUI->CachedChoices[EStoryMappingKey][ButtonIdx], EStoryMappingKey);

	PopUpUI->CachedChoices[EStoryMappingKey].Empty();
	PopUpUI->SetVisibility(ESlateVisibility::Collapsed);
}














