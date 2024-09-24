// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Navigation/PathFollowingComponent.h"
#include "UObject/NoExportTypes.h"
#include "HBCommandHandler.generated.h"

class UBlackboardComponent;
class UHBCommandHandler;
struct FAIRequestID;

UCLASS(Abstract)
class HOKBURI_API UHBCommand : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Execute(AActor* Actor);

	TWeakObjectPtr<UHBCommandHandler> Owner;

	virtual void Execute_Implementation(AActor* Actor){};
};

UCLASS()
class UHBCommand_Move : public UHBCommand
{
	GENERATED_BODY()
private:
	FVector DestLocation;

public:
	virtual void Execute_Implementation(AActor* Actor) override;
	void SetDestLocation(FVector NewLoc) { DestLocation = NewLoc; };
};

UCLASS()
class HOKBURI_API UHBCommandHandler : public UActorComponent
{
	GENERATED_BODY()

private:
	TQueue<UHBCommand*> CommandQueue;

public:
	UBlackboardComponent* GetBlackBoard();
	// TQueue<UHBCommand> CommandQueue; Object를 상속받는 Class에 대해서는 이것이 권장되지 않을 뿐더러 복사생성자가 모호함.
	UFUNCTION(BlueprintCallable)
	void EnqueueCommand(UHBCommand* NewCommand);
	UFUNCTION(BlueprintCallable)
	bool PopCommand();
	UFUNCTION(BlueprintCallable)
	const UHBCommand* PeekCommand();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanMove;
};
