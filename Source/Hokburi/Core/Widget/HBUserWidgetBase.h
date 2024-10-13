// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HBUserWidgetBase.generated.h"

class UCanvasPanelSlot;
/**
 * 
 */
UCLASS()
class HOKBURI_API UHBUserWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	// Init 전 Setting
	virtual void PreInit(){};
	// 하위 Widget에 대한 초깃값 Init
	virtual void Init() {};
	// Delegate 등록
	virtual void BindDelegate() {};

	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHideWhenFocusLost = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUseCollapse = false;

	virtual void NativeOnFocusLost(const FFocusEvent& InFocusEvent) override;

	// Character Widget Component에서는 Widget과 Component를 이을 자리가 없다.. 따라서 InitWidget을 override해서 RootUserWidget과 Component를 이어준다.
	TWeakObjectPtr<UActorComponent> OwnerComponent;
};

UCLASS()
class HOKBURI_API UHBMovableUserWidget : public UHBUserWidgetBase
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


