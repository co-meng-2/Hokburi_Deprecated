// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HBSelectableInterface.generated.h"

class UHBCommandHandler;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHBSelectableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HOKBURI_API IHBSelectableInterface
{
	GENERATED_BODY()

public:
	virtual UHBCommandHandler* GetCommandHandler() = 0;
};
