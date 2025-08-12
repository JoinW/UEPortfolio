// Fill out your copyright notice in the Description page of Project Settings.


#include "PTPawnState.h"
#include "Kismet/GameplayStatics.h"

#include "GameFramework/PawnMovementComponent.h"

void UPPawnState::Tick(float DeltaTime)
{
	if (!Owner.IsValid())
	{
		End();
	}
}

void UPTPawnState_Idle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsEnd())
		return;
}

void UPTPawnState_Move::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsEnd())
		return;

	auto CurLoc = Owner->GetActorLocation();
	auto DestDir = (Destination - CurLoc).GetSafeNormal2D();

	constexpr float AcceptableDist = 5.0f;

	auto Angle = (MoveDir | DestDir);

	//거리가 일정 거리 이하거나 목적지를 지나치면 스톱
	if (FVector::Dist2D(CurLoc, Destination) < AcceptableDist ||
		Angle < 0)
	{
		UE_LOG(LogTemp, Log, TEXT("UPTPawnState_Move End : Dist = %f, Angle = %f, Velocity = %s, DestDir = %s"), FVector::Dist2D(CurLoc, Destination), Angle, *Owner->GetVelocity().ToString(), *DestDir.ToString());
		End();
		return;
	}

	Owner->AddMovementInput(DestDir);
}

void UPTPawnState_Move::OnStart()
{
	auto CurLoc = Owner->GetActorLocation();
	MoveDir = (Destination - CurLoc).GetSafeNormal2D();

	Owner->GetMovementComponent()->StopMovementImmediately();
}


void UPTPawnState_Attack::OnStart()
{
	constexpr float FiringTime = 1.0f;
	constexpr float AttackTime = 2.0f;

	if (!Target.IsValid())
	{
		End();
		return;
	}

	FiringTimeCount = FiringTime;
	AttackTimeCount = AttackTime;

	bIsFiring = false;
}


void UPTPawnState_Attack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsEnd())
		return;

	if (!Target.IsValid())
	{
		End();
		return;
	}

	FiringTimeCount -= DeltaTime;
	AttackTimeCount -= DeltaTime;

	if (!bIsFiring)
	{
		if (FiringTimeCount < 0.0f)
		{
			bIsFiring = true;
			constexpr float Damage = 10.0f;
			UGameplayStatics::ApplyDamage(Target.Get(), Damage, Owner->GetInstigatorController(), Owner.Get(), UDamageType::StaticClass());
		}
	}

	if (AttackTimeCount < 0.0f)
	{
		End();
	}
}