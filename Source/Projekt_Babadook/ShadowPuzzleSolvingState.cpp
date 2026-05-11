// Fill out your copyright notice in the Description page of Project Settings.

#include "ShadowPuzzleManager.h"
#include "ShadowPuzzleSolvingState.h"

UShadowPuzzleSolvingState::UShadowPuzzleSolvingState()
{
	Owner = Cast<AShadowPuzzleManager>(GetOuter());
}

const FString& UShadowPuzzleSolvingState::GetInteractPrompt(ACharacter* Interactor)
{
	return NoPrompt;
}

void UShadowPuzzleSolvingState::Interact(ACharacter* Interactor)
{
}
