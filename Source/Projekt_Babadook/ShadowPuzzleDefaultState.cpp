// Fill out your copyright notice in the Description page of Project Settings.

#include "ShadowPuzzleManager.h"
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
		Owner->GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(Owner->PuzzleCameraActor, 0);
		Owner->ChangeState(Owner->SolvingState);
	}
	
}
