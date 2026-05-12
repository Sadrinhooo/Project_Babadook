// Fill out your copyright notice in the Description page of Project Settings.

#include "ShadowPuzzleManager.h"
#include "ShadowPuzzleSolvingState.h"

#include "MyPlayerController.h"

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

void UShadowPuzzleSolvingState::InitiateState()
{
	if (Owner->PuzzleCameraActor)
	{
		Cast<AMyPlayerController>(Owner->GetWorld()->GetFirstPlayerController())->PossessPuzzlePawn(Owner->PuzzleItemPawn);
		Owner->GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(Owner->PuzzleCameraActor, 0.01f);
	}
}
