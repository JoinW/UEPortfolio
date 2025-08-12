// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "PTState.h"
#include "PTPlayerPawn.h"

#include "PTPawnState.generated.h"

UCLASS()
class PORTFOLIO_API UPPawnState : public UPTState
{
	GENERATED_BODY()

public:	

	void SetOwner(APTPawn* InOwner) { Owner = InOwner; }

	virtual void Tick(float DeltaTime);

protected:
	TWeakObjectPtr<APTPawn> Owner;
};

//아무 기능 없는 멈춰 있는 대기 상태
UCLASS()
class UPTPawnState_Idle : public UPPawnState
{
	GENERATED_BODY()

protected:
	virtual void Tick(float DeltaTime) override;
};

//특정 지점 까지 이동 입력을 강제로 계속 주고
//도착하면 상태 종료하는 이동 상태
UCLASS()
class UPTPawnState_Move : public UPPawnState
{
	GENERATED_BODY()

public:
	void SetParam(const FVector& InDest) { Destination = InDest; }

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void OnStart() override;

private:

	FVector Destination;
	FVector MoveDir;

};


//일정 시간 있다가 데미지 주고, 상태 종료하게 만든
//간단 공격 상태
UCLASS()
class UPTPawnState_Attack : public UPPawnState
{
	GENERATED_BODY()

public:

	void SetParam(TWeakObjectPtr<APTPawn> InTarget) { Target = InTarget; }
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void OnStart() override;

private:

	TWeakObjectPtr<APTPawn> Target;
	float FiringTimeCount = 0.0f;
	float AttackTimeCount = 0.0f;

	bool bIsFiring = false;
};