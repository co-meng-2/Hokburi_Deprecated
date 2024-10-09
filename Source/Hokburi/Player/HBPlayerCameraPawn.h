// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HBPlayerCameraPawn.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class HOKBURI_API AHBPlayerCameraPawn : public APawn
{
	GENERATED_BODY()

public:
	AHBPlayerCameraPawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, Category = "Hokburi | Camera")
	TObjectPtr<UCameraComponent>		Camera;
	UPROPERTY(EditAnywhere, Category = "Hokburi | Camera")
	TObjectPtr<USpringArmComponent>		CameraBoom;
	UPROPERTY(EditAnywhere, Category = "Hokburi | Camera")
	TObjectPtr<UStaticMeshComponent>	StaticMesh;

	// Input Actions
	UPROPERTY(EditDefaultsOnly, Category = "Hokburi | Input")
	UInputAction* IA_Move;
	UPROPERTY(EditDefaultsOnly, Category = "Hokburi | Input")
	UInputAction* IA_Zoom;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Hokburi | Init")
	float CameraMoveSpeed = 200.f;
	UPROPERTY(EditDefaultsOnly, Category = "Hokburi | Init")
	float EdgeMargin = 20.f;

	UPROPERTY(EditDefaultsOnly, Category = "Hokburi | Zoom")
	float MaxZoom = 500.f;
	UPROPERTY(EditDefaultsOnly, Category = "Hokburi | Zoom")
	float MinZoom = 2000.f;
	UPROPERTY(EditDefaultsOnly, Category = "Hokburi | Zoom")
	float ZoomSpeed = 500.f;
	float ZoomSmoothSpeed = 5.f;

private:
	void Move(const FInputActionValue& Value);
	bool MoveCameraFromMouseInEdge(float DeltaTime);

	void Zoom(const FInputActionValue& Value);

	bool bHasMoveInput;
	FVector CachedMoveDir;

	bool bHasZoomInput;
	float CachedZoomDir;
	float CachedTargetLength;

	int ScreenSizeX;
	int ScreenSizeY;
};
