// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Widget/ContentWidget/HBButtons.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"


UHBMovableButton::UHBMovableButton()
{
	BindPressedReleasedEvent();
}

void UHBMovableButton::OnPressEvent()
{
	GetWorld()->GetTimerManager().SetTimer(Handle, this, &ThisClass::Move, 0.01f, true);
	auto ViewPortScale = UWidgetLayoutLibrary::GetViewportScale(this);
	PrevMousePos = UWidgetLayoutLibrary::GetMousePositionOnViewport(this) * ViewPortScale;

}

void UHBMovableButton::Move()	
{
	UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(Slot);

	auto ViewPortSize = UWidgetLayoutLibrary::GetViewportSize(this);
	auto ViewPortScale = UWidgetLayoutLibrary::GetViewportScale(this);

	FVector2D CurrentMousePos = UWidgetLayoutLibrary::GetMousePositionOnViewport(this) * ViewPortScale;
	auto Add = CurrentMousePos - PrevMousePos;
	auto CurrentPosition = CanvasPanelSlot->GetPosition();
	UCanvasPanel* CanvasPanel = Cast<UCanvasPanel>(CanvasPanelSlot->Parent);
	auto CanvasSz = CanvasPanel->GetCachedGeometry().GetLocalSize();

	Add = Add / ViewPortSize * CanvasSz;
	CanvasPanelSlot->SetPosition(CurrentPosition + Add);
	PrevMousePos = CurrentMousePos;
}

void UHBMovableButton::OnReleaseEvent()
{
	GetWorld()->GetTimerManager().ClearTimer(Handle);
}

void UHBMovableButton::BindPressedReleasedEvent()
{
	OnPressed.AddDynamic(this, &ThisClass::OnPressEvent);
	OnReleased.AddDynamic(this, &ThisClass::OnReleaseEvent);
}

UHBFocusableButton::UHBFocusableButton()
{
	InitIsFocusable(false);
}


