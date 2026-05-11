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
	return NoItemInteractPrompt;
}

void UShadowPuzzleDefaultState::Interact(ACharacter* Interactor)
{
	if (Owner->PuzzleCameraActor)
	{
		Cast<AMyPlayerController>(Owner->GetWorld()->GetFirstPlayerController())->PossessPuzzlePawn(Owner->PuzzleItemPawn);
		Owner->GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(Owner->PuzzleCameraActor, 0);
		Owner->ChangeState(Owner->SolvingState);
	}
	
}
