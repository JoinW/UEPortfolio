// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PTAction.h"
#include "PTCondition.h"
#include "PTConditionalAction.generated.h"

/**
 * 조건을 만족하면 자식 액션을 실행하는 액션
 */
UCLASS()
class PORTFOLIO_API UPTConditionalAction : public UPTAction
{
	GENERATED_BODY()
	
public:
	void SetParam(UPTCondition* InCondition, UPTAction* InAction) 
	{ 
		Condition = InCondition; 
		Action = InAction;
	}

protected:
	virtual void OnStart() override;
	virtual void OnTick(float DeltaTime) override;

protected:
	TObjectPtr<UPTCondition> Condition;

	TObjectPtr<UPTAction> Action;
};

//조건이 만족 안될 때 까지 자식 액션을 계속 실행하는 액션
UCLASS()
class PORTFOLIO_API UPTConditionalAction_Loop : public UPTConditionalAction
{
	GENERATED_BODY()

protected:
	virtual void OnTick(float DeltaTime) override;
};

