// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Projectile/HBProjectile.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Core/TeamSystem/HBTeamSystem.h"
#include "GameFramework/ProjectileMovementComponent.h"

AHBProjectile::AHBProjectile()
{
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
}

void AHBProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeTime);
	GetStaticMeshComponent()->SetCollisionProfileName(CollisionProfileName);
	OnActorBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
}

void AHBProjectile::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	auto AbilityInterface = Cast<IAbilitySystemInterface >(OtherActor);
	if (AbilityInterface == nullptr) return;

	if(auto ASC = AbilityInterface->GetAbilitySystemComponent())
	{
		for (const auto& GEHandle : GEHandles)
		{
			ASC->ApplyGameplayEffectSpecToSelf(*GEHandle.Data.Get());
		}
	}
	Destroy();
}
