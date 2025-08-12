// Fill out your copyright notice in the Description page of Project Settings.


#include "PTCustomAction.h"


void UPTAction_MoveToLocation::OnStart()
{
	CHECK_OWNER();

	Owner->MoveToLocation(Destination);
	DrawDebugBox(Owner->GetWorld(), Destination, FVector(50.0f), FColor::Blue, false, 0.5f);
}

void UPTAction_MoveToLocation::OnTick(float DeltaTime)
{
	if (!Owner->IsMoving())
	{
		constexpr float AcceptableDist = 100.0f;

		if (FVector::DistSquared2D(Destination, Owner->GetActorLocation()) < AcceptableDist * AcceptableDist)
		{
			End();
		}
		else
		{
			Owner->MoveToLocation(Destination);
			DrawDebugBox(Owner->GetWorld(), Destination, FVector(50.0f), FColor::Blue, false, 0.5f);
		}
	}
}

void UPTAction_ChaseTarget::OnStart()
{
	CHECK_OWNER();

	if (!Target.IsValid())
	{
		End();
		return;
	}

	Destination = Target->GetActorLocation();
	Owner->MoveToLocation(Destination);
	DrawDebugBox(Owner->GetWorld(), Destination, FVector(50.0f), FColor::Blue, false, 0.5f);
}

void UPTAction_ChaseTarget::OnTick(float DeltaTime)
{
	if (!Target.IsValid())
	{
		End();
		return;
	}

	float AcceptableDist = 100.0f;

	FVector OwnerLoc = Owner->GetActorLocation();
	FVector TargetLoc = Target->GetActorLocation();

	if (FVector::DistSquared2D(OwnerLoc, TargetLoc) < AcceptableDist * AcceptableDist)
	{
		End();
		return;
	}

	float ThresholdDist = 100.0f;
	if (FVector::Dist2D(Destination, TargetLoc) > ThresholdDist ||
		!Owner->IsMoving())
	{
		Destination = TargetLoc;
		Owner->MoveToLocation(Destination);
		DrawDebugBox(Owner->GetWorld(), Destination, FVector(50.0f), FColor::Blue, false, 0.5f);
	}
}


void UPTAction_Attack::OnStart()
{
	CHECK_OWNER();

	if (!Target.IsValid())
	{
		End();
		return;
	}

	Owner->Attack(Target);
}

void UPTAction_Attack::OnTick(float DeltaTime)
{
	if (!Owner->IsAttacking())
	{
		End();
	}
}

void UPTAction_CombatEnemy::Init()
{
	Super::Init();

	UPTConditionalAction_Loop::SetParam(
		MakeCondition<UPTCondition_ExistTarget>(Target),
			MakeAction<UPTActionGroup_Sequencial>(
				GROUP_LIST{
					MakeAction<UPTAction_ChaseTarget>(Target),
					MakeAction<UPTAction_Attack>(Target)
				}
		));
}