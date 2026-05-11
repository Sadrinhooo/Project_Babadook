// Fill out your copyright notice in the Description page of Project Settings.


#include "GemSocket.h"

#include "MyGameMode.h"

// Sets default values
AGemSocket::AGemSocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGemSocket::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this));
	
}

void AGemSocket::Interact(ACharacter* Interactor)
{
	
	if (!bIsItemPlaced)
	{
		if (PlayerHasItem(ItemIndex))
		{
			GameMode->SharedInventory.RemoveAt(ItemIndex);
			bIsItemPlaced = true;
			ItemPlaced();
		}
	}
	
	
}

const FString& AGemSocket::GetInteractPrompt(ACharacter* Interactor)
{
	if (bIsItemPlaced) return UnlockedInteractPrompt;
		
	if (PlayerHasItem(ItemIndex))
	{
		return WithKeyInteractPrompt;
	} else
	{
		return NoKeyInteractPrompt;
	}
}

bool AGemSocket::PlayerHasItem(int32& OutIndex)
{
	for (int i = 0; i < GameMode->SharedInventory.Num(); i++)
	{
		if (GameMode->SharedInventory[i].ItemTag == RequiredItemTag)
		{
			OutIndex = i;
			return true;
		}
	}
	return false;
}

