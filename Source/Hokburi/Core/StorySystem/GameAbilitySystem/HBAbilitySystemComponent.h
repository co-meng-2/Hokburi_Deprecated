// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "HBAttributeSets.h"
#include "HBAbilitySystemComponent.generated.h"

class AHBPlayerControllerBase;
class UHBPlayerWidget;
/**
 * 
 */
UCLASS(Blueprintable, meta =(BlueprintSpawnableComponent))
class HOKBURI_API UHBAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	// 동적으로 AttributeSet 정의
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<TSubclassOf<UAttributeSet>> OwningAttributeClasses;

public:
	void RemoveActiveGEFromAbilitySpec(const FGameplayAbilitySpecHandle GASpecHandle);

	struct FAbilityRelated
	{
		TArray<TWeakObjectPtr<AActor>>	RelatedActors;
		TArray<FActiveGameplayEffectHandle>	RelatedActiveGEHandles;
	};

	TMap<FGameplayAbilitySpecHandle, FAbilityRelated> GARelatedMap;
	UFUNCTION(BlueprintCallable)
	void RegisterGARelatedMap(FGameplayAbilitySpecHandle GASpecHandle, AActor* RelatedActor, FActiveGameplayEffectHandle ActiveGEHandle);
};
