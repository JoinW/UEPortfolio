// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PTAction.h"

#include "PTActionManager.generated.h"

/**
 * 액션 관리자
 * 액션들 실행 시키고 실행 중인 액션에게 Tick을 준다.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTFOLIO_API UPTActionManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPTActionManager();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void MoveToLocation(const FVector& InDest);
	void CombatEnemy(TWeakObjectPtr<APTPawn> InTarget);

private:
	template<typename T>
	void StartAction();

	template<typename T, typename P>
	void StartAction(P OneParam);

private:

	TWeakObjectPtr<UPTAction> CurrentAction;

	TWeakObjectPtr<APTPlayerPawn> Owner;
};

template<typename T>
void UPTActionManager::StartAction()
{
	if (CurrentAction.IsValid())
	{
		CurrentAction->End();
	}

	T* NewAction = NewObject<T>();
	NewAction->SetOwner(Owner);
	NewAction->Init();

	CurrentAction = NewAction;
	CurrentAction->Start();
}

template<typename T, typename P>
void UPTActionManager::StartAction(P OneParam)
{
	if (CurrentAction.IsValid())
	{
		CurrentAction->End();
	}

	T* NewAction = NewObject<T>();
	NewAction->SetOwner(Owner);
	NewAction->SetParam(OneParam);
	NewAction->Init();

	CurrentAction = NewAction;
	CurrentAction->Start();
}