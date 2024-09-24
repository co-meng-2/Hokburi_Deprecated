// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HBPlayerControllerBase.generated.h"

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
	virtual void SetupInputComponent() override;
	AActor* GetActorUnderCursor();
	virtual void Tick(float DeltaSeconds) override;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Hokburi | Input")
	UInputMappingContext* IMC;

	// Actor 선택
private:
	// @HB-Todo : Interface만들어서 선택가능한 Actor들 상호작용 정의
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<AActor>  SelectedActor;
	TWeakObjectPtr<AActor>  CachedActor;

	void SelectActor();
	void CommandSelectedActor();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* IA_Select;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* IA_Command;

	UFUNCTION(BlueprintCallable)
	AActor* GetSelectedActor() { return SelectedActor.Get(); };
	UFUNCTION(BlueprintCallable)
	void SetSelectedActor(AActor* NewActor) { SelectedActor = NewActor; };
};
