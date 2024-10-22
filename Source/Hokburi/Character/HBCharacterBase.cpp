// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HBCharacterBase.h"

#include "Components/DecalComponent.h"
#include "Components/HBCharacterWidgetComponent.h"
#include "Components/HBCombatComponent.h"
#include "Components/HBDataComponent.h"
#include "Core/StorySystem/GameAbilitySystem/HBAbilitySystemComponent.h"
#include "Core/TeamSystem/HBTeamSystem.h"

// Sets default values
AHBCharacterBase::AHBCharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// BP로 위임 -> SelectableInterface 구현 -> GetCommandHandler구현 강제됨. -> CommandHandler추가할지 말지 결정.
	// CommandHandler = CreateDefaultSubobject<UHBCommandHandler>(FName("CommandHandler"));
	ASC = ObjectInitializer.CreateOptionalDefaultSubobject<UHBAbilitySystemComponent>(this, TEXT("AbilitySystemComponent"));

	CharacterWidgetComponent = CreateDefaultSubobject<UHBCharacterWidgetComponent>(FName("CharacterWidgetComponent"));
	CharacterWidgetComponent->SetupAttachment(RootComponent);
	CharacterWidgetComponent->SetDrawSize(FVector2D(200.0f, 50.0f)); // 크기 설정
	CharacterWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);

	DecalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalCompoent"));
	DecalComponent->SetupAttachment(RootComponent);
	DecalComponent->Deactivate();
	DecalComponent->SetVisibility(false);

	TeamComponent = CreateDefaultSubobject<UHBTeamComponent>(TEXT("TeamComponent"));

	CombatComponent = CreateDefaultSubobject<UHBCombatComponent>(FName("CombatComponent"));
	CombatComponent->SetupAttachment(RootComponent);
	CombatComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CombatComponent->OnComponentBeginOverlap.AddDynamic(CombatComponent, &UHBCombatComponent::OnBeginOverlap);
	CombatComponent->OnComponentEndOverlap.AddDynamic(CombatComponent, &UHBCombatComponent::OnEndOverlap);

	DataComponent = CreateDefaultSubobject<UHBDataComponent>(FName("DataComponent"));

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}
// Called to bind functionality to input
void AHBCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UAbilitySystemComponent* AHBCharacterBase::GetAbilitySystemComponent() const
{
	return ASC;
}