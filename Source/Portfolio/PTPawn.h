// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PTPawn.generated.h"

class UPTPawnStateManager;

UCLASS()
class PORTFOLIO_API APTPawn : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APTPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void OnDie();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveToLocation(const FVector& Dest);
	void Attack(TWeakObjectPtr<APTPawn> InTarget);

	bool IsMoving() const;
	bool IsAttacking() const;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	void DrawDebug(float DeltaTime);

protected:
	TWeakObjectPtr<UPTPawnStateManager> StateManager;

	int32 Hp = 100;
};
