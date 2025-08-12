// Fill out your copyright notice in the Description page of Project Settings.


#include "PTPawn.h"

#include "PTPawnStateManager.h"

// Sets default values
APTPawn::APTPawn()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StateManager = CreateDefaultSubobject<UPTPawnStateManager>(FName(TEXT("StateManager")));

	//StateManager = GetComponentByClass<UPTPawnStateManager>();
	ensureMsgf(StateManager.IsValid(), TEXT("APTPlayerPawn : has not UPTPawnStateManager"));
}

// Called when the game starts or when spawned
void APTPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void APTPawn::OnDie()
{
	Destroy();
}

// Called every frame
void APTPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebug(DeltaTime);

	if (Hp == 0)
		OnDie();
}

void APTPawn::DrawDebug(float DeltaTime)
{
	FString Log = FString::Format(TEXT("Hp = {0}"), { Hp });
	Log += TEXT("\n");
	Log += FString::Format(TEXT("State = {0}"), { StateManager->GetDebugInfo() });

	DrawDebugString(GetWorld(), GetActorLocation() + FVector(0, 0, 100.0f), Log, 0, FColor::White, DeltaTime * 0.5f);
}

float APTPawn::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DrawDebugString(GetWorld(), GetActorLocation() + FVector(0, 0, 200.0f), FString::Format(TEXT("Damage = {0}"), { Damage }), 0, FColor::Red, 0.5f);

	Hp = FMath::Max(Hp - Damage, 0);
	return Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}

void APTPawn::MoveToLocation(const FVector& Dest)
{
	StateManager->MoveToLoction(Dest);
}

void APTPawn::Attack(TWeakObjectPtr<APTPawn> InTarget)
{
	StateManager->Attack(InTarget);
}

bool APTPawn::IsMoving() const
{
	return StateManager->IsState<UPTPawnState_Move>();
}

bool APTPawn::IsAttacking() const
{
	return StateManager->IsState<UPTPawnState_Attack>();
}