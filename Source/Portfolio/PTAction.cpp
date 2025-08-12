// Fill out your copyright notice in the Description page of Project Settings.


#include "PTAction.h"

#include "Kismet/GameplayStatics.h"

#include "PTPlayerPawn.h"


void UPTAction::Init()
{
	Owner = APTPlayerPawn::Get();
}

bool UPTAction::CheckOwner()
{
	if (!Owner.IsValid())
	{
		End();
		return false;
	}

	return true;
}

void UPTAction::Tick(float DeltaTime)
{
	CHECK_OWNER();

	OnTick(DeltaTime);
}
