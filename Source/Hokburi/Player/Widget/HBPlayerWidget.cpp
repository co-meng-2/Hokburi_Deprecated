// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Widget/HBPlayerWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Core/StorySystem/HBStoryManager.h"
#include "Core/StorySystem/GameAbilitySystem/HBAbilitySystemComponent.h"
#include "Core/Widget/ContentWidget/HBButtons.h"
#include "Kismet/GameplayStatics.h"
#include "Player/HBPlayerCharacter.h"
#include "Player/Components/HBPlayerWidgetComponent.h"

void UHBStatusUI::NativeConstruct()
{
	Super::NativeConstruct();

	auto DelegateHP = RequestAttChangeDelegate(UHBHealthAttributeSet::GetHealthAttribute());
	DelegateHP->AddDynamic(this, &ThisClass::UpdateHP);

	auto DelegateMaxHP = RequestAttChangeDelegate(UHBHealthAttributeSet::GetMaxHealthAttribute());
	DelegateMaxHP->AddDynamic(this, &ThisClass::UpdateMaxHP);
}

void UHBStatusUI::UpdateHPBar()
{
	HPBar->SetPercent(HP / MaxHP);
}

void UHBStatusUI::UpdateHP(float New)
{
	HP = New;
	UpdateHPBar();
}

void UHBStatusUI::UpdateMaxHP(float New)
{
	MaxHP = New;
	UpdateHPBar();
}


FOnAttributeChangedDelegate* UHBStatusUI::RequestAttChangeDelegate(FGameplayAttribute Attribute)
{
	auto WidgetComponent = Cast<UHBPlayerWidget>(FindRootUserWidget(this))->OwnerComponent;
	return WidgetComponent->GetAttChangeDelegate(Attribute);
}

void UHBStoryButtonUI::NativeConstruct()
{
	Super::NativeConstruct();

	InitButtonMap();
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
}

FOnStoryChangeDelegate* UHBStoryButtonUI::RequestStoryChangeDelegate()
{
	auto WidgetComponent = Cast<UHBPlayerWidget>(FindRootUserWidget(this))->OwnerComponent;
	return WidgetComponent->GetStoryChangeDelegate();
}

void UHBStoryButtonUI::BindOnClickedDelegate()
{

	for (auto& [Key, Button] : ButtonMap)
	{
		Button->OnClicked.AddDynamic(Button, &UHBStoryButton::UpdatePopUp);
	}
}

void UHBStoryButton::UpdatePopUp()
{
	UHBStoryChoicePopUpUI* StoryChoicePopUpUI = Cast<UHBStoryChoicePopUpUI>(UHBWidgetBase::FindRootUserWidget(this)->WidgetTree->FindWidget(FName("StoryChoicePopUpUI")));
	// 1. Popup Update
	StoryChoicePopUpUI->UpdateChoiceButtons(StoryLevel, EStoryMappingKey);

	// 2. Show Popup
	StoryChoicePopUpUI->SetVisibility(ESlateVisibility::Visible);
	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(StoryChoicePopUpUI->TakeWidget()); // SetFocus();
	UGameplayStatics::GetPlayerController(this, 0)->SetInputMode(InputMode);
}

void UHBStoryChoicePopUpUI::NativeConstruct()
{
	Super::NativeConstruct();
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

	for(auto StoryChoiceButton : StoryChoiceButtons)
	{
		StoryChoiceButton->OnClicked.Clear();
		StoryChoiceButton->OnClicked.AddDynamic(StoryChoiceButton, &UHBStoryChoicePopUpUIButton::GiveStory);
	}
}

void UHBStoryChoicePopUpUIButton::GiveStory()
{
	UHBStoryChoicePopUpUI* PopUpUI = Cast<UHBStoryChoicePopUpUI>(UHBWidgetBase::FindUserWidget(this));
	EStoryMappingKey::Key EStoryMappingKey = PopUpUI->CachedStoryContext;
	auto StoryManager = UHBStoryManager::GetInstance(this);

	// @HB-Todo : Character는 바뀔일 없으니 Cache 해놓기
	UHBPlayerWidget* PlayerWidget = Cast<UHBPlayerWidget>(UHBWidgetBase::FindRootUserWidget(this));
	auto WidgetComponent = Cast<UHBPlayerWidgetComponent>(PlayerWidget->OwnerComponent);
	auto Character =  Cast<AHBPlayerCharacter>(WidgetComponent->GetOwner());
	StoryManager->GiveStory(Character, PopUpUI->CachedChoices[EStoryMappingKey][ButtonIdx], EStoryMappingKey);

	PopUpUI->CachedChoices[EStoryMappingKey].Empty();
}














