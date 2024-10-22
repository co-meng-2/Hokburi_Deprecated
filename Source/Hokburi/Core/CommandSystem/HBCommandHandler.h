// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/HBObject.h"
#include "HBCommandHandler.generated.h"

class UBlackboardComponent;
class UHBCommandHandler;
struct FAIRequestID;

UCLASS(Abstract, Blueprintable)
class HOKBURI_API UHBCommand : public UHBObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void RunCommand(AActor* Actor, UBlackboardComponent* BB);

	virtual void RunCommand_Implementation(AActor* Actor, UBlackboardComponent* BB);
};

UCLASS()
class UHBCommand_MoveToLocation : public UHBCommand
{
	GENERATED_BODY()
private:
	FVector DestLocation;

public:
	virtual void RunCommand_Implementation(AActor* Actor, UBlackboardComponent* BB) override;
	void SetDestLocation(FVector NewLoc) { DestLocation = NewLoc; };
};

UCLASS()
class UHBCommand_MoveToActor : public UHBCommand
{
	GENERATED_BODY()
private:
	TWeakObjectPtr<AActor> Target;

public:
	virtual void RunCommand_Implementation(AActor* Actor, UBlackboardComponent* BB) override;
	void SetTarget(AActor* NewTarget) { Target = NewTarget; }
};

UCLASS()
class UHBCommand_AttackToLocation : public UHBCommand
{
	GENERATED_BODY()
private:
	FVector DestLocation;

public:
	virtual void RunCommand_Implementation(AActor* Actor, UBlackboardComponent* BB) override;
	void SetDestLocation(FVector NewLoc) { DestLocation = NewLoc; };
};

UCLASS()
class UHBCommand_AttackToActor : public UHBCommand
{
	GENERATED_BODY()
private:
	TWeakObjectPtr<AActor> Target;

public:
	virtual void RunCommand_Implementation(AActor* Actor, UBlackboardComponent* BB) override;
	void SetTarget(AActor* NewTarget) { Target = NewTarget; }
};

UCLASS(BlueprintType, meta = (BlueprintSpawnableComponent))
class HOKBURI_API UHBCommandHandler : public UActorComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hokburi | Able Command")
	bool bCanMove;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hokburi | Able Command")
	bool bCanAttack;
};

// @HB-Todo: 연속된 Command를 구현하고 싶었는데 생각보다 도전적인 과제인 것 같다. 나중에 해보자.
// TQueue<UHBCommand> CommandQueue; Object를 상속받는 Class에 대해서는 이것이 권장되지 않을 뿐더러 복사생성자가 모호함.
//TQueue<UHBCommand*> CommandQueue;
//UFUNCTION(BlueprintCallable)
//void EnqueueCommand(UHBCommand* NewCommand);
//UFUNCTION(BlueprintCallable)
//bool DequeueCommand();
//UFUNCTION(BlueprintCallable)
//const UHBCommand* PeekCommand();