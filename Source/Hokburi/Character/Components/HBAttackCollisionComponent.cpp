// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Components/HBAttackCollisionComponent.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"

void UHBAttackCollisionComponent::BeginPlay()
{
	Super::BeginPlay();
	SetCollisionProfileName(CollisionProfileName.Name, true);
	OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
}

void UHBAttackCollisionComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    UAbilitySystemComponent* AbilitySystemComponent = Cast<IAbilitySystemInterface>(GetOwner())->GetAbilitySystemComponent();
    if (AbilitySystemComponent && EventTag.IsValid())
    {
        // GameplayEvent 데이터 생성
        FGameplayEventData EventData;
        EventData.Instigator = GetOwner();
        EventData.Target = OtherActor;
        EventData.EventTag = EventTag;

        FGameplayAbilityTargetData_ActorArray* NewData = new FGameplayAbilityTargetData_ActorArray();
        TArray<AActor*> TargetActors;
        TargetActors.Push(OtherActor);
        NewData->TargetActorArray.Append(TargetActors);
        EventData.TargetData.Add(NewData);

        // 이벤트 브로드캐스트
        AbilitySystemComponent->HandleGameplayEvent(EventTag, &EventData);
    }
}
