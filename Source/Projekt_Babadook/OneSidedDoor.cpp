// Fill out your copyright notice in the Description page of Project Settings.

#include "OneSidedDoor.h"

#include "GameFramework/Character.h"


void AOneSidedDoor::Interact(ACharacter* Interactor)
{
	GetComponentByClass<UMeshComponent>()->SetSimulatePhysics(bIsUnlocked);
	
	if (!bIsUnlocked)
	{
		if (ADoor::GetOpenerDirectionToDoor(Interactor->GetActorLocation()) > 0.f)
		{
			bIsUnlocked = true;
			GetComponentByClass<UMeshComponent>()->SetSimulatePhysics(bIsUnlocked);
			SlightlyOpenDoor(Interactor->GetActorLocation());
			ADoor::PlaySFX();	
		}
	}
}

const FString& AOneSidedDoor::GetInteractPrompt(ACharacter* Interactor)
{
	if (ADoor::GetOpenerDirectionToDoor(Interactor->GetActorLocation()) > 0.f)
	{
		if (!bIsUnlocked) return RightSideInteractPrompt;
		
		return UnlockedInteractPrompt;
	}
	else
	{
		return WrongSideInteractPrompt;
	}
	
}
