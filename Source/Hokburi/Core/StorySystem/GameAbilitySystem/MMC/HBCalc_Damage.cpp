// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/StorySystem/GameAbilitySystem/MMC/HBCalc_Damage.h"

#include "Core/StorySystem/GameAbilitySystem/HBAttributeSets.h"

UHBCalc_Damage::UHBCalc_Damage()
{
	AttackPointDef.AttributeToCapture = UHBAttackAttributeSet::GetAttackPointAttribute();
	AttackPointDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	AttackPointDef.bSnapshot = true;

	RelevantAttributesToCapture.Add(AttackPointDef);
}

float UHBCalc_Damage::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;

	float AttackPoint = 0.f;
	GetCapturedAttributeMagnitude(AttackPointDef, Spec, EvaluateParameters, AttackPoint);

	return AttackPoint;
}

UHBCalc_ApplyDamage::UHBCalc_ApplyDamage()
{
	HealthDef.AttributeToCapture = UHBHealthAttributeSet::GetHealthAttribute();
	HealthDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	HealthDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(HealthDef);
}

float UHBCalc_ApplyDamage::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;

	float Damage = GetSetByCallerMagnitudeByTag(Spec, FGameplayTag::RequestGameplayTag(FName("GE.Caller.Damage")));

	float Health = 0.f;
	GetCapturedAttributeMagnitude(HealthDef, Spec, EvaluateParameters, Health);
	Health -= Damage;
	Health = FMath::Max<float>(0.f, Health);

	return Health;
}
