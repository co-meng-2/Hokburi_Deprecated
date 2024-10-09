// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Widget/HBWidgetBase.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"


void UHBWidgetBase::NativeOnFocusLost(const FFocusEvent& InFocusEvent)
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

UUserWidget* UHBWidgetBase::FindRootUserWidget(UWidget* Widget)
{
    UWidget* CurWidget = Widget;

    while (CurWidget)
    {
        CurWidget = FindUserWidget(CurWidget);
        UUserWidget* UserWidget = Cast<UUserWidget>(CurWidget);
        if (UserWidget && UserWidget->GetParent() == nullptr)
            return UserWidget;
    }

    return nullptr;
}

UUserWidget* UHBWidgetBase::FindUserWidget(UWidget* Widget)
{
    UWidget* CurWidget = Widget;
    while (CurWidget)
    {
    	UPanelWidget* ParentWidget = CurWidget->GetParent();
        if(ParentWidget == nullptr)
        {
            UWidgetTree* CurWidgetTree = Cast<UWidgetTree>(CurWidget->GetOuter());
            return Cast<UUserWidget>(CurWidgetTree->GetOuter());
        }
        CurWidget = ParentWidget;
    }
    return nullptr;
}

void UHBMovableWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // UButton이 어느 Panel에 속하는지 CanvasPanelSlot을 얻어옴
    CanvasSlot = Cast<UCanvasPanelSlot>(Slot);
}

FReply UHBMovableWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
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

FReply UHBMovableWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
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

FReply UHBMovableWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
    {
        bIsDragging = false;
        return FReply::Handled();
    }

    return FReply::Unhandled();
}
