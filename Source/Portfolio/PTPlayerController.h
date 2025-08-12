// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PTActionManager.h"

#include "PTPlayerController.generated.h"

class APTPlayerPawn;
/**
 * PlayerController로 BP에서 입력 들어온걸로 Action을 실행 시켜준다.
 */
UCLASS()
class PORTFOLIO_API APTPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	APTPlayerController();

	UFUNCTION(BlueprintCallable)
	void MoveToLocation(const FVector& Dest);

	UFUNCTION(BlueprintCallable)
	void AttackToTarget(APTPawn* InTarget);

protected:
	virtual void OnPossess(APawn* aPawn) override;

private:
	TWeakObjectPtr<UPTActionManager> ActionManager;
	TWeakObjectPtr<APTPlayerPawn> MyPawn;
};
