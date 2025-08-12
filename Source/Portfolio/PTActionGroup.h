// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PTAction.h"
#include "PTActionGroup.generated.h"

typedef std::initializer_list<UPTAction*> GROUP_LIST;
/**
 * 
 */

//여러 액션들을 가진 액션 그룹
//
UCLASS(Abstract)
class PORTFOLIO_API UPTActionGroup : public UPTAction
{
	GENERATED_BODY()
	
public:
	void SetParam(std::initializer_list<UPTAction*> ActionList);

protected:
	UPROPERTY(Transient)
	TArray<TObjectPtr<UPTAction>> Actions;
};

//액션들을 순차 실행하는 액션
UCLASS()
class PORTFOLIO_API UPTActionGroup_Sequencial : public UPTActionGroup
{
	GENERATED_BODY()

public:
	virtual void OnTick(float DeltaTime) override;

protected:
	virtual void OnStart();

private:
	bool StartAction(int Index);

private:
	int CurrentActionIndex = 0;
	TWeakObjectPtr<UPTAction> CurrentAction;
};
