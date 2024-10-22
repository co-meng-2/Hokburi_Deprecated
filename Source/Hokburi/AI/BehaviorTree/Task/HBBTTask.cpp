// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTree/Task/HBBTTask.h"

#include "AIController.h"
#include "Abilities/GameplayAbility.h"
#include "AI/NavigationSystemBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/Components/HBCombatComponent.h"
#include "Core/HBBlueprintFunctionLibrary.h"
#include "Core/StorySystem/GameAbilitySystem/HBGameplayAbility.h"
#include "Navigation/PathFollowingComponent.h"


UHBBTTask_MoveTo::UHBBTTask_MoveTo()
{
	bNotifyTaskFinished = true;
}

void UHBBTTask_MoveTo::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
                                      EBTNodeResult::Type TaskResult)
{
	auto BB = OwnerComp.GetBlackboardComponent();
	if (BB->GetValueAsBool("JustMove"))
	{
		BB->SetValueAsBool("JustMove", false);
		BB->SetValueAsObject("TargetActor", nullptr);
	}

	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}

EBTNodeResult::Type UHBBTTask_MoveTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (MoveToAttackTarget)
	{
		auto CombatComp = OwnerComp.GetOwner<AAIController>()->GetPawn()->GetComponentByClass<UHBCombatComponent>();
		AcceptableRadius = CombatComp->AttackRadius;
	}

	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

UHBBTTask_TurnToTarget::UHBBTTask_TurnToTarget()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UHBBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::InProgress;
}

void UHBBTTask_TurnToTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	static FName TargetActorName = FName("TargetActor");
	auto BB = OwnerComp.GetBlackboardComponent();
	AActor* TargetActor = Cast<AActor>(BB->GetValueAsObject(TargetActorName));
	AActor* SourceActor = OwnerComp.GetOwner<AAIController>()->GetPawn();

	if(IsValid(TargetActor))
	{
		FVector Direction =  TargetActor->GetActorLocation() - SourceActor->GetActorLocation();
		Direction.Normalize();

		FRotator LookAtRotation = Direction.Rotation();
		FRotator CurRotation = SourceActor->GetActorRotation();

		SourceActor->SetActorRotation(FMath::RInterpTo(CurRotation, LookAtRotation, DeltaSeconds, TurnSpeed));
		if(UHBUtilityBFL::IsRotationDifferenceSmall(CurRotation, LookAtRotation, RotationDiffThreshold))
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
	else
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

}

UHBBTTask_Attack::UHBBTTask_Attack()
{
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UHBBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto AIController = OwnerComp.GetOwner<AAIController>();
	auto CombatComponent = AIController->GetPawn()->GetComponentByClass<UHBCombatComponent>();
	auto AnimInstance = AIController->GetPawn()->GetComponentByClass<USkeletalMeshComponent>()->GetAnimInstance();
	bool AttackSucceed = CombatComponent->Attack();
	CachedBT = &OwnerComp;
	
	if(AttackSucceed == false)
	{
		return EBTNodeResult::Failed;
	}
	AnimInstance->OnMontageEnded.AddDynamic(this, &ThisClass::OnMontageEnded);
	bMontageEnded = false;

	return EBTNodeResult::InProgress;
}

void UHBBTTask_Attack::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);

	auto AIController = OwnerComp.GetOwner<AAIController>();
	if (!AIController) return;

	auto Pawn = AIController->GetPawn();
	if (!Pawn) return;

	auto AnimInstance = Pawn->GetComponentByClass<USkeletalMeshComponent>()->GetAnimInstance();

	if (AnimInstance)
	{
		if(bMontageEnded == false)
		{
			AnimInstance->Montage_Stop(0.1f);
		}
		AnimInstance->OnMontageEnded.RemoveDynamic(this, &ThisClass::OnMontageEnded);
	}
}

void UHBBTTask_Attack::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	FinishLatentTask(*CachedBT, EBTNodeResult::Succeeded);
	bMontageEnded = true;
}

