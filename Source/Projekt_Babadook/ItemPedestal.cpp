// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemPedestal.h"

#include "Door.h"

// Sets default values
AItemPedestal::AItemPedestal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AItemPedestal::BeginPlay()
{
	Super::BeginPlay();
	
	GameMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this));
}

void AItemPedestal::Interact(ACharacter* Interactor)
{
	if (!bIsItemPlaced)
	{
		if (PlayerHasKey(KeyIndex))
		{
			GameMode->SharedInventory[KeyIndex].NumberOfUses++;
			if (GameMode->SharedInventory[KeyIndex].NumberOfUses >= GameMode->SharedInventory[KeyIndex].MaxNumberOfUses) GameMode->SharedInventory.RemoveAt(KeyIndex);
			bIsItemPlaced = true;
			PlaceItem();
		}
	}
	else
	{
		if (GameMode)
		{
			GameMode->AddItem(ItemData);
		}
		PickUpItem();
		bIsItemPlaced = false;
	}
	
}

const FString& AItemPedestal::GetInteractPrompt(ACharacter* Interactor)
{
	if (bIsItemPlaced) return PickupInteractPrompt;
		
	if (PlayerHasKey(KeyIndex))
	{
		return PlaceInteractPromt;
	} else
	{
		return NoKeyInteractPrompt;
	}
}

UTexture2D* AItemPedestal::GetWidget()
{
	if (PlayerHasKey(KeyIndex))
	{
		return nullptr;
	}else
	{
		return Icon;
	}
}

bool AItemPedestal::PlayerHasKey(int32& OutIndex)
{
	for (int i = 0; i < GameMode->SharedInventory.Num(); i++)
	{
		if (GameMode->SharedInventory[i].ItemTag == RequiredKeyTag)
		{
			OutIndex = i;
			return true;
		}
	}

	return false;
}

