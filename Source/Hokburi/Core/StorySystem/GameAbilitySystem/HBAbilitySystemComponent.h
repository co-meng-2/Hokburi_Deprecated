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
	virtual void InitializeComponent() override;
	virtual void BeginPlay() override;

	// Attribute
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Hokburi | Attribute")
	TArray<TSubclassOf<UAttributeSet>> OwningAttributeClasses;
	virtual void RegisterAttributes();

	UPROPERTY(EditAnywhere, Category = "Hokburi | Attribute")
	TSubclassOf<UGameplayEffect> GE_InitAttribute;

	// Ability 관련된 것들 제거
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
