// Fill out your copyright notice in the Description page of Project Settings.


#include "PTPlayerPawn.h"

#include "PTPawnStateManager.h"
#include "GameFramework/CharacterMovementComponent.h"

TWeakObjectPtr< APTPlayerPawn> APTPlayerPawn::Instance = nullptr;
// Sets default values
APTPlayerPawn::APTPlayerPawn()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APTPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	Instance = this;
}

void APTPlayerPawn::BeginDestroy()
{
	Instance = nullptr;

	Super::BeginDestroy();
}

void APTPlayerPawn::OnDie()
{
	//GameOver
}

// Called every frame
void APTPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APTPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}