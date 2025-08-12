// Fill out your copyright notice in the Description page of Project Settings.


#include "PTPlayerController.h"

#include "PTPlayerPawn.h"

APTPlayerController::APTPlayerController()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ActionManager = CreateDefaultSubobject<UPTActionManager>(FName(TEXT("ActionManager")));
	ensureMsgf(ActionManager.IsValid(), TEXT("APTPlayerController : has not UPTActionManager"));
}

void APTPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	MyPawn = Cast<APTPlayerPawn>(aPawn);
	ensureMsgf(MyPawn.IsValid(), TEXT("Possessed Pawn is not APTPlayerPawn"));
}

void APTPlayerController::MoveToLocation(const FVector& Dest)
{
	ActionManager->MoveToLocation(Dest);
}

void APTPlayerController::AttackToTarget(APTPawn* InTarget)
{
	if (InTarget)
	{
		ActionManager->CombatEnemy(InTarget);
	}
}
	
