// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Components/HBCombatComponent.h"

#include "AbilitySystemInterface.h"
#include "Core/StorySystem/GameAbilitySystem/HBAbilitySystemComponent.h"

void UHBCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	if (IsMelee)
	{
		SetSphereRadius(MeleeAttackDetectionRadius);
	}
	else
	{
		SetSphereRadius(AttackRadius * RangeAttackDetectionRadiusMultiplier);
	}

	if(GA_Attack)
	{
		auto ASC = Cast<IAbilitySystemInterface>(GetOwner())->GetAbilitySystemComponent();
		GA_Attack_Handle = ASC->GiveAbility(FGameplayAbilitySpec(GA_Attack));
	}
}

bool UHBCombatComponent::Attack()
{
	auto ASC = Cast<IAbilitySystemInterface>(GetOwner())->GetAbilitySystemComponent();
	return ASC->TryActivateAbility(GA_Attack_Handle);
}

void UHBCombatComponent::OnBeginOverlap(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	OverlappedActors.Push(OtherActor);
}

void UHBCombatComponent::OnEndOverlap(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OverlappedActors.Remove(OtherActor);
}

AActor* UHBCombatComponent::GetNearestActor()
{
	AActor* NearestActor = nullptr;
	float NearestDist = FLT_MAX;

	for(auto Actor : OverlappedActors)
	{
		float DistanceSq = (GetComponentLocation() - Actor->GetActorLocation()).SizeSquared();
		if(NearestDist > DistanceSq)
		{
			NearestDist = DistanceSq;
			NearestActor = Actor;
		}
	}
	
	CachedNearestActor = NearestActor;
	return NearestActor;
}
