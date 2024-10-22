// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "HBBTDecorators.generated.h"

/**
 * 
 */
UCLASS()
class HOKBURI_API UHBBTD_DetectEnemy : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
public:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};

UCLASS()
class HOKBURI_API UHBBTD_ValidCheck : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
public:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};