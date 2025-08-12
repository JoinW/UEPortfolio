// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PTPawn.h"
#include "PTCondition.generated.h"

/**
 * PTAction들에서 사용할 조건들에 사용할 기본 클래스
 */
UCLASS(Abstract)
class PORTFOLIO_API UPTCondition : public UObject
{
	GENERATED_BODY()
	
public:

	void SetOwner(TWeakObjectPtr<APTPawn> InOwner) { Owner = InOwner; }

	explicit operator bool() const {
		// Return true if the object is in a valid state, false otherwise
		return Condition();
	}

protected:
	virtual bool Condition() const { return true; }

	TWeakObjectPtr<APTPawn> Owner;
};

//TFunction을 조건으로 사용 하는 조건
UCLASS()
class UPTCondition_Func : public UPTCondition
{
	GENERATED_BODY()

public:
	void SetParam(TFunction<bool()> InFunc) { Function = InFunc; }
protected:
	virtual bool Condition() const override { return Function.IsSet() && Function(); }

private:
	TFunction<bool()> Function;
};

//타겟이 존재 하는지 체크 하는 조건
UCLASS()
class UPTCondition_ExistTarget : public UPTCondition
{
	GENERATED_BODY()

public:
	void SetParam(TWeakObjectPtr<APTPawn> InTarget) { Target = InTarget; }
protected:
	virtual bool Condition() const override;

private:
	TWeakObjectPtr<APTPawn> Target;
};