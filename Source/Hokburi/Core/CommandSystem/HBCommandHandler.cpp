// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/CommandSystem/HBCommandHandler.h"

#include "AIController.h"
#include "AI/HBAIControllerBase.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

void UHBCommand::RunCommand_Implementation(AActor* Actor, UBlackboardComponent* BB)
{
}

void UHBCommand_MoveToLocation::RunCommand_Implementation(AActor* Actor, UBlackboardComponent* BB)
{
	auto BT = BB->GetOwner<AAIController>()->GetComponentByClass<UBehaviorTreeComponent>();
	BT->RestartTree(EBTRestartMode::ForceReevaluateRootNode);
	BB->SetValueAsBool(FName("JustMove"), true);
	BB->SetValueAsObject(FName("TargetActor"), nullptr);
	BB->SetValueAsVector(FName("TargetLocation"), DestLocation);
}

void UHBCommand_MoveToActor::RunCommand_Implementation(AActor* Actor, UBlackboardComponent* BB)
{
	Super::RunCommand_Implementation(Actor, BB);
	if (!Target.IsValid()) return;

	BB->SetValueAsBool(FName("JustMove"), true);
	BB->SetValueAsObject(FName("TargetActor"), Target.Get());
}

void UHBCommand_AttackToLocation::RunCommand_Implementation(AActor* Actor, UBlackboardComponent* BB)
{
	BB->SetValueAsBool(FName("HasLocation"), true);
	BB->SetValueAsVector(FName("TargetLocation"), DestLocation);
}

void UHBCommand_AttackToActor::RunCommand_Implementation(AActor* Actor, UBlackboardComponent* BB)
{
}


//void UHBCommandHandler::EnqueueCommand(UHBCommand* NewCommand)
//{
//	CommandQueue.Enqueue(NewCommand);
//	NewCommand->AddToRoot();
//	
//	GetBlackBoard()->SetValueAsBool(FName("HasCommand"), true);
//}
//
//bool UHBCommandHandler::DequeueCommand()
//{
//	if (CommandQueue.IsEmpty())
//	{
//		return false;
//	}
//
//	UHBCommand* OutCommand = nullptr;
//	CommandQueue.Dequeue(OutCommand);
//	OutCommand->RemoveFromRoot();
//
//	if (CommandQueue.IsEmpty())
//		GetBlackBoard()->SetValueAsBool(FName("HasCommand"), false);
//	return true;
//}
//
//const UHBCommand* UHBCommandHandler::PeekCommand()
//{
//	if (CommandQueue.IsEmpty()) 
//		return nullptr;
//	return *CommandQueue.Peek();
//}

