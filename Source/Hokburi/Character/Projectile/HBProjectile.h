// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Engine/StaticMeshActor.h"
#include "NiagaraSystem.h"
#include "HBProjectile.generated.h"


class UHBTeamComponent;
class UProjectileMovementComponent;
/**
 * 
 */
UCLASS()
class HOKBURI_API AHBProjectile : public AStaticMeshActor
{
	GENERATED_BODY()
public:
	AHBProjectile();
	virtual void BeginPlay() override;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hokburi | Component")
	UProjectileMovementComponent* MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Hokburi | Niagara")
	UNiagaraSystem* StartFX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hokburi | Niagara")
	UNiagaraSystem* PersistentFX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hokburi | Niagara")
	UNiagaraSystem* EndFX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hokburi")
	float LifeTime = 3.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hokburi")
	FName CollisionProfileName;

	bool IsGuided = false;
	TWeakObjectPtr<AActor> Target;

public:
	UPROPERTY(BlueprintReadOnly)
	TArray<FGameplayEffectSpecHandle> GEHandles;

public:
	UFUNCTION()
	void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
