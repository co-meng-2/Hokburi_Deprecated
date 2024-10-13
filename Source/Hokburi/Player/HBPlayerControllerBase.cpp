// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/HBPlayerControllerBase.h"

#include "AIController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "HBPlayerState.h"
#include "Components/DecalComponent.h"
#include "Components/HBPlayerWidgetComponent.h"
#include "Core/CommandSystem/HBCommandHandler.h"
#include "Core/StorySystem/GameAbilitySystem/HBAbilitySystemComponent.h"
#include "Engine/LocalPlayer.h"
#include "Interface/HBSelectableInterface.h"

AHBPlayerControllerBase::AHBPlayerControllerBase()
{
	PlayerWidgetComponent = CreateDefaultSubobject<UHBPlayerWidgetComponent>(FName("PlayerWidgetComponent"));
	bShowMouseCursor = true;
}

void AHBPlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();
	UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	EnhancedInputSubsystem->AddMappingContext(IMC, 0);

	SetInputMode(FInputModeGameAndUI());
	// 마우스 화면에 가두기.
	// SetInputMode(FInputModeGameAndUI().SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways));
}

void AHBPlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EIComp = Cast<UEnhancedInputComponent>(InputComponent);
	EIComp->BindAction(IA_Select, ETriggerEvent::Triggered, this, &ThisClass::SelectActor);
	EIComp->BindAction(IA_Command, ETriggerEvent::Triggered, this, &ThisClass::CommandSelectedActor);

	for(int i = EStoryMappingKey::E_Start; i < EStoryMappingKey::END; ++i)
	{
		EStoryMappingKey::Key Key = static_cast<EStoryMappingKey::Key>(i);
		EIComp->BindAction<>(IA_ActivateStoryArray[Key], ETriggerEvent::Triggered, this, &ThisClass::ActivateStory, Key);
	}
}

void AHBPlayerControllerBase::ActivateStory(EStoryMappingKey::Key Key)
{
	auto SelectedCharacter = Cast<AHBPlayerCharacter>(SelectedActor);
	if (!SelectedCharacter) return;
	
	SelectedCharacter->ActivateStory(Key);
}

AActor* AHBPlayerControllerBase::GetActorUnderCursor()
{
	FHitResult Hit;
	if(GetHitResultUnderCursor(ECC_Visibility, false, Hit))
	{
		AActor* HitActor = Hit.GetActor();
		// GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Emerald, HitActor->GetName());
		if(HitActor->Implements<UHBSelectableInterface>())
		{
			return HitActor;
		}
	}
	return nullptr;
}

void AHBPlayerControllerBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	auto NewActor = GetActorUnderCursor();
	if(NewActor != CachedActor)
	{
		if (CachedActor.Get())
		{
			if (auto Skel = CachedActor->GetComponentByClass<USkeletalMeshComponent>())
			{
				if (CachedActor != SelectedActor)
				{
					Skel->SetRenderCustomDepth(false);
					Skel->SetCustomDepthStencilValue(0);
				}
			}
		}

		CachedActor = NewActor;

		if (CachedActor.Get())
		{
			if (auto Skel = CachedActor->GetComponentByClass<USkeletalMeshComponent>())
			{
				if (CachedActor != SelectedActor)
				{
					Skel->SetRenderCustomDepth(true);
					Skel->SetCustomDepthStencilValue(UnderCursorStencilValue);
				}
			}
		}
	}
}

void AHBPlayerControllerBase::SelectActor()
{
	if(SelectedActor.Get() && SelectedActor->Implements<UHBSelectableInterface>())
	{
		auto DecalComponent = IHBSelectableInterface::Execute_GetDecalComponent(SelectedActor.Get());
		if (DecalComponent)
		{
			DecalComponent->Deactivate();
			DecalComponent->SetVisibility(false);
			if(auto Skel = SelectedActor->GetComponentByClass<USkeletalMeshComponent>())
			{
				Skel->SetRenderCustomDepth(false);
				Skel->SetCustomDepthStencilValue(0);
			}
			
		}
	}

	SelectedActor = CachedActor;

	if (SelectedActor.Get() && SelectedActor->Implements<UHBSelectableInterface>())
	{
		UE_LOG(LogTemp, Warning, TEXT("In"));
		auto DecalComponent = IHBSelectableInterface::Execute_GetDecalComponent(SelectedActor.Get());
		if (DecalComponent)
		{
			DecalComponent->Activate();
			DecalComponent->SetVisibility(true);
			if (auto Skel = SelectedActor->GetComponentByClass<USkeletalMeshComponent>())
			{
				Skel->SetRenderCustomDepth(true);
				Skel->SetCustomDepthStencilValue(SelectedStencilValue);
			}
		}
	}

	// SelectedActor = GetActorUnderCursor();
}

void AHBPlayerControllerBase::CommandSelectedActor()
{
	if (!SelectedActor.IsValid()) return;

	APawn* ActorPawn = Cast<APawn>(SelectedActor);
	if (!ActorPawn) return;

	AAIController* AIController = Cast<AAIController>(ActorPawn->GetController());
	if (!AIController) return;


	if (!SelectedActor->Implements<UHBSelectableInterface>()) return;
		
	auto CommandHandler = IHBSelectableInterface::Execute_GetCommandHandler(SelectedActor.Get());
	if (!CommandHandler) return;
	

	FHitResult Hit;
	if (GetHitResultUnderCursor(ECC_Visibility, false, Hit))
	{
		if (CommandHandler->bCanMove)
		{
			// 높이 값 무시
			Hit.Location.Z = SelectedActor->GetActorLocation().Z;

			UHBCommand_Move* CommandMove = NewObject<UHBCommand_Move>();
			CommandMove->SetDestLocation(Hit.Location);
			CommandHandler->EnqueueCommand(CommandMove);
		}
		// @HB-ToDo : Attack, Hold... 
	}
}

AHBPlayerCharacter* AHBPlayerControllerBase::GetMainCharacter()
{
	return Cast<AHBPlayerCharacter>(GetPlayerState<AHBPlayerState>()->GetAbilitySystemComponent()->GetAvatarActor());
}



