// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTree/Decorator/HBBTDecorators.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/Components/HBCombatComponent.h"

bool UHBBTD_DetectEnemy::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	auto CombatComponent = OwnerComp.GetOwner<AAIController>()->GetPawn()->GetComponentByClass<UHBCombatComponent>();
	auto BB = OwnerComp.GetBlackboardComponent();

	auto Obj = BB->GetValueAsObject(GetSelectedBlackboardKey());
	if (IsValid(Obj))
		return true;
	
	if (CombatComponent->OverlappedActors.IsEmpty())
	{
		BB->SetValueAsObject(GetSelectedBlackboardKey(), nullptr);
		return false;
	}

	BB->SetValueAsObject(GetSelectedBlackboardKey(), CombatComponent->GetNearestActor());
	return true;
}

bool UHBBTD_ValidCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	auto CombatComponent = OwnerComp.GetOwner<AAIController>()->GetPawn()->GetComponentByClass<UHBCombatComponent>();
	auto BB = OwnerComp.GetBlackboardComponent();
	auto Obj = BB->GetValueAsObject(GetSelectedBlackboardKey());
	if(IsValid(Obj))
	{
		return true;
	}
	BB->SetValueAsObject(GetSelectedBlackboardKey(), nullptr);
	return false;
}


