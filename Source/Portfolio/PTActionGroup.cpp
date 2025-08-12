// Fill out your copyright notice in the Description page of Project Settings.


#include "PTActionGroup.h"

void UPTActionGroup::SetParam(std::initializer_list<UPTAction*> ActionList)
{
	Actions = ActionList;
}

void UPTActionGroup_Sequencial::OnStart()
{
	if (Actions.IsEmpty())
	{
		End();
		return;
	}

	StartAction(0);
}

bool UPTActionGroup_Sequencial::StartAction(int Index)
{
	if (!Actions.IsValidIndex(Index))
	{
		return false;
	}

	CurrentAction = Actions[Index];
	CurrentAction->Start();
	CurrentActionIndex = Index;
	return true;
}

void UPTActionGroup_Sequencial::OnTick(float DeltaTime)
{
	if (!CurrentAction.IsValid())
	{
		End();
		return;
	}

	if (CurrentAction->IsEnd())
	{
		if (!StartAction(CurrentActionIndex + 1))
		{
			End();
		}
	}
	else
	{
		CurrentAction->Tick(DeltaTime);
	}
	
}