// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PTUtils.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UPTUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	template<typename T>
	static FString EnumToString(T EnumValue);
	
};

template<typename T>
FString UPTUtils::EnumToString(T EnumValue)
{
	UEnum* EnumPtr = StaticEnum<T>();
	if (EnumPtr)
	{
		FText DisplayText = EnumPtr->GetDisplayNameTextByValue(static_cast<int64>(EnumValue));
		return DisplayText.ToString();
	}

	return TEXT("");
}

#define ENUM_TO_FSTRING(ENUM) UPTUtils::EnumToString(ENUM)