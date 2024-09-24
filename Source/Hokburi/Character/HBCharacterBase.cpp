// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HBCharacterBase.h"

#include "Core/CommandSystem/HBCommandHandler.h"

// Sets default values
AHBCharacterBase::AHBCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CommandHandler = CreateDefaultSubobject<UHBCommandHandler>(FName("CommandHandler"));
}

// Called when the game starts or when spawned
void AHBCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	CommandHandler->bCanMove = true;
}

// Called every frame
void AHBCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHBCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UHBCommandHandler* AHBCharacterBase::GetCommandHandler()
{
	return CommandHandler;
}

