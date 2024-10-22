// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/HBPlayerCameraPawn.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Blueprint/WidgetLayoutLibrary.h"



AHBPlayerCameraPawn::AHBPlayerCameraPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(FName("CameraBoom"));
	SetRootComponent(StaticMesh);
	Camera->SetupAttachment(CameraBoom);
	CameraBoom->SetupAttachment(RootComponent);
	
}

void AHBPlayerCameraPawn::BeginPlay()
{
	Super::BeginPlay();

	CachedTargetArmLength = CameraBoom->TargetArmLength;
}

void AHBPlayerCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Input Event가 있는 입력이 우선시 된다.
	if(bHasMoveInput)
	{
		FVector Offset = CachedMoveDir* CameraMoveSpeed * DeltaTime;
		AddActorWorldOffset(Offset);
		bHasMoveInput = false;
	}
	else
	{
		// 마우스가 보이게 Controller -> bShowMouseCursor = true;
		// MoveCameraFromMouseInEdge(DeltaTime);
	}

	// Input이 먼저 처리됨 -> Tick에 위임
	if(bHasZoomInput)
	{
		float Ret = CameraBoom->TargetArmLength + CachedZoomDir * DeltaTime * ZoomSpeed;
		CachedTargetArmLength = FMath::Clamp(Ret, MinTargetArmLength, MaxTargetArmLength);
		// CameraBoom->TargetArmLength = FMath::Clamp(Ret, MinTargetArmLength, MaxTargetArmLength);
		bHasZoomInput = false;
	}

	// Zoom Smoothly
	// 현재 값 + (타겟 값 - 현재 값) * (비율 : DT * SmoothSpeed)
	// 일정 비율로 계속 타겟 값으로 향함. -> 초반엔 가파르게 후엔 완만하게 바뀐다.
	if (CameraBoom->TargetArmLength != CachedTargetArmLength)
	{
		CameraBoom->TargetArmLength = FMath::FInterpTo(CameraBoom->TargetArmLength, CachedTargetArmLength, DeltaTime, ZoomSmoothSpeed);
		if( FMath::Abs(CameraBoom->TargetArmLength - CachedTargetArmLength) <= ZoomThreshold )
		{
			CameraBoom->TargetArmLength = CachedTargetArmLength;
		}
	}
}

void AHBPlayerCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	EIComp->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ThisClass::Move);
	EIComp->BindAction(IA_Zoom, ETriggerEvent::Triggered, this, &ThisClass::Zoom);
}

void AHBPlayerCameraPawn::Move(const FInputActionValue& Value)
{
	FVector Val = Value.Get<FVector>();

	// 방향 벡터를 Pawn의 로컬 방향 기준으로 변환
	FRotator ControlRotation = GetActorRotation();
	CachedMoveDir = FRotationMatrix(ControlRotation).TransformVector(Val);

	bHasMoveInput = true;
}

bool AHBPlayerCameraPawn::MoveCameraFromMouseInEdge(float DeltaTime)
{
	APlayerController* PC = Cast<APlayerController>(Controller);
	float MouseX, MouseY;
	PC->GetMousePosition(MouseX, MouseY);
	PC->GetViewportSize(ScreenSizeX, ScreenSizeY);

	// OutOfWindow
	if (MouseX <= 0.f || MouseX >= ScreenSizeX || MouseY <= 0.f || MouseY >= ScreenSizeY)
		return false;

	FVector FrontDir = GetActorForwardVector();
	FVector RightDir = GetActorRightVector();

	FVector NewLocation = GetActorLocation();

	if (MouseY <= EdgeMargin)
	{
		NewLocation += FrontDir * CameraMoveSpeed * DeltaTime;
	}
	else if (MouseY >= ScreenSizeY - EdgeMargin)
	{
		NewLocation -= FrontDir * CameraMoveSpeed * DeltaTime;
	}

	if (MouseX <= EdgeMargin)
	{
		NewLocation -= RightDir * CameraMoveSpeed * DeltaTime;
	}
	else if (MouseX >= ScreenSizeX - EdgeMargin)
	{
		NewLocation += RightDir * CameraMoveSpeed * DeltaTime;
	}
	SetActorLocation(NewLocation);

	return true;
}

void AHBPlayerCameraPawn::Zoom(const FInputActionValue& Value)
{
	CachedZoomDir = Value.Get<float>();
	bHasZoomInput = true;
}


