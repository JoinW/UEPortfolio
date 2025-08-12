// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PTPawnState.h"
#include "PTUtils.h"

#include "PTPawnStateManager.generated.h"

class APTPawn;

UENUM()
enum class EPawnState
{
	Idle,
	Move,
	Attack
};


//상태 관리자
//특정 상태 실행 시켜주고, 상태 종료 되면 Idle로 돌려 주는 간단한 관리자
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTFOLIO_API UPTPawnStateManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPTPawnStateManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FString GetDebugInfo();

	void MoveToLoction(const FVector& Dest);
	void Attack(TWeakObjectPtr<APTPawn> InTarget);

	template<typename T>
	bool IsState();

private:
	void SetDefaultState();

	template<typename T>
	void SetState();

	template<typename T, typename P>
	void SetState(P OneParam);

	void PreSetState();

	template<typename T>
	T* GetState();

	template<typename T>
	void MakeState(EPawnState StateEnum);

private:
	UPROPERTY(Transient)
	TMap <EPawnState, TObjectPtr<UPPawnState>> StateMap;

	UPROPERTY(Transient)
	TMap<UClass*, EPawnState> StateClassTypeMap;
	

	TWeakObjectPtr<APTPawn> Owner;
	TWeakObjectPtr<UPPawnState> CurrentState;
};

template<typename T>
bool UPTPawnStateManager::IsState()
{
	return CurrentState.IsValid() && CurrentState->IsA<T>();
}

template<typename T>
void UPTPawnStateManager::MakeState(EPawnState StateEnum)
{
	StateClassTypeMap.Add(T::StaticClass(), StateEnum);

	auto NewState = NewObject<T>(this);
	NewState->SetOwner(Cast<APTPawn>(GetOwner()));
	StateMap.Add(StateEnum, NewState);
}

template<typename T>
T* UPTPawnStateManager::GetState()
{
	ensureMsgf(StateClassTypeMap.Contains(T::StaticClass()), TEXT("UPTPawnStateManager::SetState() : Invalid State (%s)"), *T::StaticClass()->GetName());
	EPawnState StateEnum = StateClassTypeMap[T::StaticClass()];

	ensureMsgf(StateMap.Contains(StateEnum), TEXT("UPTPawnStateManager::SetState() : Invalid State Enum (%s)"), *ENUM_TO_FSTRING(StateEnum));

	TWeakObjectPtr<UPPawnState> State = StateMap[StateClassTypeMap[T::StaticClass()]];
	ensureMsgf(State.IsValid(), TEXT("UPTPawnStateManager::SetState() : Not Exist State Instance (%s)"), *ENUM_TO_FSTRING(StateEnum));

	T* MyState = Cast<T>(State.Get());
	ensureMsgf(MyState != nullptr, TEXT("UPTPawnStateManager::SetState() : Not matched ClassType : RequestType = %s, ExistType = %s"), *T::StaticClass()->GetName(), *State->GetClass()->GetName());
	return MyState;
}

template<typename T>
void UPTPawnStateManager::SetState()
{
	PreSetState();

	auto NewState = GetState<T>();

	CurrentState = NewState;
	CurrentState->Start();
}

template<typename T, typename P>
void UPTPawnStateManager::SetState(P OneParam)
{
	PreSetState();

	auto NewState = GetState<T>();
	NewState->SetParam(OneParam);

	CurrentState = NewState;
	CurrentState->Start();
}