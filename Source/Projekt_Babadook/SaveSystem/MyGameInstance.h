// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "MySaveGame.h"
#include "Engine/GameInstance.h"
#include "Projekt_Babadook/Door.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJEKT_BABADOOK_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	FGameplayTagContainer CollectedItems;
	
	UPROPERTY(BlueprintReadWrite)
	bool bShouldLoad = false;
	
	UPROPERTY(BlueprintReadWrite)
	FString GameSlotName = "Slot01";
	
	UPROPERTY(BlueprintReadWrite)
	UMySaveGame* SaveGame;
	
	//UPROPERTY(BlueprintReadWrite)
	//TMap<FGuid, FDoorInfo> SavedDoors;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString LevelName;
	
	//UPROPERTY(BlueprintReadWrite)
	//TArray<FVector> Doors;
	//TMap<int32, FDoorInfo> DoorInfo;
	
public:
	
	UFUNCTION(BlueprintCallable)
	bool IsItemCollected(FGameplayTag ItemTag) const;

	UFUNCTION(BlueprintCallable)
	void CollectItem(FGameplayTag ItemTag);
	
	/*
	UFUNCTION(BlueprintCallable)
	FDoorInfo GetDoorInfo(FGuid Guid);
	
	UFUNCTION(BlueprintCallable)
	FDoorInfo GetDoorInfo(int32 DoorID);
	*/
	
	UFUNCTION(BlueprintCallable)
	void SaveGameData() ;
	
	UFUNCTION(BlueprintCallable)
	void LoadGameData() ;

	UFUNCTION(BLueprintCallable, BlueprintImplementableEvent)
	void OnLoad(USaveGame* SaveGameRef);
	
	virtual void Init() override;
};
