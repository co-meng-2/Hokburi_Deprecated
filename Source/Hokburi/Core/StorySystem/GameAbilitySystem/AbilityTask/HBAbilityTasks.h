// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "HBAbilityTasks.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHBPlayMontageAndWaitForEventDelegate, FGameplayTag, EventTag, FGameplayEventData, EventData);

UCLASS()
class HOKBURI_API UHBAbilityTaskBase : public UAbilityTask
{
	GENERATED_BODY()
	
};

UCLASS()
class HOKBURI_API UHBAbilityTask_PlayMontageAndWaitEvent : public UHBAbilityTaskBase
{
	GENERATED_BODY()
public:
	virtual void Activate() override;
	UFUNCTION(BlueprintCallable, meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UHBAbilityTask_PlayMontageAndWaitEvent* CreatePlayMontage(UGameplayAbility* OwningAbility, UAnimMontage* MontageToPlay, FGameplayTagContainer EventTags, float Rate = 1.f);

public:
	UAnimMontage* Montage;
	float Rate;

	FOnMontageEnded MontageEndedDelegate;
	UFUNCTION()
	void OnMontageEnded(UAnimMontage* CurMontage, bool bInterrupted);

	UPROPERTY(BlueprintAssignable)
	FHBPlayMontageAndWaitForEventDelegate OnTaskFinsihDelegate;
	void OnDestroy(bool bInOwnerFinished) override;

	// Event
public:
	FGameplayTagContainer EventTags;
	FDelegateHandle EventHandle;
	void OnGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* EventData);
	UPROPERTY(BlueprintAssignable)
	FHBPlayMontageAndWaitForEventDelegate OnEventReceived;

	//UPROPERTY(BlueprintAssignable)
	//FMontageWaitSimpleDelegate	OnCompleted;

	//UPROPERTY(BlueprintAssignable)
	//FMontageWaitSimpleDelegate	OnBlendOut;

	//UPROPERTY(BlueprintAssignable)
	//FMontageWaitSimpleDelegate	OnInterrupted;

	//UPROPERTY(BlueprintAssignable)
	//FMontageWaitSimpleDelegate	OnCancelled;

	//UFUNCTION()
	//void OnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted);
	//UFUNCTION()
	//void OnGameplayAbilityCancelled();

};
