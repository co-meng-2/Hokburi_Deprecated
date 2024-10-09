// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HBWidgetBase.generated.h"

class UCanvasPanelSlot;
/**
 * 
 */
UCLASS()
class HOKBURI_API UHBWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHideWhenFocusLost = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUseCollapse = false;

	virtual void NativeOnFocusLost(const FFocusEvent& InFocusEvent) override;

	static UUserWidget* FindRootUserWidget(UWidget* Widget);
	static UUserWidget* FindUserWidget(UWidget* Widget);
};

UCLASS()
class HOKBURI_API UHBMovableWidget : public UHBWidgetBase
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	UCanvasPanelSlot* CanvasSlot;
	bool bIsDragging = false;
	FVector2D InitialMousePosition;
	FVector2D InitialWidgetPosition;
};


