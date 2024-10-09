// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/CommandSystem/HBCommandHandler.h"

#include "AIController.h"
#include "AI/HBAIControllerBase.h"
#include "BehaviorTree/BlackboardComponent.h"

void UHBCommand_Move::RunCommand_Implementation(AActor* Actor)
{
	Super::RunCommand_Implementation(Actor);
	if( auto Pawn = Cast<APawn>(Actor))
	{
		if(auto Controller = Pawn->GetController())
		{
			if(auto AIController = Cast<AAIController>(Controller))
			{
				EPathFollowingRequestResult::Type RetType = AIController->MoveToLocation(DestLocation);
			}
		}
	}
}

UBlackboardComponent* UHBCommandHandler::GetBlackBoard()
{
	auto Controller = Cast<AHBAIControllerBase>(Cast<APawn>(GetOwner())->GetController());
	auto BB = Controller->GetBlackboardComponent();
	return BB;
}


void UHBCommandHandler::EnqueueCommand(UHBCommand* NewCommand)
{
	CommandQueue.Enqueue(NewCommand);
	NewCommand->AddToRoot();
	
	GetBlackBoard()->SetValueAsBool(FName("HasCommand"), true);
}

bool UHBCommandHandler::DequeueCommand()
{
	if (CommandQueue.IsEmpty())
	{
		return false;
	}

	UHBCommand* OutCommand = nullptr;
	CommandQueue.Dequeue(OutCommand);
	OutCommand->RemoveFromRoot();

	if (CommandQueue.IsEmpty())
		GetBlackBoard()->SetValueAsBool(FName("HasCommand"), false);
	return true;
}

const UHBCommand* UHBCommandHandler::PeekCommand()
{
	if (CommandQueue.IsEmpty()) 
		return nullptr;
	return *CommandQueue.Peek();
}

