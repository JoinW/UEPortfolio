// Fill out your copyright notice in the Description page of Project Settings.


#include "PTPawnStateManager.h"

#include "PTPlayerPawn.h"

// Sets default values for this component's properties
UPTPawnStateManager::UPTPawnStateManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPTPawnStateManager::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<APTPawn>(GetOwner());

	ensureMsgf(Owner.IsValid(), TEXT("UPTPawnStateManager : Owner is not Valid"));

	//InitStats
	MakeState<UPTPawnState_Idle>(EPawnState::Idle);
	MakeState<UPTPawnState_Move>(EPawnState::Move);
	MakeState<UPTPawnState_Attack>(EPawnState::Attack);

	SetDefaultState();
}

FString UPTPawnStateManager::GetDebugInfo()
{
	return FString::Format(TEXT("{0}"), { CurrentState.IsValid() ? CurrentState->GetName() : TEXT("None") });
}

// Called every frame
void UPTPawnStateManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (CurrentState.IsValid())
	{
		CurrentState->Tick(DeltaTime);

		if (CurrentState->IsEnd())
		{
			SetDefaultState();
		}
	}
}

void UPTPawnStateManager::PreSetState()
{
	if (CurrentState.IsValid())
	{
		CurrentState->End();
	}
}

void UPTPawnStateManager::SetDefaultState()
{
	SetState<UPTPawnState_Idle>();
}

void UPTPawnStateManager::MoveToLoction(const FVector& Dest)
{
	SetState<UPTPawnState_Move>(Dest);
}

void UPTPawnStateManager::Attack(TWeakObjectPtr<APTPawn> InTarget)
{
	SetState<UPTPawnState_Attack>(InTarget);
}