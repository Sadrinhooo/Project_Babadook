// Fill out your copyright notice in the Description page of Project Settings.

#include "ShadowPuzzleManager.h"
#include "MyPlayerController.h"
#include "ShadowPuzzleDefaultState.h"


UShadowPuzzleDefaultState::UShadowPuzzleDefaultState()
{
	Owner = Cast<AShadowPuzzleManager>(GetOuter());
}

const FString& UShadowPuzzleDefaultState::GetInteractPrompt(ACharacter* Interactor)
{
	if (Owner->PlayerHasKeyItem(Owner->KeyItemIndex))
	{
		if (bHasPlacedKeyItem)
		{
			return MoveItemInteractPrompt;
		}else
		{
			return HasItemInteractPrompt;
		}
	} else
	{
		return NoItemInteractPrompt;	
	}
}

void UShadowPuzzleDefaultState::Interact(ACharacter* Interactor)
{
	if (bHasPlacedKeyItem) Owner->ChangeState(Owner->SolvingState);
	
	if (Owner->PlayerHasKeyItem(Owner->KeyItemIndex))
	{
		Owner->PuzzleItemPawn->SetActorHiddenInGame(false);
		bHasPlacedKeyItem = true;
	}	
}

void UShadowPuzzleDefaultState::InitiateState()
{
	Owner->PuzzleItemPawn->SetActorHiddenInGame(true);
}
