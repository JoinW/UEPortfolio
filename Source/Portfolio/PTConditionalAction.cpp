// Fill out your copyright notice in the Description page of Project Settings.


#include "PTConditionalAction.h"

void UPTConditionalAction::OnStart()
{
	if (!Condition)
	{
		End();
		return;
	}

	Action->Start();
}

void UPTConditionalAction::OnTick(float DeltaTime)
{
	if (Action->IsEnd())
	{
		End();
	}
}

void UPTConditionalAction_Loop::OnTick(float DeltaTime)
{
	if (Action->IsEnd())
	{
		if (Condition)
		{
			Action->Start();
		}
		else
		{
			End();
		}
	}
	else
	{
		Action->Tick(DeltaTime);
	}
}