// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Animation/HBAnimInstanceBase.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UHBAnimInstanceBase::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<ACharacter>(GetOwningActor());
	if (!Character) return;

	CharacterMovementComp = Character->GetCharacterMovement();
}

void UHBAnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!Character) return;

	Velocity = CharacterMovementComp->Velocity;
	Velocity.Z = 0.f;
	GroundSpeed = Velocity.Length();
	ShouldMove = (GroundSpeed > 3.f);
}
