// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameMode.h"
#include "ShadowPuzzleManager.h"
#include "Kismet/GameplayStatics.h"
#include "KeyItem.h"
#include "MyPlayerController.h"
#include "ShadowPuzzleDefaultState.h"


// Sets default values
AShadowPuzzleManager::AShadowPuzzleManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShadowPuzzleManager::BeginPlay()
{
	Super::BeginPlay();
	DefaultState = NewObject<UShadowPuzzleDefaultState>(this);
	SolvingState = NewObject<UShadowPuzzleSolvingState>(this);
	ChangeState(DefaultState);
}

// Called every frame
void AShadowPuzzleManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if ((FVector::DotProduct(PuzzleItemPawn->GetActorForwardVector(), TargetForwardVector)) > 0.99f &&
		FVector::DotProduct(PuzzleItemPawn->GetActorUpVector(), TargetUpVector) > 0.99f)
	{
		OnSuccess(DeltaTime);
	}

}

void AShadowPuzzleManager::Interact(ACharacter* Interactor)
{
	PuzzleState->Interact(Interactor);
}

const FString& AShadowPuzzleManager::GetInteractPrompt(ACharacter* Interactor)
{
	return PuzzleState->GetInteractPrompt(Interactor);
}

void AShadowPuzzleManager::ChangeState(UObject* NewState)
{
	PuzzleState = NewState;
	PuzzleState->InitiateState();
}

bool AShadowPuzzleManager::PlayerHasKeyItem(int32& OutIndex)
{
	for (int i = 0; i < Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this))->SharedInventory.Num(); i++)
	{
		if (Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this))->SharedInventory[i].ItemTag == RequiredKeyItemTag)
		{
			OutIndex = i;
			return true;
		}
	}

	return false;
}

void AShadowPuzzleManager::OnSuccess(float DeltaTime)
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	APawn* PlayerPawn = PC->GetPawn();

	PlayerPawn->DisableInput(PC);
	FQuat TargetQuat = TargetRotation.Quaternion();
	FQuat CurrentQuat = PuzzleItemPawn->GetActorQuat();
	FQuat NewQuat = FQuat::Slerp(CurrentQuat, TargetQuat, DeltaTime * 0.05);
	NewQuat.Normalize();
	PuzzleItemPawn->SetActorRotation(NewQuat);
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, [this]()
	{
		//ALL BS
		UE_LOG(LogTemp, Warning, TEXT("SIGMA SIGMA ON THE ALL"));
		EnableInput(GetWorld()->GetFirstPlayerController());
		Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController())->UnpossessPuzzlePawn();
		PrimaryActorTick.bCanEverTick = false;
    
	}, 3.0f, false); 
}

