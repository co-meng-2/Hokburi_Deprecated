// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "HBBTTask.generated.h"

namespace EPathFollowingResult
{
	enum Type : int;
}

/**
 * 
 */

UCLASS()
class HOKBURI_API UHBBTTask_MoveTo : public UBTTask_MoveTo
{
	GENERATED_BODY()
public:
	UHBBTTask_MoveTo();
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	// 고정된 적에게 공격하러 이동. -> Acceptable Radius 자신의 공격 Radius로 조절
	UPROPERTY(EditAnywhere)
	bool MoveToAttackTarget = false;
};
UCLASS()
class HOKBURI_API UHBBTTask_TurnToTarget : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UHBBTTask_TurnToTarget();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere)
	float TurnSpeed = 5.f;
	UPROPERTY(EditAnywhere)
	float RotationDiffThreshold = 1.f;
};

UCLASS()
class HOKBURI_API UHBBTTask_Attack : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UHBBTTask_Attack();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

	UBehaviorTreeComponent* CachedBT;

public:
	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

private:
	bool bMontageEnded = false;
};