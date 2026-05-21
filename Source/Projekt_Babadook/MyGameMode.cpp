// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"

#include "KeyItem.h"

AMyGameMode::AMyGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called every frame
void AMyGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (const FItemData& item : SharedInventory)
	{
		UE_LOG(LogTemp, Display, TEXT("%s"), *item.ItemName);
	}
}

void AMyGameMode::AddItem(FItemData Item)
{
	if (!HasAddedItem)
	{
		ShowInventoryTutorial();
		HasAddedItem = true;
	}
	SharedInventory.Add(Item);
}

#include "KeyItem.h"
