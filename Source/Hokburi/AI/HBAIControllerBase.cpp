// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/HBAIControllerBase.h"

#include "Character/Components/HBDataComponent.h"

void AHBAIControllerBase::BeginPlay()
{
	Super::BeginPlay();
	if(auto DataComp = GetPawn()->GetComponentByClass<UHBDataComponent>())
	{
		RunBehaviorTree(DataComp->TreeAsset);
	}
}
