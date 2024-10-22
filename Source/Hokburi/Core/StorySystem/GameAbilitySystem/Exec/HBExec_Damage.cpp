// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/StorySystem/GameAbilitySystem/Exec/HBExec_Damage.h"

#include "Core/StorySystem/GameAbilitySystem/HBAttributeSets.h"

struct HBDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPoint);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);

	HBDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UHBAttackAttributeSet, AttackPoint, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UHBHealthAttributeSet, Health, Target, false);
	}
};

static const HBDamageStatics& DamageStatics()
{
	static HBDamageStatics DStatics;
	return DStatics;
}


UHBExec_Damage::UHBExec_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().HealthDef);
	RelevantAttributesToCapture.Add(DamageStatics().AttackPointDef);
}

void UHBExec_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                            FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();

	AActor* SourceActor = SourceAbilitySystemComponent ? SourceAbilitySystemComponent->GetAvatarActor() : nullptr;
	AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	// Gather the tags from the source and target as that can affect which buffs should be used
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Health = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().HealthDef, EvaluationParameters, Health);

	float AttackPoint = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().AttackPointDef, EvaluationParameters, AttackPoint);
	AttackPoint *= -1.f;

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().HealthProperty, EGameplayModOp::Additive, AttackPoint));
}
