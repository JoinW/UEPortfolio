// Fill out your copyright notice in the Description page of Project Settings.


#include "PTAutomationTest.h"

#include "PTCustomAction.h"

#include "Misc/AutomationTest.h"

bool GPTTestResult = true;

//기존 AutomationLatentCommand는 Update 처리만되서 ActionStart 처리를 하기 위한 
class FPTActionTestCommand : public IAutomationLatentCommand
{
public:
	FPTActionTestCommand(UPTAction* InAction)
		: Action(InAction)
	{
	}
	virtual ~FPTActionTestCommand()
	{
	}
	virtual bool Update() {

		if (!GPTTestResult || !Action.IsValid())
		{
			return true;
		}

		if (!bIsStart)
		{
			bIsStart = true;
			Action->Start();
			return false;
		}

		if (Action->IsEnd())
		{
			return true;
		}

		Action->Tick(FApp::GetDeltaTime());
		return false;
	}
private:

	//어차피 이 클래스는 UObject가 아니라서 Reference 참조로 인한 GC 방지가 안된다.
	//그래서 Valid 체크만 들고 있는 TWeakObjectPtr 사용
	TWeakObjectPtr<UPTAction> Action;
	bool bIsStart = false;
};

template<typename T>
T* UPTActionTestExecutor::MakePTAction(APTPawn* InOwner)
{
	T* NewAction = NewObject<T>();

	NewAction->SetOwner(InOwner);
	NewAction->Init();

	Actions.Add(NewAction);

	return NewAction;
}

template<typename T, typename P1>
T* UPTActionTestExecutor::MakePTAction(APTPawn* InOwner, P1 OneParam)
{
	T* NewAction = NewObject<T>();

	NewAction->SetOwner(InOwner);
	NewAction->SetParam(OneParam);
	NewAction->Init();

	Actions.Add(NewAction);

	return NewAction;
}

//Player 위치 체크용 커맨드
DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FPTCheckPlayerLocationCommand, FAutomationTestBase*, Test, TWeakObjectPtr<APTPlayerPawn>, Player, FVector, CheckLoc);
bool FPTCheckPlayerLocationCommand::Update()
{
	if (!GPTTestResult)
		return true;

	constexpr float AcceptableDist = 100.0f;
	if (FVector::DistSquared2D(Player->GetActorLocation(), CheckLoc) >= AcceptableDist * AcceptableDist)
	{
		GPTTestResult = false;
		Test->AddError(TEXT("Failed to reach the goal"));
	}
	return true;
}

//AddToRoot 했던 UObject 해제 하기 위한 Command
DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FPTReleaseExectorCommand, TWeakObjectPtr<UPTActionTestExecutor>, Executor);
bool FPTReleaseExectorCommand::Update()
{
	Executor->RemoveFromRoot();
	return true;
}


//이동 테스트 : 3개 지점 이동하면서 제대로 이동 됐는지 테스트
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPTMoveTest, "PT.GamePlayTest.MoveTest", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FPTMoveTest::RunTest(const FString& Parameters)
{
	GPTTestResult = true;

	APTPlayerPawn* MyPawn = APTPlayerPawn::Get();

	AddErrorIfFalse(MyPawn != nullptr, TEXT("Not Found Player"));
	if (MyPawn)
	{
		//Action들 GC 방지용 UObject
		UPTActionTestExecutor* Executor = NewObject<UPTActionTestExecutor>();
		Executor->AddToRoot();

		ADD_LATENT_AUTOMATION_COMMAND(FPTActionTestCommand(Executor->MakePTAction<UPTAction_MoveToLocation>(MyPawn, FVector(0.0f))));
		ADD_LATENT_AUTOMATION_COMMAND(FPTCheckPlayerLocationCommand(this, MyPawn, FVector(0.0f)));

		ADD_LATENT_AUTOMATION_COMMAND(FPTActionTestCommand(Executor->MakePTAction<UPTAction_MoveToLocation>(MyPawn, FVector(1000.0f, 0.0f, 0.0f))));
		ADD_LATENT_AUTOMATION_COMMAND(FPTCheckPlayerLocationCommand(this, MyPawn, FVector(1000.0f, 0.0f, 0.0f)));

		ADD_LATENT_AUTOMATION_COMMAND(FPTActionTestCommand(Executor->MakePTAction<UPTAction_MoveToLocation>(MyPawn, FVector(0.0f, 1000.0f, 0.0f))));
		ADD_LATENT_AUTOMATION_COMMAND(FPTCheckPlayerLocationCommand(this, MyPawn, FVector(0.0f, 1000.0f, 0.0f)));

		ADD_LATENT_AUTOMATION_COMMAND(FPTActionTestCommand(Executor->MakePTAction<UPTAction_MoveToLocation>(MyPawn, FVector(0.0f))));
		ADD_LATENT_AUTOMATION_COMMAND(FPTCheckPlayerLocationCommand(this, MyPawn, FVector(0.0f)));

		//AddToRoot 했던 UObject 해제
		ADD_LATENT_AUTOMATION_COMMAND(FPTReleaseExectorCommand(Executor));
	}
	else
	{
		return false;
	}
	

    return GPTTestResult; // Return true for pass, false for fail
}

//실패 처리 테스트 하기 위한 테스트
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPTMoveFailTest, "PT.GamePlayTest.MoveFailTest", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FPTMoveFailTest::RunTest(const FString& Parameters)
{
	GPTTestResult = true;

	APTPlayerPawn* MyPawn = APTPlayerPawn::Get();

	AddErrorIfFalse(MyPawn != nullptr, TEXT("Not Found Player"));

	if (MyPawn)
	{
		UPTActionTestExecutor* Executor = NewObject<UPTActionTestExecutor>();
		Executor->AddToRoot();

		//실패 되도록 이동 지점과 체크 지점 다르게 넣음
		ADD_LATENT_AUTOMATION_COMMAND(FPTActionTestCommand(Executor->MakePTAction<UPTAction_MoveToLocation>(MyPawn, FVector(0.0f))));
		ADD_LATENT_AUTOMATION_COMMAND(FPTCheckPlayerLocationCommand(this, MyPawn, FVector(1000.0f)));

		ADD_LATENT_AUTOMATION_COMMAND(FPTReleaseExectorCommand(Executor));
	}
	else
	{
		return false;
	}


	return GPTTestResult; // Return true for pass, false for fail
}