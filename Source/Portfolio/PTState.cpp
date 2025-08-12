// Fill out your copyright notice in the Description page of Project Settings.


#include "PTState.h"

void UPTState::Start()
{
	IsEnded = false;

	OnStart();
}

void UPTState::End()
{
	IsEnded = true;

	OnEnd();
}