// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PTPawn.h"
#include "PTPlayerPawn.generated.h"

class UPTPawnStateManager;

UCLASS()
class PORTFOLIO_API APTPlayerPawn : public APTPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APTPlayerPawn();

	static APTPlayerPawn* Get() { return Instance.IsValid() ? Instance.Get() : nullptr; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void BeginDestroy() override;

	virtual void OnDie() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	static TWeakObjectPtr<APTPlayerPawn> Instance;
	
};
