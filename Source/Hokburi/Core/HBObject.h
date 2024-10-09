// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HBObject.generated.h"

/**
 * BlueprintFunctionLibrary를 사용할 수 있게 하는 Object
 * 이 Object가 WorldContext 객체인지 아닌지 판단해서 사용해야한다.
 */
UCLASS()
class HOKBURI_API UHBObject : public UObject
{
	GENERATED_BODY()

	ULevel* GetLevel() const;
	virtual UWorld* GetWorld() const override;
};

// ## enforce WorldContext restrictions ##

//	const bool bInsideBpFuncLibrary = Blueprint && (BPTYPE_FunctionLibrary == Blueprint->BlueprintType);
//	if (!bInsideBpFuncLibrary &&
//	    Function->HasMetaData(FBlueprintMetadata::MD_WorldContext) &&
//	    !Function->HasMetaData(FBlueprintMetadata::MD_CallableWithoutWorldContext))
//	{
//	    check(Blueprint);
//	    UClass* ParentClass = Blueprint->ParentClass;
//	    check(ParentClass);
//	    if (ParentClass && !FBlueprintEditorUtils::ImplementsGetWorld(Blueprint) && !ParentClass->HasMetaDataHierarchical(FBlueprintMetadata::MD_ShowWorldContextPin))
//	    {
//	        MessageLog.Warning(*LOCTEXT("FunctionUnsafeInContext", "Function '@@' is unsafe to call from blueprints of class '@@'.").ToString(), this, ParentClass);
//	    }
//	}

// !FBlueprintEditorUtils::ImplementsGetWorld(Blueprint) 부분에서 탈출하도록, GetWorld를 override해주어야 함.
// 기본 UObject의 GetWorld에는 실행하면 override 했는지 안했는지 구분하는 bGetWorldOverridden = false; 이런 부분이 있음.