// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Widget/HBUserWidgetBase.h"

#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"


void UHBUserWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
    PreInit();
    Init();
    BindDelegate();
}

void UHBUserWidgetBase::NativeOnFocusLost(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnFocusLost(InFocusEvent);

    if(bHideWhenFocusLost)
    {
        if(bUseCollapse)
			SetVisibility(ESlateVisibility::Collapsed);
        else
            SetVisibility(ESlateVisibility::Hidden);
    }
}

void UHBMovableUserWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // UButton이 어느 Panel에 속하는지 CanvasPanelSlot을 얻어옴
    CanvasSlot = Cast<UCanvasPanelSlot>(Slot);
}

FReply UHBMovableUserWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
    {
        bIsDragging = true;
        InitialMousePosition = InMouseEvent.GetScreenSpacePosition();

        if (CanvasSlot)
        {
            InitialWidgetPosition = CanvasSlot->GetPosition();
        }

        return FReply::Handled();
    }

    return FReply::Unhandled();;
}

FReply UHBMovableUserWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (bIsDragging && CanvasSlot)
    {
        FVector2D CurrentMousePosition = InMouseEvent.GetScreenSpacePosition();

        UCanvasPanel* CanvasPanel = Cast<UCanvasPanel>(CanvasSlot->Parent);
        auto CanvasSize = CanvasPanel->GetCachedGeometry().GetLocalSize();

        FVector2D Delta = (CurrentMousePosition - InitialMousePosition) / UWidgetLayoutLibrary::GetViewportSize(this) * CanvasSize;

        // 버튼의 위치를 이동
        CanvasSlot->SetPosition(InitialWidgetPosition + Delta);

        return FReply::Handled();
    }

    return FReply::Unhandled();
}

FReply UHBMovableUserWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
    {
        bIsDragging = false;
        return FReply::Handled();
    }

    return FReply::Unhandled();
}
