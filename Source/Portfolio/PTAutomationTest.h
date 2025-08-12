// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "PTPawn.h"
#include "PTAction.h"

#include "PTAutomationTest.generated.h"

UCLASS()
class UPTActionTestExecutor : public UObject
{
	GENERATED_BODY()

public:
	template<typename T>
	T* MakePTAction(APTPawn* InOwner);

	template<typename T, typename P1>
	T* MakePTAction(APTPawn* InOwner, P1 OneParam);

private:
	UPROPERTY(Transient)
	TArray<TObjectPtr<UPTAction>> Actions;
};
