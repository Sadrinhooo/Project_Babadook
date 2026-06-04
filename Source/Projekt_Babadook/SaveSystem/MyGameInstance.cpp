// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "MySaveGame.h"
#include "Kismet/GameplayStatics.h"

bool UMyGameInstance::IsItemCollected(FGameplayTag ItemTag) const
{
	return CollectedItems.HasTag(ItemTag);
}

void UMyGameInstance::CollectItem(FGameplayTag ItemTag)
{
	CollectedItems.AddTag(ItemTag);
}

/*
FDoorInfo UMyGameInstance::GetDoorInfo(FGuid Guid)
{
	if (FDoorInfo* CurrentDoor = SavedDoors.Find(Guid))
	{
		FDoorInfo& data = *CurrentDoor;
		return data;
	}
	
	return FDoorInfo{Guid, false, FRotator::ZeroRotator};
}
*/
/*
FDoorInfo UMyGameInstance::GetDoorInfo(int32 DoorID)
{
	if (FDoorInfo* FindDoor = DoorInfo.Find(DoorID))
	{
		FDoorInfo& Door = *FindDoor;
	}
	
	return FDoorInfo{false, FRotator(0,0,0)};
}
*/

void UMyGameInstance::SaveGameData()
{
	UGameplayStatics::SaveGameToSlot(SaveGame, GameSlotName,0);
	SaveGame->CollectedItems = CollectedItems;
	//SaveGame->SavedDoors = SavedDoors;
	SaveGame->LevelName = LevelName = UGameplayStatics::GetCurrentLevelName(this,true);
	//SaveGame->Doors = Doors;
}

void UMyGameInstance::LoadGameData()
{
	
	if (UGameplayStatics::DoesSaveGameExist(GameSlotName, 0))
	{
		bShouldLoad = true;
		
		USaveGame* Save = UGameplayStatics::LoadGameFromSlot(GameSlotName, 0);
		OnLoad(Save);
		
		if (UMySaveGame* SaveGameRef = Cast<UMySaveGame>(Save))
		{
			SaveGame = SaveGameRef;
			CollectedItems = SaveGame->CollectedItems;
			//SavedDoors = SaveGame->SavedDoors;
			
			FString SavedLevel = SaveGame->LevelName;
			UGameplayStatics::OpenLevel(this, FName(*SavedLevel));
			//Doors = SaveGame->Doors;
		}
	}
	else
	{
		if (UMySaveGame* SaveGameRef = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass())))
		{
			SaveGame = SaveGameRef;
		}
	}
	
}

void UMyGameInstance::Init()
{
	Super::Init();
	
	LoadGameData();
}
