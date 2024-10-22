// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/StorySystem/GameAbilitySystem/AbilityTask/HBAbilityTasks.h"

#include "Core/StorySystem/GameAbilitySystem/HBAbilitySystemComponent.h"

UHBAbilityTask_PlayMontageAndWaitEvent* UHBAbilityTask_PlayMontageAndWaitEvent::CreatePlayMontage(UGameplayAbility* OwningAbility, UAnimMontage* MontageToPlay, 
	FGameplayTagContainer EventTags, float Rate)
{
	UHBAbilityTask_PlayMontageAndWaitEvent* MyObj = NewAbilityTask<UHBAbilityTask_PlayMontageAndWaitEvent>(OwningAbility);
	MyObj->Montage = MontageToPlay;
	MyObj->Rate = Rate;
	MyObj->EventTags = EventTags;
	return MyObj;
}

void UHBAbilityTask_PlayMontageAndWaitEvent::OnMontageEnded(UAnimMontage* CurMontage, bool bInterrupted)
{
	EndTask();
}

void UHBAbilityTask_PlayMontageAndWaitEvent::OnDestroy(bool bInOwnerFinished)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		// EndAbility 담당
		OnTaskFinsihDelegate.Broadcast(FGameplayTag(), FGameplayEventData());
	}

	AbilitySystemComponent.Get()->RemoveGameplayEventTagContainerDelegate(EventTags, EventHandle);

	Super::OnDestroy(bInOwnerFinished);
}

void UHBAbilityTask_PlayMontageAndWaitEvent::OnGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* EventData)
{
	if(ShouldBroadcastAbilityTaskDelegates())
	{
		FGameplayEventData TempData = *EventData;
		OnEventReceived.Broadcast(EventTag, TempData);
	}
}

void UHBAbilityTask_PlayMontageAndWaitEvent::Activate()
{
	if(Ability == nullptr)
	{
		return;
	}

	UHBAbilitySystemComponent* ASC = Cast<UHBAbilitySystemComponent>(AbilitySystemComponent.Get());
	if(ASC == nullptr)
	{
		return;
	}
	EventHandle = ASC->AddGameplayEventTagContainerDelegate(EventTags, FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this, &UHBAbilityTask_PlayMontageAndWaitEvent::OnGameplayEvent));

	ASC->PlayMontage(Ability, Ability->GetCurrentActivationInfo(), Montage, Rate);

	const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
	UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();

	MontageEndedDelegate.BindUObject(this, &ThisClass::OnMontageEnded);
	AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate ,Montage);
}




