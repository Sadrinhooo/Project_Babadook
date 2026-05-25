// Fill out your copyright notice in the Description page of Project Settings.

#include "OneSidedDoor.h"

#include "GameFramework/Character.h"


void AOneSidedDoor::Interact(ACharacter* Interactor)
{
	
	if (!bIsUnlocked)
	{
		if (ADoor::GetOpenerDirectionToDoor(Interactor->GetActorLocation()) > 0.f)
		{
			bIsUnlocked = true;
			OpenDoor(Interactor->GetActorLocation());
			ADoor::PlaySFX();	
		}
	}
}

const FString& AOneSidedDoor::GetInteractPrompt(ACharacter* Interactor)
{
	if (ADoor::GetOpenerDirectionToDoor(Interactor->GetActorLocation()) > 0.f)
	{
		if (!bIsUnlocked) return RightSideInteractPrompt;
	}
	else
	{
		if (!bIsUnlocked)return WrongSideInteractPrompt;
	}
	
	return UnlockedInteractPrompt;
}
