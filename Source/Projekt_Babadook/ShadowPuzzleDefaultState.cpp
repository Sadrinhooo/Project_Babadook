// Fill out your copyright notice in the Description page of Project Settings.

#include "ShadowPuzzleDefaultState.h"
#include "ShadowPuzzleManager.h"
#include "MyGameMode.h"	
#include "KeyItem.h"
#include "MyPlayerController.h"



UShadowPuzzleDefaultState::UShadowPuzzleDefaultState()
{
	Owner = Cast<AShadowPuzzleManager>(GetOuter());
}

const FString& UShadowPuzzleDefaultState::GetInteractPrompt(ACharacter* Interactor)
{
	if (Owner->bHasPlacedKeyItem)
	{
		return MoveItemInteractPrompt;
	}

	if (Owner->PlayerHasKeyItem(Owner->KeyItemIndex))
	{
		return HasItemInteractPrompt;
	}

	return NoItemInteractPrompt;
}

void UShadowPuzzleDefaultState::Interact(ACharacter* Interactor)
{
	if (Owner->bHasPlacedKeyItem)
	{
		Owner->ChangeState(Owner->SolvingState);
		Owner->PuzzleState->InitiateState();
		Owner->SetInteractable(false);
		return;
	}
	
	if (Owner->PlayerHasKeyItem(Owner->KeyItemIndex))
	{
		int Index = Owner->KeyItemIndex;
		Owner->PuzzleItemPawn->SetActorHiddenInGame(false);
		Owner->GameMode->SharedInventory[Index].NumberOfUses++;
		if (Owner->GameMode->SharedInventory[Index].NumberOfUses >= Owner->GameMode->SharedInventory[Index].MaxNumberOfUses) Owner->GameMode->SharedInventory.RemoveAt(Index);
		Owner->bHasPlacedKeyItem = true;
	}	
}

void UShadowPuzzleDefaultState::InitiateState()
{
	Owner->PuzzleItemPawn->SetActorHiddenInGame(true);
}
