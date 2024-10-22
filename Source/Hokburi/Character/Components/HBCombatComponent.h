// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "Components/SphereComponent.h"
#include "HBCombatComponent.generated.h"


class UGameplayAbility;
class UHBGameplayAbility_PlayMontage;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HOKBURI_API UHBCombatComponent : public USphereComponent
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hokburi | Attack")
	bool IsMelee;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hokburi | Attack")
	float MeleeAttackDetectionRadius = 700.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hokburi | Attack")
	float RangeAttackDetectionRadiusMultiplier = 1.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Hokburi | Attack" )
	float AttackRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hokburi | Attack")
	TSubclassOf<UGameplayAbility> GA_Attack;

	FGameplayAbilitySpecHandle GA_Attack_Handle;
	bool Attack();

public:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	AActor* GetNearestActor();
	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<AActor> CachedNearestActor;

	TArray<AActor*> OverlappedActors;
};
