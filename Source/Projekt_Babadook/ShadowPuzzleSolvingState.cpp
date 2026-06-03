// Fill out your copyright notice in the Description page of Project Settings.

#include "ShadowPuzzleSolvingState.h"
#include "ShadowPuzzleManager.h"

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
	if (Owner->PuzzleCameraComponent)
	{
		Owner->ShowWidget();
		Cast<AMyPlayerController>(Owner->GetWorld()->GetFirstPlayerController())->bAutoManageActiveCameraTarget = false;
		Cast<AMyPlayerController>(Owner->GetWorld()->GetFirstPlayerController())->PossessPuzzlePawn(Owner);
		Owner->GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(Owner, 1.f);
	}
}
