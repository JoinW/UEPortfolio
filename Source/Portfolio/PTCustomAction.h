// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PTAction.h"
#include "PTActionGroup.h"
#include "PTConditionalAction.h"

#include "PTCustomAction.generated.h"

//아래는 기본 액션을 상속 받아 실제 게임 기능들을 구현한 액션들이다


//특정 지점까지 이동하는 액션, 지점에 도달하면 종료된다.
UCLASS()
class PORTFOLIO_API UPTAction_MoveToLocation : public UPTAction
{
	GENERATED_BODY()

public:
	void SetParam(const FVector& InDest) { Destination = InDest; }
	virtual void OnTick(float DeltaTime) override;

protected:
	virtual void OnStart() override;

private:
	FVector Destination;
};

//타겟을 추적해서 이동하는 액션, 근처에 도달하면 종료된다.
UCLASS()
class PORTFOLIO_API UPTAction_ChaseTarget : public UPTAction
{
	GENERATED_BODY()

public:
	void SetParam(TWeakObjectPtr<APTPawn> InTarget) { Target = InTarget; }
	virtual void OnTick(float DeltaTime) override;

protected:
	virtual void OnStart() override;

private:
	TWeakObjectPtr<APTPawn> Target;

	FVector Destination;
};

//대상을 공격하는 액션, 1회성이다
UCLASS()
class PORTFOLIO_API UPTAction_Attack : public UPTAction
{
	GENERATED_BODY()

public:

	void SetParam(TWeakObjectPtr<APTPawn> InTarget) { Target = InTarget; }

	virtual void OnTick(float DeltaTime) override;

protected:
	virtual void OnStart() override;

private:
	TWeakObjectPtr<APTPawn> Target;
};


//하나의 대상이 죽을 때까지 추적하면서 공격하는 액션
UCLASS()
class UPTAction_CombatEnemy : public UPTConditionalAction_Loop
{
	GENERATED_BODY()

public:
	void SetParam(TWeakObjectPtr<APTPawn> InTarget) { Target = InTarget; }

	virtual void Init() override;

private:
	TWeakObjectPtr<APTPawn> Target;
};
