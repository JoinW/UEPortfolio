// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "PTPlayerPawn.h"
#include "PTState.h"

#include "PTAction.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UPTAction : public UPTState
{
	GENERATED_BODY()

	friend class UPTActionManager;

public:
	virtual void Init();

	void Tick(float DeltaTime);

	void SetOwner(TWeakObjectPtr<APTPawn> InOwner) { Owner = InOwner; }

protected:
	bool CheckOwner();

	virtual void OnTick(float DeltaTime) {}

	template<typename T>
	T* MakeAction();

	template<typename T, typename P>
	T* MakeAction(P OneParam);

	template<typename T>
	T* MakeCondition();

	template<typename T, typename P>
	T* MakeCondition(P OneParam);

protected:
	TWeakObjectPtr<APTPawn> Owner;
};


template<typename T>
T* UPTAction::MakeAction()
{
	T* NewAction = NewObject<T>();

	NewAction->SetOwner(Owner);
	NewAction->Init();

	return NewAction;
}

template<typename T, typename P>
T* UPTAction::MakeAction(P OneParam)
{
	T* NewAction = NewObject<T>();

	NewAction->SetOwner(Owner);
	NewAction->SetParam(OneParam);
	NewAction->Init();

	return NewAction;
}

template<typename T>
T* UPTAction::MakeCondition()
{
	T* NewCondition = NewObject<T>();

	NewCondition->SetOwner(Owner);

	return NewCondition;
}

template<typename T, typename P>
T* UPTAction::MakeCondition(P OneParam)
{
	T* NewCondition = NewObject<T>();

	NewCondition->SetOwner(Owner);
	NewCondition->SetParam(OneParam);

	return NewCondition;
}

#define CHECK_OWNER() \
if (!CheckOwner()) \
{\
	return;\
}