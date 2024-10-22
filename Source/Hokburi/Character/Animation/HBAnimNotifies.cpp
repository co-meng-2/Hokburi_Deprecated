// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Animation/HBAnimNotifies.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Character/Components/HBAttackCollisionComponent.h"
#include "Components/SphereComponent.h"

void UHBAnimNotify_TriggerEvent::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if(MeshComp && MeshComp->GetOwner())
	{

        // AbilitySystemComponent를 가져옴
        auto ASC = Cast<IAbilitySystemInterface>(MeshComp->GetOwner())->GetAbilitySystemComponent();
        if (ASC && EventTag.IsValid())
        {
            // GameplayEvent 데이터 생성
            FGameplayEventData EventData;
            EventData.Instigator = MeshComp->GetOwner();
            EventData.Target = MeshComp->GetOwner();
            EventData.EventTag = EventTag;

            // 이벤트 브로드캐스트
            ASC->HandleGameplayEvent(EventTag, &EventData);
        }
	}
}

void UHBAnimNotifyState_CollisionOnOff::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

    auto Actor = MeshComp->GetOwner();
    if (auto AttackCollision = Actor->FindComponentByClass<UHBAttackCollisionComponent>())
    {
        AttackCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    }
}

void UHBAnimNotifyState_CollisionOnOff::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

    auto Actor = MeshComp->GetOwner();
    if (auto AttackCollision = Actor->FindComponentByClass<UHBAttackCollisionComponent>())
    {
        AttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
}

