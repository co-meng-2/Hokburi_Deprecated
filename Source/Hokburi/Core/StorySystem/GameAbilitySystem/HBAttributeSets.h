// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "HBAttributeSets.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedDelegate, float, Changed);

/**
 * AttributeSet 모음
 */

UCLASS()
class HOKBURI_API UHBAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()

public:
	TMap<FGameplayAttribute, FOnAttributeChangedDelegate> AttributeChangedDelegateMap;

	FOnAttributeChangedDelegate* GetChangedDelegate(FGameplayAttribute Attribute)
	{
		return &AttributeChangedDelegateMap.FindOrAdd(Attribute);
	};

	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
};

UCLASS()
class HOKBURI_API UHBHealthAttributeSet : public UHBAttributeSetBase
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FGameplayAttributeData Health;
	UPROPERTY()
	FGameplayAttributeData MaxHealth;
	UPROPERTY()
	FGameplayAttributeData HealthRegen;

public:
	ATTRIBUTE_ACCESSORS(UHBHealthAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UHBHealthAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UHBHealthAttributeSet, HealthRegen);
};

UCLASS()
class HOKBURI_API UHBAttackAttributeSet : public UHBAttributeSetBase
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FGameplayAttributeData AttackPoint;
	UPROPERTY()
	FGameplayAttributeData AttackSpeed;
	// meta Attribute
	UPROPERTY()
	FGameplayAttributeData Damage;

public:
	ATTRIBUTE_ACCESSORS(UHBAttackAttributeSet, AttackPoint);
	ATTRIBUTE_ACCESSORS(UHBAttackAttributeSet, AttackSpeed);
	ATTRIBUTE_ACCESSORS(UHBAttackAttributeSet, Damage);
};
