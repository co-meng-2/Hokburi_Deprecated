// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HBPlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "AbilitySystemInterface.h"
#include "HBPlayerControllerBase.generated.h"


class UHBPlayerWidgetComponent;
class AHBPlayerCharacter;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */


UCLASS()
class HOKBURI_API AHBPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	AHBPlayerControllerBase();
	virtual void BeginPlay() override;

public:
	AActor* GetActorUnderCursor();
	virtual void Tick(float DeltaSeconds) override;

	// Input
public:
	UPROPERTY(EditDefaultsOnly, Category = "Hokburi | Input")
	UInputMappingContext* IMC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hokburi | Input")
	UInputAction* IA_Select;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hokburi | Input")
	UInputAction* IA_Command;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Hokburi | Input")
	TArray<UInputAction*> IA_ActivateStoryArray;

	virtual void SetupInputComponent() override;
private:
	void ActivateStory(EStoryMappingKey::Key Key);

	// Selected
private:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Hokburi | Selected")
	TWeakObjectPtr<AActor>  SelectedActor;
	TWeakObjectPtr<AActor>  CachedActor;

	void SelectActor();
	void CommandSelectedActor();

public:
	UFUNCTION(BlueprintCallable)
	AActor* GetSelectedActor() { return SelectedActor.Get(); }
	UFUNCTION(BlueprintCallable)
	void SetSelectedActor(AActor* NewActor) { SelectedActor = NewActor; }
	AHBPlayerCharacter* GetMainCharacter();

	// UI
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UHBPlayerWidgetComponent* PlayerWidgetComponent;

	// PostProcess
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hokburi | PostProcess")
	uint8 SelectedStencilValue = 2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hokburi | PostProcess")
	uint8 UnderCursorStencilValue = 1;
};
