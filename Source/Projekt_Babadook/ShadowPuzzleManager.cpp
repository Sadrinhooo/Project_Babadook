// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameMode.h"
#include "ShadowPuzzleManager.h"
#include "Kismet/GameplayStatics.h"
#include "KeyItem.h"
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
	PuzzleState = DefaultState;
	
}

// Called every frame
void AShadowPuzzleManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

