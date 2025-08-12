// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PTState.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PORTFOLIO_API UPTState : public UObject
{
	GENERATED_BODY()
	
public:
	void Start();
	void End();

	bool IsEnd() const {
		return IsEnded;
	}

protected:

	virtual void OnStart() {}
	virtual void OnEnd() {}

private:
	bool IsEnded = true;
};
