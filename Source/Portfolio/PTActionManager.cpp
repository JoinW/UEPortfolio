// Fill out your copyright notice in the Description page of Project Settings.


#include "PTActionManager.h"
#include "PTCustomAction.h"

// Sets default values for this component's properties
UPTActionManager::UPTActionManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called every frame
void UPTActionManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (CurrentAction.IsValid())
	{
		if (CurrentAction->IsEnd())
		{
			CurrentAction = nullptr;
		}
		else
		{
			CurrentAction->Tick(DeltaTime);
		}
	}
}

void UPTActionManager::MoveToLocation(const FVector& InDest)
{
	StartAction<UPTAction_MoveToLocation>(InDest);
}

void UPTActionManager::CombatEnemy(TWeakObjectPtr<APTPawn> InTarget)
{
	StartAction<UPTAction_CombatEnemy>(InTarget);
}

