// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HBCharacterBase.h"

#include "Core/CommandSystem/HBCommandHandler.h"
#include "Core/StorySystem/GameAbilitySystem/HBAbilitySystemComponent.h"

// Sets default values
AHBCharacterBase::AHBCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// BP로 위임 -> SelectableInterface 구현 -> GetCommandHandler구현 강제됨. -> CommandHandler추가할지 말지 결정.
	// CommandHandler = CreateDefaultSubobject<UHBCommandHandler>(FName("CommandHandler"));

	ASC = CreateDefaultSubobject<UHBAbilitySystemComponent>(FName("AbilitySystemComponent"));
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AHBCharacterBase::BeginPlay()
{
	Super::BeginPlay();
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

